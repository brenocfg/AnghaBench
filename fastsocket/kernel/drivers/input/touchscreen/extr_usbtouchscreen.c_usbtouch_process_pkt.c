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
struct usbtouch_usb {int /*<<< orphan*/  input; int /*<<< orphan*/  press; int /*<<< orphan*/  y; int /*<<< orphan*/  x; int /*<<< orphan*/  touch; struct usbtouch_device_info* type; } ;
struct usbtouch_device_info {scalar_t__ max_press; int /*<<< orphan*/  (* read_data ) (struct usbtouch_usb*,unsigned char*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  ABS_PRESSURE ; 
 int /*<<< orphan*/  ABS_X ; 
 int /*<<< orphan*/  ABS_Y ; 
 int /*<<< orphan*/  BTN_TOUCH ; 
 int /*<<< orphan*/  input_report_abs (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  input_report_key (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  input_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct usbtouch_usb*,unsigned char*) ; 
 scalar_t__ swap_xy ; 

__attribute__((used)) static void usbtouch_process_pkt(struct usbtouch_usb *usbtouch,
                                 unsigned char *pkt, int len)
{
	struct usbtouch_device_info *type = usbtouch->type;

	if (!type->read_data(usbtouch, pkt))
			return;

	input_report_key(usbtouch->input, BTN_TOUCH, usbtouch->touch);

	if (swap_xy) {
		input_report_abs(usbtouch->input, ABS_X, usbtouch->y);
		input_report_abs(usbtouch->input, ABS_Y, usbtouch->x);
	} else {
		input_report_abs(usbtouch->input, ABS_X, usbtouch->x);
		input_report_abs(usbtouch->input, ABS_Y, usbtouch->y);
	}
	if (type->max_press)
		input_report_abs(usbtouch->input, ABS_PRESSURE, usbtouch->press);
	input_sync(usbtouch->input);
}