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
struct usb_hcd {int dummy; } ;
struct sa1111_dev {int dummy; } ;

/* Variables and functions */
 struct usb_hcd* sa1111_get_drvdata (struct sa1111_dev*) ; 
 int /*<<< orphan*/  usb_hcd_sa1111_remove (struct usb_hcd*,struct sa1111_dev*) ; 

__attribute__((used)) static int ohci_hcd_sa1111_drv_remove(struct sa1111_dev *dev)
{
	struct usb_hcd *hcd = sa1111_get_drvdata(dev);

	usb_hcd_sa1111_remove(hcd, dev);
	return 0;
}