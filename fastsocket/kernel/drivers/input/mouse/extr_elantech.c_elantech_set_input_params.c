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
struct psmouse {struct elantech_data* private; struct input_dev* dev; } ;
struct input_dev {int /*<<< orphan*/  keybit; int /*<<< orphan*/  evbit; } ;
struct elantech_data {int hw_version; int fw_version_maj; int capabilities; } ;

/* Variables and functions */
 int /*<<< orphan*/  ABS_HAT0X ; 
 int /*<<< orphan*/  ABS_HAT0Y ; 
 int /*<<< orphan*/  ABS_HAT1X ; 
 int /*<<< orphan*/  ABS_HAT1Y ; 
 int /*<<< orphan*/  ABS_X ; 
 int /*<<< orphan*/  ABS_Y ; 
 int /*<<< orphan*/  BTN_BACK ; 
 int /*<<< orphan*/  BTN_FORWARD ; 
 int /*<<< orphan*/  BTN_LEFT ; 
 int /*<<< orphan*/  BTN_RIGHT ; 
 int /*<<< orphan*/  BTN_TOOL_DOUBLETAP ; 
 int /*<<< orphan*/  BTN_TOOL_FINGER ; 
 int /*<<< orphan*/  BTN_TOOL_TRIPLETAP ; 
 int /*<<< orphan*/  BTN_TOUCH ; 
 int /*<<< orphan*/  ETP_2FT_XMAX ; 
 int /*<<< orphan*/  ETP_2FT_XMIN ; 
 int /*<<< orphan*/  ETP_2FT_YMAX ; 
 int /*<<< orphan*/  ETP_2FT_YMIN ; 
 int ETP_CAP_HAS_ROCKER ; 
 int /*<<< orphan*/  ETP_XMAX_V1 ; 
 int /*<<< orphan*/  ETP_XMAX_V2 ; 
 int /*<<< orphan*/  ETP_XMIN_V1 ; 
 int /*<<< orphan*/  ETP_XMIN_V2 ; 
 int /*<<< orphan*/  ETP_YMAX_V1 ; 
 int /*<<< orphan*/  ETP_YMAX_V2 ; 
 int /*<<< orphan*/  ETP_YMIN_V1 ; 
 int /*<<< orphan*/  ETP_YMIN_V2 ; 
 int /*<<< orphan*/  EV_ABS ; 
 int /*<<< orphan*/  EV_KEY ; 
 int /*<<< orphan*/  __set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  input_set_abs_params (struct input_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void elantech_set_input_params(struct psmouse *psmouse)
{
	struct input_dev *dev = psmouse->dev;
	struct elantech_data *etd = psmouse->private;

	__set_bit(EV_KEY, dev->evbit);
	__set_bit(EV_ABS, dev->evbit);

	__set_bit(BTN_LEFT, dev->keybit);
	__set_bit(BTN_RIGHT, dev->keybit);

	__set_bit(BTN_TOUCH, dev->keybit);
	__set_bit(BTN_TOOL_FINGER, dev->keybit);
	__set_bit(BTN_TOOL_DOUBLETAP, dev->keybit);
	__set_bit(BTN_TOOL_TRIPLETAP, dev->keybit);

	switch (etd->hw_version) {
	case 1:
		/* Rocker button */
		if ((etd->fw_version_maj == 0x01) &&
		    (etd->capabilities & ETP_CAP_HAS_ROCKER)) {
			__set_bit(BTN_FORWARD, dev->keybit);
			__set_bit(BTN_BACK, dev->keybit);
		}
		input_set_abs_params(dev, ABS_X, ETP_XMIN_V1, ETP_XMAX_V1, 0, 0);
		input_set_abs_params(dev, ABS_Y, ETP_YMIN_V1, ETP_YMAX_V1, 0, 0);
		break;

	case 2:
		input_set_abs_params(dev, ABS_X, ETP_XMIN_V2, ETP_XMAX_V2, 0, 0);
		input_set_abs_params(dev, ABS_Y, ETP_YMIN_V2, ETP_YMAX_V2, 0, 0);
		input_set_abs_params(dev, ABS_HAT0X, ETP_2FT_XMIN, ETP_2FT_XMAX, 0, 0);
		input_set_abs_params(dev, ABS_HAT0Y, ETP_2FT_YMIN, ETP_2FT_YMAX, 0, 0);
		input_set_abs_params(dev, ABS_HAT1X, ETP_2FT_XMIN, ETP_2FT_XMAX, 0, 0);
		input_set_abs_params(dev, ABS_HAT1Y, ETP_2FT_YMIN, ETP_2FT_YMAX, 0, 0);
		break;
	}
}