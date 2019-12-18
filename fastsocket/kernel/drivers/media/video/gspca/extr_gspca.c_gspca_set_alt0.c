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
struct gspca_dev {scalar_t__ alt; int /*<<< orphan*/  iface; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  err (char*,int) ; 
 int usb_set_interface (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int gspca_set_alt0(struct gspca_dev *gspca_dev)
{
	int ret;

	if (gspca_dev->alt == 0)
		return 0;
	ret = usb_set_interface(gspca_dev->dev, gspca_dev->iface, 0);
	if (ret < 0)
		err("set alt 0 err %d", ret);
	return ret;
}