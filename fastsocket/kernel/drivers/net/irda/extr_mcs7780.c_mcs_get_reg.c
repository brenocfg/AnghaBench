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
struct usb_device {int dummy; } ;
struct mcs_cb {struct usb_device* usbdev; } ;
typedef  int /*<<< orphan*/  __u16 ;

/* Variables and functions */
 int /*<<< orphan*/  MCS_CTRL_TIMEOUT ; 
 int /*<<< orphan*/  MCS_RDREQ ; 
 int /*<<< orphan*/  MCS_RD_RTYPE ; 
 int /*<<< orphan*/  msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int usb_control_msg (struct usb_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_rcvctrlpipe (struct usb_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mcs_get_reg(struct mcs_cb *mcs, __u16 reg, __u16 * val)
{
	struct usb_device *dev = mcs->usbdev;
	int ret = usb_control_msg(dev, usb_rcvctrlpipe(dev, 0), MCS_RDREQ,
				  MCS_RD_RTYPE, 0, reg, val, 2,
				  msecs_to_jiffies(MCS_CTRL_TIMEOUT));

	return ret;
}