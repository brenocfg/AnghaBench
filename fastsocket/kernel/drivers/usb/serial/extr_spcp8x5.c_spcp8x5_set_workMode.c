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
struct usb_device {int /*<<< orphan*/  dev; } ;
typedef  enum spcp8x5_type { ____Placeholder_spcp8x5_type } spcp8x5_type ;

/* Variables and functions */
 int /*<<< orphan*/  SET_WORKING_MODE ; 
 int /*<<< orphan*/  SET_WORKING_MODE_TYPE ; 
 int SPCP825_007_TYPE ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int,...) ; 
 int usb_control_msg (struct usb_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  usb_sndctrlpipe (struct usb_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void spcp8x5_set_workMode(struct usb_device *dev, u16 value,
				 u16 index, enum spcp8x5_type type)
{
	int ret;

	/* I return Permited not support here but seem inval device
	 * is more fix */
	if (type == SPCP825_007_TYPE)
		return;

	ret = usb_control_msg(dev, usb_sndctrlpipe(dev, 0),
			      SET_WORKING_MODE_TYPE, SET_WORKING_MODE,
			      value, index, NULL, 0, 100);
	dev_dbg(&dev->dev, "value = %#x , index = %#x\n", value, index);
	if (ret < 0)
		dev_dbg(&dev->dev,
			"RTSCTS usb_control_msg(enable flowctrl) = %d\n", ret);
}