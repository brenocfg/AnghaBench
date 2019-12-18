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
struct gspca_dev {scalar_t__ nbalt; int /*<<< orphan*/  iface; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  err (char*) ; 
 int usb_set_interface (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int sd_isoc_init(struct gspca_dev *gspca_dev)
{
	int ret;

	ret = usb_set_interface(gspca_dev->dev, gspca_dev->iface,
		gspca_dev->nbalt - 1);
	if (ret < 0) {
		err("usb_set_interface failed");
		return ret;
	}
/*	reg_w(gspca_dev, 0x0003, 0x0002); */
	return 0;
}