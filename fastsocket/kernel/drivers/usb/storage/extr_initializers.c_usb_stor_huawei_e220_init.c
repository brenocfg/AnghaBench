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
struct us_data {int /*<<< orphan*/  send_ctrl_pipe; } ;

/* Variables and functions */
 int USB_RECIP_DEVICE ; 
 int /*<<< orphan*/  USB_REQ_SET_FEATURE ; 
 int USB_TYPE_STANDARD ; 
 int /*<<< orphan*/  US_DEBUGP (char*,int) ; 
 int usb_stor_control_msg (struct us_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int,int /*<<< orphan*/ *,int,int) ; 

int usb_stor_huawei_e220_init(struct us_data *us)
{
	int result;

	result = usb_stor_control_msg(us, us->send_ctrl_pipe,
				      USB_REQ_SET_FEATURE,
				      USB_TYPE_STANDARD | USB_RECIP_DEVICE,
				      0x01, 0x0, NULL, 0x0, 1000);
	US_DEBUGP("Huawei mode set result is %d\n", result);
	return 0;
}