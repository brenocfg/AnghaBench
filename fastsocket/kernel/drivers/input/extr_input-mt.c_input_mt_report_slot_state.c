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
struct input_dev {size_t slot; struct input_mt_slot* mt; } ;

/* Variables and functions */
 int /*<<< orphan*/  ABS_MT_TOOL_TYPE ; 
 int /*<<< orphan*/  ABS_MT_TRACKING_ID ; 
 int /*<<< orphan*/  EV_ABS ; 
 int /*<<< orphan*/  input_event (struct input_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 unsigned int input_mt_get_value (struct input_mt_slot*,int /*<<< orphan*/ ) ; 
 int input_mt_new_trkid (struct input_dev*) ; 

void input_mt_report_slot_state(struct input_dev *dev,
				unsigned int tool_type, bool active)
{
	struct input_mt_slot *mt;
	int id;

	if (!dev->mt || !active) {
		input_event(dev, EV_ABS, ABS_MT_TRACKING_ID, -1);
		return;
	}

	mt = &dev->mt[dev->slot];
	id = input_mt_get_value(mt, ABS_MT_TRACKING_ID);
	if (id < 0 || input_mt_get_value(mt, ABS_MT_TOOL_TYPE) != tool_type)
		id = input_mt_new_trkid(dev);

	input_event(dev, EV_ABS, ABS_MT_TRACKING_ID, id);
	input_event(dev, EV_ABS, ABS_MT_TOOL_TYPE, tool_type);
}