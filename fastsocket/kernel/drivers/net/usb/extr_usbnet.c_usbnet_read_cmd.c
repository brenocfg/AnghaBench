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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct usbnet {int /*<<< orphan*/  intf; } ;

/* Variables and functions */
 int ENODEV ; 
 int __usbnet_read_cmd (struct usbnet*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 
 scalar_t__ usb_autopm_get_interface (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_autopm_put_interface (int /*<<< orphan*/ ) ; 

int usbnet_read_cmd(struct usbnet *dev, u8 cmd, u8 reqtype,
		    u16 value, u16 index, void *data, u16 size)
{
	int ret;

	if (usb_autopm_get_interface(dev->intf) < 0)
		return -ENODEV;
	ret = __usbnet_read_cmd(dev, cmd, reqtype, value, index,
				data, size);
	usb_autopm_put_interface(dev->intf);
	return ret;
}