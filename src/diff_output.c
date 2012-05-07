#include "filter.h"
	git_diff_data_fn line_cb;
	git_diff_range range;
	return (digits > 0) ? 0 : -1;
		const char *scan = bufs[0].ptr;
		if (*scan != '@')
			return -1;

		if (read_next_int(&scan, &range.old_start) < 0)
			return -1;
		if (*scan == ',' && read_next_int(&scan, &range.old_lines) < 0)
			return -1;

		if (read_next_int(&scan, &range.new_start) < 0)
			return -1;
		if (*scan == ',' && read_next_int(&scan, &range.new_lines) < 0)
			return -1;

		if (range.old_start < 0 || range.new_start < 0)
			return -1;

		memcpy(&info->range, &range, sizeof(git_diff_range));

		return info->hunk_cb(
			info->cb_data, info->delta, &range, bufs[0].ptr, bufs[0].size);

	if ((len == 2 || len == 3) && info->line_cb) {
		if (info->line_cb(
			info->cb_data, info->delta, &info->range, origin, bufs[1].ptr, bufs[1].size) < 0)
			return -1;
		if (len == 3) {
			return info->line_cb(
				info->cb_data, info->delta, &info->range, origin, bufs[2].ptr, bufs[2].size);
	return 0;
static int update_file_is_binary_by_attr(git_repository *repo, git_diff_file *file)
	if (git_attr_get(repo, 0, file->path, "diff", &value) < 0)
		return -1;


	return 0;
static void update_delta_is_binary(git_diff_delta *delta)
	if ((delta->old_file.flags & GIT_DIFF_FILE_BINARY) != 0 ||
		(delta->new_file.flags & GIT_DIFF_FILE_BINARY) != 0)
	else if ((delta->old_file.flags & GIT_DIFF_FILE_NOT_BINARY) != 0 ||
			 (delta->new_file.flags & GIT_DIFF_FILE_NOT_BINARY) != 0)
	int error = 0, mirror_new;
	if ((git_off_t)((size_t)delta->old_file.size) != delta->old_file.size ||
		(git_off_t)((size_t)delta->new_file.size) != delta->new_file.size)
		delta->old_file.flags |= GIT_DIFF_FILE_BINARY;
		delta->new_file.flags |= GIT_DIFF_FILE_BINARY;
		return 0;
		delta->old_file.flags |= GIT_DIFF_FILE_NOT_BINARY;
		delta->new_file.flags |= GIT_DIFF_FILE_NOT_BINARY;
		return 0;
	if (update_file_is_binary_by_attr(diff->repo, &delta->old_file) < 0)
		return -1;
	mirror_new = (delta->new_file.path == delta->old_file.path ||
				  strcmp(delta->new_file.path, delta->old_file.path) == 0);
		delta->new_file.flags &= (delta->old_file.flags & BINARY_DIFF_FLAGS);
		error = update_file_is_binary_by_attr(diff->repo, &delta->new_file);
	update_delta_is_binary(delta);
	git_buf search;
	git_text_stats stats;

	if ((delta->old_file.flags & BINARY_DIFF_FLAGS) == 0) {
		search.ptr  = old_data->data;
		search.size = min(old_data->len, 4000);

		git_text_gather_stats(&stats, &search);

		if (git_text_is_binary(&stats))
			delta->old_file.flags |= GIT_DIFF_FILE_BINARY;
			delta->old_file.flags |= GIT_DIFF_FILE_NOT_BINARY;
	if ((delta->new_file.flags & BINARY_DIFF_FLAGS) == 0) {
		search.ptr  = new_data->data;
		search.size = min(new_data->len, 4000);

		git_text_gather_stats(&stats, &search);

		if (git_text_is_binary(&stats))
			delta->new_file.flags |= GIT_DIFF_FILE_BINARY;
			delta->new_file.flags |= GIT_DIFF_FILE_NOT_BINARY;
	update_delta_is_binary(delta);
	return 0;
		return 0;
	if (git_blob_lookup(blob, repo, oid) < 0)
		return -1;
	map->data = (void *)git_blob_rawcontent(*blob);
	map->len  = git_blob_rawsize(*blob);
	return 0;
	int error = 0;
	git_buf path = GIT_BUF_INIT;

	if (git_buf_joinpath(&path, git_repository_workdir(repo), file->path) < 0)
		return -1;
		ssize_t read_len;

		GITERR_CHECK_ALLOC(map->data);

		read_len = p_readlink(path.ptr, map->data, (size_t)file->size + 1);
		if (read_len != (ssize_t)file->size) {
			giterr_set(GITERR_OS, "Failed to read symlink '%s'", file->path);
			error = -1;
		} else
			map->len = read_len;
		error = git_futils_mmap_ro_file(map, path.ptr);
	git_buf_free(&path);
	git_diff_data_fn line_cb)
	int error = 0;
		mmfile_t old_xdiff_data, new_xdiff_data;
		if (delta->status == GIT_DELTA_UNMODIFIED &&
			(diff->opts.flags & GIT_DIFF_INCLUDE_UNMODIFIED) == 0)
		if ((error = file_is_binary_by_attr(diff, delta)) < 0)
				error = get_workdir_content(diff->repo, &delta->old_file, &old_data);
					diff->repo, &delta->old_file.oid, &old_data, &old_blob);

			if (error < 0)
			(hunk_cb || line_cb || git_oid_iszero(&delta->new_file.oid)) &&
				error = get_workdir_content(diff->repo, &delta->new_file, &new_data);
					diff->repo, &delta->new_file.oid, &new_data, &new_blob);

			if (error < 0)
			if ((delta->new_file.flags | GIT_DIFF_FILE_VALID_OID) == 0) {
					&delta->new_file.oid, new_data.data, new_data.len, GIT_OBJ_BLOB);

				if (error < 0)
				if (git_oid_cmp(&delta->old_file.oid, &delta->new_file.oid) == 0) {
					if ((diff->opts.flags & GIT_DIFF_INCLUDE_UNMODIFIED) == 0)
						goto cleanup;
			if (error < 0)
			if (error < 0)
		old_xdiff_data.ptr = old_data.data;
		old_xdiff_data.size = old_data.len;
		new_xdiff_data.ptr = new_data.data;
		new_xdiff_data.size = new_data.len;
		xdl_diff(&old_xdiff_data, &new_xdiff_data,
		release_content(&delta->old_file, &old_data, old_blob);
		release_content(&delta->new_file, &new_data, new_blob);
		if (error < 0)
	git_diff_data_fn print_cb;
		return 0;
	old_suffix = pick_suffix(delta->old_file.mode);
	new_suffix = pick_suffix(delta->new_file.mode);
	if (delta->old_file.path != delta->new_file.path &&
		strcmp(delta->old_file.path,delta->new_file.path) != 0)
			delta->old_file.path, old_suffix, delta->new_file.path, new_suffix);
	else if (delta->old_file.mode != delta->new_file.mode &&
		delta->old_file.mode != 0 && delta->new_file.mode != 0)
			delta->old_file.path, new_suffix, delta->old_file.mode, delta->new_file.mode);
		git_buf_printf(pi->buf, "%c\t%s%c\n", code, delta->old_file.path, old_suffix);
		git_buf_printf(pi->buf, "%c\t%s\n", code, delta->old_file.path);
	if (git_buf_oom(pi->buf))
		return -1;
	return pi->print_cb(pi->cb_data, delta, NULL, GIT_DIFF_LINE_FILE_HDR, git_buf_cstr(pi->buf), git_buf_len(pi->buf));
	git_diff_data_fn print_cb)
	git_oid_tostr(start_oid, sizeof(start_oid), &delta->old_file.oid);
	git_oid_tostr(end_oid, sizeof(end_oid), &delta->new_file.oid);
	if (delta->old_file.mode == delta->new_file.mode) {
			start_oid, end_oid, delta->old_file.mode);
		if (delta->old_file.mode == 0) {
			git_buf_printf(pi->buf, "new file mode %o\n", delta->new_file.mode);
		} else if (delta->new_file.mode == 0) {
			git_buf_printf(pi->buf, "deleted file mode %o\n", delta->old_file.mode);
			git_buf_printf(pi->buf, "old mode %o\n", delta->old_file.mode);
			git_buf_printf(pi->buf, "new mode %o\n", delta->new_file.mode);
	if (git_buf_oom(pi->buf))
		return -1;

	return 0;
	const char *oldpfx = pi->diff->opts.old_prefix;
	const char *oldpath = delta->old_file.path;
	const char *newpfx = pi->diff->opts.new_prefix;
	const char *newpath = delta->new_file.path;
	int result;
	if (!oldpfx)
		oldpfx = DIFF_OLD_PREFIX_DEFAULT;

	if (!newpfx)
		newpfx = DIFF_NEW_PREFIX_DEFAULT;

	git_buf_printf(pi->buf, "diff --git %s%s %s%s\n", oldpfx, delta->old_file.path, newpfx, delta->new_file.path);

	if (print_oid_range(pi, delta) < 0)
		return -1;
	if (git_oid_iszero(&delta->old_file.oid)) {
	if (git_oid_iszero(&delta->new_file.oid)) {
		newpfx = "";
		newpath = "/dev/null";
	if (git_buf_oom(pi->buf))
		return -1;

    result = pi->print_cb(pi->cb_data, delta, NULL, GIT_DIFF_LINE_FILE_HDR, git_buf_cstr(pi->buf), git_buf_len(pi->buf));
    if (result < 0)
        return result;
    if (delta->binary != 1)
        return 0;
	if (git_buf_oom(pi->buf))
		return -1;
	return pi->print_cb(pi->cb_data, delta, NULL, GIT_DIFF_LINE_BINARY, git_buf_cstr(pi->buf), git_buf_len(pi->buf));
	if (git_buf_printf(pi->buf, "%.*s", (int)header_len, header) < 0)
		return -1;
	return pi->print_cb(pi->cb_data, d, r, GIT_DIFF_LINE_HUNK_HDR, git_buf_cstr(pi->buf), git_buf_len(pi->buf));
	git_diff_range *range,
	if (git_buf_oom(pi->buf))
		return -1;
	return pi->print_cb(pi->cb_data, delta, range, line_origin, git_buf_cstr(pi->buf), git_buf_len(pi->buf));
	git_diff_data_fn print_cb)
	git_diff_data_fn line_cb)
	mmfile_t old_data, new_data;
		old_data.ptr  = (char *)git_blob_rawcontent(old_blob);
		old_data.size = git_blob_rawsize(old_blob);
		old_data.ptr  = "";
		old_data.size = 0;
		new_data.ptr  = (char *)git_blob_rawcontent(new_blob);
		new_data.size = git_blob_rawsize(new_blob);
		new_data.ptr  = "";
		new_data.size = 0;
	delta.status = old_data.ptr ?
		(new_data.ptr ? GIT_DELTA_MODIFIED : GIT_DELTA_DELETED) :
		(new_data.ptr ? GIT_DELTA_ADDED : GIT_DELTA_UNTRACKED);
	delta.old_file.mode = 0100644; /* can't know the truth from a blob alone */
	delta.new_file.mode = 0100644;
	git_oid_cpy(&delta.old_file.oid, git_object_id((const git_object *)old_blob));
	git_oid_cpy(&delta.new_file.oid, git_object_id((const git_object *)new_blob));
	delta.old_file.path = NULL;
	delta.new_file.path = NULL;
	xdl_diff(&old_data, &new_data, &xdiff_params, &xdiff_config, &xdiff_callback);
	return 0;