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
struct sa1111_dev {int dummy; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  ohci_sa1111_hc_driver ; 
 scalar_t__ usb_disabled () ; 
 int usb_hcd_sa1111_probe (int /*<<< orphan*/ *,struct sa1111_dev*) ; 

__attribute__((used)) static int ohci_hcd_sa1111_drv_probe(struct sa1111_dev *dev)
{
	int ret;

	if (usb_disabled())
		return -ENODEV;

	ret = usb_hcd_sa1111_probe(&ohci_sa1111_hc_driver, dev);
	return ret;
}