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
 int /*<<< orphan*/  D_STREAM ; 
 int /*<<< orphan*/  PDEBUG (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reg_r (struct gspca_dev*,int,int) ; 
 int /*<<< orphan*/  reg_w (struct gspca_dev*,int,int,int) ; 

__attribute__((used)) static void sd_stopN(struct gspca_dev *gspca_dev)
{
	reg_w(gspca_dev, 0, 0x8003, 0x00);

	/* switch to video camera mode */
	reg_w(gspca_dev, 0x00, 0x8000, 0x0004);
	reg_r(gspca_dev, 0x8000, 1);
	PDEBUG(D_STREAM, "stop SPCA500 done reg8000: 0x%2x",
		gspca_dev->usb_buf[0]);
}