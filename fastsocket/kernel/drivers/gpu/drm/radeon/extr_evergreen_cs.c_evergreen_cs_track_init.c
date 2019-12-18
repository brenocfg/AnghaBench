#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct evergreen_cs_track {int* cb_color_bo_offset; int* cb_color_view; int* cb_color_slice; int cb_target_mask; int cb_shader_mask; int cb_dirty; int db_depth_slice; int db_depth_view; int db_depth_size; int db_depth_control; int db_z_info; int db_z_read_offset; int db_z_write_offset; int db_s_info; int db_s_read_offset; int db_s_write_offset; int db_dirty; int htile_offset; int* vgt_strmout_bo_offset; int streamout_dirty; int sx_misc_kill_all_prims; int /*<<< orphan*/ ** vgt_strmout_bo; scalar_t__* vgt_strmout_size; scalar_t__ htile_surface; int /*<<< orphan*/ * htile_bo; int /*<<< orphan*/ * db_s_write_bo; int /*<<< orphan*/ * db_s_read_bo; int /*<<< orphan*/ * db_z_write_bo; int /*<<< orphan*/ * db_z_read_bo; scalar_t__* cb_color_slice_idx; scalar_t__* cb_color_pitch; scalar_t__* cb_color_info; int /*<<< orphan*/ ** cb_color_bo; scalar_t__* cb_color_fmask_slice; scalar_t__* cb_color_cmask_slice; int /*<<< orphan*/ ** cb_color_cmask_bo; int /*<<< orphan*/ ** cb_color_fmask_bo; } ;

/* Variables and functions */

__attribute__((used)) static void evergreen_cs_track_init(struct evergreen_cs_track *track)
{
	int i;

	for (i = 0; i < 8; i++) {
		track->cb_color_fmask_bo[i] = NULL;
		track->cb_color_cmask_bo[i] = NULL;
		track->cb_color_cmask_slice[i] = 0;
		track->cb_color_fmask_slice[i] = 0;
	}

	for (i = 0; i < 12; i++) {
		track->cb_color_bo[i] = NULL;
		track->cb_color_bo_offset[i] = 0xFFFFFFFF;
		track->cb_color_info[i] = 0;
		track->cb_color_view[i] = 0xFFFFFFFF;
		track->cb_color_pitch[i] = 0;
		track->cb_color_slice[i] = 0xfffffff;
		track->cb_color_slice_idx[i] = 0;
	}
	track->cb_target_mask = 0xFFFFFFFF;
	track->cb_shader_mask = 0xFFFFFFFF;
	track->cb_dirty = true;

	track->db_depth_slice = 0xffffffff;
	track->db_depth_view = 0xFFFFC000;
	track->db_depth_size = 0xFFFFFFFF;
	track->db_depth_control = 0xFFFFFFFF;
	track->db_z_info = 0xFFFFFFFF;
	track->db_z_read_offset = 0xFFFFFFFF;
	track->db_z_write_offset = 0xFFFFFFFF;
	track->db_z_read_bo = NULL;
	track->db_z_write_bo = NULL;
	track->db_s_info = 0xFFFFFFFF;
	track->db_s_read_offset = 0xFFFFFFFF;
	track->db_s_write_offset = 0xFFFFFFFF;
	track->db_s_read_bo = NULL;
	track->db_s_write_bo = NULL;
	track->db_dirty = true;
	track->htile_bo = NULL;
	track->htile_offset = 0xFFFFFFFF;
	track->htile_surface = 0;

	for (i = 0; i < 4; i++) {
		track->vgt_strmout_size[i] = 0;
		track->vgt_strmout_bo[i] = NULL;
		track->vgt_strmout_bo_offset[i] = 0xFFFFFFFF;
	}
	track->streamout_dirty = true;
	track->sx_misc_kill_all_prims = false;
}