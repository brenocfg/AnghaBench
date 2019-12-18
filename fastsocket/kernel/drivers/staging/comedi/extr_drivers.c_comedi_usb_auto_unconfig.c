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
struct usb_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  comedi_auto_unconfig (int /*<<< orphan*/ *) ; 

void comedi_usb_auto_unconfig(struct usb_device *usbdev)
{
	BUG_ON(usbdev == NULL);
	comedi_auto_unconfig(&usbdev->dev);
}