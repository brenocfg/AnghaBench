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
typedef  int u32 ;
struct svga_timing_regs {int /*<<< orphan*/  v_sync_end_regs; int /*<<< orphan*/  v_blank_end_regs; int /*<<< orphan*/  v_sync_start_regs; int /*<<< orphan*/  v_blank_start_regs; int /*<<< orphan*/  v_display_regs; int /*<<< orphan*/  v_total_regs; int /*<<< orphan*/  h_sync_end_regs; int /*<<< orphan*/  h_blank_end_regs; int /*<<< orphan*/  h_sync_start_regs; int /*<<< orphan*/  h_blank_start_regs; int /*<<< orphan*/  h_display_regs; int /*<<< orphan*/  h_total_regs; } ;
struct fb_var_screeninfo {int xres; int left_margin; int right_margin; int hsync_len; int yres; int upper_margin; int lower_margin; int vsync_len; } ;

/* Variables and functions */
 int EINVAL ; 
 int svga_regset_size (int /*<<< orphan*/ ) ; 

int svga_check_timings(const struct svga_timing_regs *tm, struct fb_var_screeninfo *var, int node)
{
	u32 value;

	var->xres         = (var->xres+7)&~7;
	var->left_margin  = (var->left_margin+7)&~7;
	var->right_margin = (var->right_margin+7)&~7;
	var->hsync_len    = (var->hsync_len+7)&~7;

	/* Check horizontal total */
	value = var->xres + var->left_margin + var->right_margin + var->hsync_len;
	if (((value / 8) - 5) >= svga_regset_size (tm->h_total_regs))
		return -EINVAL;

	/* Check horizontal display and blank start */
	value = var->xres;
	if (((value / 8) - 1) >= svga_regset_size (tm->h_display_regs))
		return -EINVAL;
	if (((value / 8) - 1) >= svga_regset_size (tm->h_blank_start_regs))
		return -EINVAL;

	/* Check horizontal sync start */
	value = var->xres + var->right_margin;
	if (((value / 8) - 1) >= svga_regset_size (tm->h_sync_start_regs))
		return -EINVAL;

	/* Check horizontal blank end (or length) */
	value = var->left_margin + var->right_margin + var->hsync_len;
	if ((value == 0) || ((value / 8) >= svga_regset_size (tm->h_blank_end_regs)))
		return -EINVAL;

	/* Check horizontal sync end (or length) */
	value = var->hsync_len;
	if ((value == 0) || ((value / 8) >= svga_regset_size (tm->h_sync_end_regs)))
		return -EINVAL;

	/* Check vertical total */
	value = var->yres + var->upper_margin + var->lower_margin + var->vsync_len;
	if ((value - 1) >= svga_regset_size(tm->v_total_regs))
		return -EINVAL;

	/* Check vertical display and blank start */
	value = var->yres;
	if ((value - 1) >= svga_regset_size(tm->v_display_regs))
		return -EINVAL;
	if ((value - 1) >= svga_regset_size(tm->v_blank_start_regs))
		return -EINVAL;

	/* Check vertical sync start */
	value = var->yres + var->lower_margin;
	if ((value - 1) >= svga_regset_size(tm->v_sync_start_regs))
		return -EINVAL;

	/* Check vertical blank end (or length) */
	value = var->upper_margin + var->lower_margin + var->vsync_len;
	if ((value == 0) || (value >= svga_regset_size (tm->v_blank_end_regs)))
		return -EINVAL;

	/* Check vertical sync end  (or length) */
	value = var->vsync_len;
	if ((value == 0) || (value >= svga_regset_size (tm->v_sync_end_regs)))
		return -EINVAL;

	return 0;
}