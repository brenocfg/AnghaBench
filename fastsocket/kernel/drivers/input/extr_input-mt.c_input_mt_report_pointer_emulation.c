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
struct input_mt_slot {int dummy; } ;
struct input_dev {int trkid; int mtsize; struct input_mt_slot* mt; } ;

/* Variables and functions */
 int /*<<< orphan*/  ABS_MT_POSITION_X ; 
 int /*<<< orphan*/  ABS_MT_POSITION_Y ; 
 int /*<<< orphan*/  ABS_MT_PRESSURE ; 
 int /*<<< orphan*/  ABS_MT_TRACKING_ID ; 
 int /*<<< orphan*/  ABS_PRESSURE ; 
 int /*<<< orphan*/  ABS_X ; 
 int /*<<< orphan*/  ABS_Y ; 
 int /*<<< orphan*/  BTN_TOUCH ; 
 int /*<<< orphan*/  EV_ABS ; 
 int /*<<< orphan*/  EV_KEY ; 
 int TRKID_SGN ; 
 int /*<<< orphan*/  input_event (struct input_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int input_mt_get_value (struct input_mt_slot*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  input_mt_report_finger_count (struct input_dev*,int) ; 

void input_mt_report_pointer_emulation(struct input_dev *dev, bool use_count)
{
	struct input_mt_slot *oldest = 0;
	int oldid = dev->trkid;
	int count = 0;
	int i;

	for (i = 0; i < dev->mtsize; ++i) {
		struct input_mt_slot *ps = &dev->mt[i];
		int id = input_mt_get_value(ps, ABS_MT_TRACKING_ID);

		if (id < 0)
			continue;
		if ((id - oldid) & TRKID_SGN) {
			oldest = ps;
			oldid = id;
		}
		count++;
	}

	input_event(dev, EV_KEY, BTN_TOUCH, count > 0);
	if (use_count)
		input_mt_report_finger_count(dev, count);

	if (oldest) {
		int x = input_mt_get_value(oldest, ABS_MT_POSITION_X);
		int y = input_mt_get_value(oldest, ABS_MT_POSITION_Y);
		int p = input_mt_get_value(oldest, ABS_MT_PRESSURE);

		input_event(dev, EV_ABS, ABS_X, x);
		input_event(dev, EV_ABS, ABS_Y, y);
		input_event(dev, EV_ABS, ABS_PRESSURE, p);
	} else {
		input_event(dev, EV_ABS, ABS_PRESSURE, 0);
	}
}