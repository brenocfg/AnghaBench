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
typedef  int u16 ;
struct synaptics_ts_data {int flags; int* snap_down; int* snap_up; int* snap_down_on; int* snap_down_off; int* snap_up_on; int* snap_up_off; int /*<<< orphan*/  input_dev; } ;
struct synaptics_i2c_rmi_platform_data {int inactive_left; int inactive_right; int inactive_top; int inactive_bottom; int snap_left_on; int snap_left_off; int snap_right_on; int snap_right_off; int snap_top_on; int snap_top_off; int snap_bottom_on; int snap_bottom_off; int fuzz_x; int fuzz_y; int fuzz_p; int fuzz_w; } ;

/* Variables and functions */
 int /*<<< orphan*/  ABS_HAT0X ; 
 int /*<<< orphan*/  ABS_HAT0Y ; 
 int /*<<< orphan*/  ABS_PRESSURE ; 
 int /*<<< orphan*/  ABS_TOOL_WIDTH ; 
 int /*<<< orphan*/  ABS_X ; 
 int /*<<< orphan*/  ABS_Y ; 
 int SYNAPTICS_SWAP_XY ; 
 int /*<<< orphan*/  input_set_abs_params (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_info (char*,int,int,...) ; 

__attribute__((used)) static void compute_areas(struct synaptics_ts_data *ts,
			  struct synaptics_i2c_rmi_platform_data *pdata,
			  u16 max_x, u16 max_y)
{
	int inactive_area_left;
	int inactive_area_right;
	int inactive_area_top;
	int inactive_area_bottom;
	int snap_left_on;
	int snap_left_off;
	int snap_right_on;
	int snap_right_off;
	int snap_top_on;
	int snap_top_off;
	int snap_bottom_on;
	int snap_bottom_off;
	int fuzz_x;
	int fuzz_y;
	int fuzz_p;
	int fuzz_w;
	int swapped = !!(ts->flags & SYNAPTICS_SWAP_XY);

	inactive_area_left = pdata->inactive_left;
	inactive_area_right = pdata->inactive_right;
	inactive_area_top = pdata->inactive_top;
	inactive_area_bottom = pdata->inactive_bottom;
	snap_left_on = pdata->snap_left_on;
	snap_left_off = pdata->snap_left_off;
	snap_right_on = pdata->snap_right_on;
	snap_right_off = pdata->snap_right_off;
	snap_top_on = pdata->snap_top_on;
	snap_top_off = pdata->snap_top_off;
	snap_bottom_on = pdata->snap_bottom_on;
	snap_bottom_off = pdata->snap_bottom_off;
	fuzz_x = pdata->fuzz_x;
	fuzz_y = pdata->fuzz_y;
	fuzz_p = pdata->fuzz_p;
	fuzz_w = pdata->fuzz_w;

	inactive_area_left = inactive_area_left * max_x / 0x10000;
	inactive_area_right = inactive_area_right * max_x / 0x10000;
	inactive_area_top = inactive_area_top * max_y / 0x10000;
	inactive_area_bottom = inactive_area_bottom * max_y / 0x10000;
	snap_left_on = snap_left_on * max_x / 0x10000;
	snap_left_off = snap_left_off * max_x / 0x10000;
	snap_right_on = snap_right_on * max_x / 0x10000;
	snap_right_off = snap_right_off * max_x / 0x10000;
	snap_top_on = snap_top_on * max_y / 0x10000;
	snap_top_off = snap_top_off * max_y / 0x10000;
	snap_bottom_on = snap_bottom_on * max_y / 0x10000;
	snap_bottom_off = snap_bottom_off * max_y / 0x10000;
	fuzz_x = fuzz_x * max_x / 0x10000;
	fuzz_y = fuzz_y * max_y / 0x10000;


	ts->snap_down[swapped] = -inactive_area_left;
	ts->snap_up[swapped] = max_x + inactive_area_right;
	ts->snap_down[!swapped] = -inactive_area_top;
	ts->snap_up[!swapped] = max_y + inactive_area_bottom;
	ts->snap_down_on[swapped] = snap_left_on;
	ts->snap_down_off[swapped] = snap_left_off;
	ts->snap_up_on[swapped] = max_x - snap_right_on;
	ts->snap_up_off[swapped] = max_x - snap_right_off;
	ts->snap_down_on[!swapped] = snap_top_on;
	ts->snap_down_off[!swapped] = snap_top_off;
	ts->snap_up_on[!swapped] = max_y - snap_bottom_on;
	ts->snap_up_off[!swapped] = max_y - snap_bottom_off;
	pr_info("synaptics_ts_probe: max_x %d, max_y %d\n", max_x, max_y);
	pr_info("synaptics_ts_probe: inactive_x %d %d, inactive_y %d %d\n",
	       inactive_area_left, inactive_area_right,
	       inactive_area_top, inactive_area_bottom);
	pr_info("synaptics_ts_probe: snap_x %d-%d %d-%d, snap_y %d-%d %d-%d\n",
	       snap_left_on, snap_left_off, snap_right_on, snap_right_off,
	       snap_top_on, snap_top_off, snap_bottom_on, snap_bottom_off);

	input_set_abs_params(ts->input_dev, ABS_X,
			     -inactive_area_left, max_x + inactive_area_right,
			     fuzz_x, 0);
	input_set_abs_params(ts->input_dev, ABS_Y,
			     -inactive_area_top, max_y + inactive_area_bottom,
			     fuzz_y, 0);
	input_set_abs_params(ts->input_dev, ABS_PRESSURE, 0, 255, fuzz_p, 0);
	input_set_abs_params(ts->input_dev, ABS_TOOL_WIDTH, 0, 15, fuzz_w, 0);
	input_set_abs_params(ts->input_dev, ABS_HAT0X, -inactive_area_left,
			     max_x + inactive_area_right, fuzz_x, 0);
	input_set_abs_params(ts->input_dev, ABS_HAT0Y, -inactive_area_top,
			     max_y + inactive_area_bottom, fuzz_y, 0);
}