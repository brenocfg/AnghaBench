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
typedef  unsigned short u8 ;
struct usb_device {int /*<<< orphan*/  dev; } ;
typedef  enum spcp8x5_type { ____Placeholder_spcp8x5_type } spcp8x5_type ;

/* Variables and functions */
 int EPERM ; 
 int /*<<< orphan*/  SET_UART_STATUS ; 
 int /*<<< orphan*/  SET_UART_STATUS_TYPE ; 
 int SPCP825_007_TYPE ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int) ; 
 int usb_control_msg (struct usb_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned short,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  usb_sndctrlpipe (struct usb_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int spcp8x5_set_ctrlLine(struct usb_device *dev, u8 value,
				enum spcp8x5_type type)
{
	int retval;
	u8 mcr = 0 ;

	if (type == SPCP825_007_TYPE)
		return -EPERM;

	mcr = (unsigned short)value;
	retval = usb_control_msg(dev, usb_sndctrlpipe(dev, 0),
				 SET_UART_STATUS_TYPE, SET_UART_STATUS,
				 mcr, 0x04, NULL, 0, 100);
	if (retval != 0)
		dev_dbg(&dev->dev, "usb_control_msg return %#x\n", retval);
	return retval;
}