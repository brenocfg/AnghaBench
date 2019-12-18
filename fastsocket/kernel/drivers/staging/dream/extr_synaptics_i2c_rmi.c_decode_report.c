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
typedef  int u8 ;
typedef  int u32 ;
typedef  int u16 ;
struct synaptics_ts_data {int flags; int* max; int** snap_state; int* snap_down_off; int* snap_down; int* snap_up_off; int* snap_up; int* snap_down_on; int* snap_up_on; int /*<<< orphan*/  input_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ABS_HAT0X ; 
 int /*<<< orphan*/  ABS_HAT0Y ; 
 int /*<<< orphan*/  ABS_PRESSURE ; 
 int /*<<< orphan*/  ABS_TOOL_WIDTH ; 
 int /*<<< orphan*/  ABS_X ; 
 int /*<<< orphan*/  ABS_Y ; 
 int /*<<< orphan*/  BTN_2 ; 
 int /*<<< orphan*/  BTN_TOUCH ; 
 int SYNAPTICS_FLIP_X ; 
 int SYNAPTICS_SNAP_TO_INACTIVE_EDGE ; 
 int SYNAPTICS_SWAP_XY ; 
 int /*<<< orphan*/  input_report_abs (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  input_report_key (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  input_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  swap (int,int) ; 

__attribute__((used)) static void decode_report(struct synaptics_ts_data *ts, u8 *buf)
{
/*
 * This sensor sends two 6-byte absolute finger reports, an optional
 * 2-byte relative report followed by a status byte. This function
 * reads the two finger reports and transforms the coordinates
 * according the platform data so they can be aligned with the lcd
 * behind the touchscreen. Typically we flip the y-axis since the
 * sensor uses the bottom left corner as the origin, but if the sensor
 * is mounted upside down the platform data will request that the
 * x-axis should be flipped instead. The snap to inactive edge border
 * are used to allow tapping the edges of the screen on the G1. The
 * active area of the touchscreen is smaller than the lcd. When the
 * finger gets close the edge of the screen we snap it to the
 * edge. This allows ui elements at the edge of the screen to be hit,
 * and it prevents hitting ui elements that are not at the edge of the
 * screen when the finger is touching the edge.
 */
	int pos[2][2];
	int f, a;
	int base = 2;
	int z = buf[1];
	int w = buf[0] >> 4;
	int finger = buf[0] & 7;
	int finger2_pressed;

	for (f = 0; f < 2; f++) {
		u32 flip_flag = SYNAPTICS_FLIP_X;
		for (a = 0; a < 2; a++) {
			int p = buf[base + 1];
			p |= (u16)(buf[base] & 0x1f) << 8;
			if (ts->flags & flip_flag)
				p = ts->max[a] - p;
			if (ts->flags & SYNAPTICS_SNAP_TO_INACTIVE_EDGE) {
				if (ts->snap_state[f][a]) {
					if (p <= ts->snap_down_off[a])
						p = ts->snap_down[a];
					else if (p >= ts->snap_up_off[a])
						p = ts->snap_up[a];
					else
						ts->snap_state[f][a] = 0;
				} else {
					if (p <= ts->snap_down_on[a]) {
						p = ts->snap_down[a];
						ts->snap_state[f][a] = 1;
					} else if (p >= ts->snap_up_on[a]) {
						p = ts->snap_up[a];
						ts->snap_state[f][a] = 1;
					}
				}
			}
			pos[f][a] = p;
			base += 2;
			flip_flag <<= 1;
		}
		base += 2;
		if (ts->flags & SYNAPTICS_SWAP_XY)
			swap(pos[f][0], pos[f][1]);
	}
	if (z) {
		input_report_abs(ts->input_dev, ABS_X, pos[0][0]);
		input_report_abs(ts->input_dev, ABS_Y, pos[0][1]);
	}
	input_report_abs(ts->input_dev, ABS_PRESSURE, z);
	input_report_abs(ts->input_dev, ABS_TOOL_WIDTH, w);
	input_report_key(ts->input_dev, BTN_TOUCH, finger);
	finger2_pressed = finger > 1 && finger != 7;
	input_report_key(ts->input_dev, BTN_2, finger2_pressed);
	if (finger2_pressed) {
		input_report_abs(ts->input_dev, ABS_HAT0X, pos[1][0]);
		input_report_abs(ts->input_dev, ABS_HAT0Y, pos[1][1]);
	}
	input_sync(ts->input_dev);
}