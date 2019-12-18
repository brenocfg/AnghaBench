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
 int /*<<< orphan*/  D_ERR ; 
 int /*<<< orphan*/  PDEBUG (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stv_sndctrl (struct gspca_dev*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int stv0680_handle_error(struct gspca_dev *gspca_dev, int ret)
{
	stv_sndctrl(gspca_dev, 0, 0x80, 0, 0x02); /* Get Last Error */
	PDEBUG(D_ERR, "last error: %i,  command = 0x%x",
	       gspca_dev->usb_buf[0], gspca_dev->usb_buf[1]);
	return ret;
}