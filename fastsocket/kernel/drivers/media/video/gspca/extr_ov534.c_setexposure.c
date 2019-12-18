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
typedef  int u8 ;
struct sd {int exposure; scalar_t__ aec; } ;
struct gspca_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  sccb_reg_write (struct gspca_dev*,int,int) ; 

__attribute__((used)) static void setexposure(struct gspca_dev *gspca_dev)
{
	struct sd *sd = (struct sd *) gspca_dev;
	u8 val;

	if (sd->aec)
		return;

	/* 'val' is one byte and represents half of the exposure value we are
	 * going to set into registers, a two bytes value:
	 *
	 *    MSB: ((u16) val << 1) >> 8   == val >> 7
	 *    LSB: ((u16) val << 1) & 0xff == val << 1
	 */
	val = sd->exposure;
	sccb_reg_write(gspca_dev, 0x08, val >> 7);
	sccb_reg_write(gspca_dev, 0x10, val << 1);
}