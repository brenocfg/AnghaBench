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
struct gspca_dev {int /*<<< orphan*/ * usb_buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  D_PROBE ; 
 int /*<<< orphan*/  PDEBUG (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reg_r (struct gspca_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  reg_w (struct gspca_dev*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int sd_init(struct gspca_dev *gspca_dev)
{
	/* HDG not sure if these 2 reads are needed */
	reg_r(gspca_dev, 0, 0x10);
	PDEBUG(D_PROBE, "Reg 0x10 reads: %02x %02x",
	       gspca_dev->usb_buf[0], gspca_dev->usb_buf[1]);
	reg_r(gspca_dev, 0, 0x10);
	PDEBUG(D_PROBE, "Reg 0x10 reads: %02x %02x",
	       gspca_dev->usb_buf[0], gspca_dev->usb_buf[1]);
	reg_w(gspca_dev, 0, 0x0d);

	return 0;
}