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
struct psmouse {char* name; struct input_dev* dev; } ;
struct ps2pp_info {int features; int kind; } ;
struct input_dev {int /*<<< orphan*/  relbit; int /*<<< orphan*/  keybit; } ;

/* Variables and functions */
 int /*<<< orphan*/  BTN_BACK ; 
 int /*<<< orphan*/  BTN_EXTRA ; 
 int /*<<< orphan*/  BTN_FORWARD ; 
 int /*<<< orphan*/  BTN_SIDE ; 
 int /*<<< orphan*/  BTN_TASK ; 
 int PS2PP_EXTRA_BTN ; 
 int PS2PP_HWHEEL ; 
#define  PS2PP_KIND_MX 131 
#define  PS2PP_KIND_TP3 130 
#define  PS2PP_KIND_TRACKMAN 129 
#define  PS2PP_KIND_WHEEL 128 
 int PS2PP_NAV_BTN ; 
 int PS2PP_SIDE_BTN ; 
 int PS2PP_TASK_BTN ; 
 int PS2PP_WHEEL ; 
 int /*<<< orphan*/  REL_HWHEEL ; 
 int /*<<< orphan*/  REL_WHEEL ; 
 int /*<<< orphan*/  __set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ps2pp_set_model_properties(struct psmouse *psmouse,
				       const struct ps2pp_info *model_info,
				       bool using_ps2pp)
{
	struct input_dev *input_dev = psmouse->dev;

	if (model_info->features & PS2PP_SIDE_BTN)
		__set_bit(BTN_SIDE, input_dev->keybit);

	if (model_info->features & PS2PP_EXTRA_BTN)
		__set_bit(BTN_EXTRA, input_dev->keybit);

	if (model_info->features & PS2PP_TASK_BTN)
		__set_bit(BTN_TASK, input_dev->keybit);

	if (model_info->features & PS2PP_NAV_BTN) {
		__set_bit(BTN_FORWARD, input_dev->keybit);
		__set_bit(BTN_BACK, input_dev->keybit);
	}

	if (model_info->features & PS2PP_WHEEL)
		__set_bit(REL_WHEEL, input_dev->relbit);

	if (model_info->features & PS2PP_HWHEEL)
		__set_bit(REL_HWHEEL, input_dev->relbit);

	switch (model_info->kind) {
		case PS2PP_KIND_WHEEL:
			psmouse->name = "Wheel Mouse";
			break;

		case PS2PP_KIND_MX:
			psmouse->name = "MX Mouse";
			break;

		case PS2PP_KIND_TP3:
			psmouse->name = "TouchPad 3";
			break;

		case PS2PP_KIND_TRACKMAN:
			psmouse->name = "TrackMan";
			break;

		default:
			/*
			 * Set name to "Mouse" only when using PS2++,
			 * otherwise let other protocols define suitable
			 * name
			 */
			if (using_ps2pp)
				psmouse->name = "Mouse";
			break;
	}
}