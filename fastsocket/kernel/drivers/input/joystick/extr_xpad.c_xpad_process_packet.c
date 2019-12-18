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
typedef  int /*<<< orphan*/  u16 ;
struct usb_xpad {scalar_t__ dpad_mapping; struct input_dev* dev; } ;
struct input_dev {int dummy; } ;
typedef  int __s16 ;
typedef  int /*<<< orphan*/  __le16 ;

/* Variables and functions */
 int /*<<< orphan*/  ABS_HAT0X ; 
 int /*<<< orphan*/  ABS_HAT0Y ; 
 int /*<<< orphan*/  ABS_RX ; 
 int /*<<< orphan*/  ABS_RY ; 
 int /*<<< orphan*/  ABS_RZ ; 
 int /*<<< orphan*/  ABS_X ; 
 int /*<<< orphan*/  ABS_Y ; 
 int /*<<< orphan*/  ABS_Z ; 
 int /*<<< orphan*/  BTN_0 ; 
 int /*<<< orphan*/  BTN_1 ; 
 int /*<<< orphan*/  BTN_A ; 
 int /*<<< orphan*/  BTN_B ; 
 int /*<<< orphan*/  BTN_BACK ; 
 int /*<<< orphan*/  BTN_C ; 
 int /*<<< orphan*/  BTN_LEFT ; 
 int /*<<< orphan*/  BTN_RIGHT ; 
 int /*<<< orphan*/  BTN_START ; 
 int /*<<< orphan*/  BTN_THUMBL ; 
 int /*<<< orphan*/  BTN_THUMBR ; 
 int /*<<< orphan*/  BTN_X ; 
 int /*<<< orphan*/  BTN_Y ; 
 int /*<<< orphan*/  BTN_Z ; 
 scalar_t__ MAP_DPAD_TO_AXES ; 
 int /*<<< orphan*/  input_report_abs (struct input_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  input_report_key (struct input_dev*,int /*<<< orphan*/ ,unsigned char) ; 
 int /*<<< orphan*/  input_sync (struct input_dev*) ; 
 scalar_t__ le16_to_cpup (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void xpad_process_packet(struct usb_xpad *xpad, u16 cmd, unsigned char *data)
{
	struct input_dev *dev = xpad->dev;

	/* left stick */
	input_report_abs(dev, ABS_X,
			 (__s16) le16_to_cpup((__le16 *)(data + 12)));
	input_report_abs(dev, ABS_Y,
			 ~(__s16) le16_to_cpup((__le16 *)(data + 14)));

	/* right stick */
	input_report_abs(dev, ABS_RX,
			 (__s16) le16_to_cpup((__le16 *)(data + 16)));
	input_report_abs(dev, ABS_RY,
			 ~(__s16) le16_to_cpup((__le16 *)(data + 18)));

	/* triggers left/right */
	input_report_abs(dev, ABS_Z, data[10]);
	input_report_abs(dev, ABS_RZ, data[11]);

	/* digital pad */
	if (xpad->dpad_mapping == MAP_DPAD_TO_AXES) {
		input_report_abs(dev, ABS_HAT0X,
				 !!(data[2] & 0x08) - !!(data[2] & 0x04));
		input_report_abs(dev, ABS_HAT0Y,
				 !!(data[2] & 0x02) - !!(data[2] & 0x01));
	} else /* xpad->dpad_mapping == MAP_DPAD_TO_BUTTONS */ {
		input_report_key(dev, BTN_LEFT,  data[2] & 0x04);
		input_report_key(dev, BTN_RIGHT, data[2] & 0x08);
		input_report_key(dev, BTN_0,     data[2] & 0x01); /* up */
		input_report_key(dev, BTN_1,     data[2] & 0x02); /* down */
	}

	/* start/back buttons and stick press left/right */
	input_report_key(dev, BTN_START,  data[2] & 0x10);
	input_report_key(dev, BTN_BACK,   data[2] & 0x20);
	input_report_key(dev, BTN_THUMBL, data[2] & 0x40);
	input_report_key(dev, BTN_THUMBR, data[2] & 0x80);

	/* "analog" buttons A, B, X, Y */
	input_report_key(dev, BTN_A, data[4]);
	input_report_key(dev, BTN_B, data[5]);
	input_report_key(dev, BTN_X, data[6]);
	input_report_key(dev, BTN_Y, data[7]);

	/* "analog" buttons black, white */
	input_report_key(dev, BTN_C, data[8]);
	input_report_key(dev, BTN_Z, data[9]);

	input_sync(dev);
}