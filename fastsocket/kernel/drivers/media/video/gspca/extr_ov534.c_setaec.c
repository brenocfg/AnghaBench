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
struct sd {scalar_t__ aec; } ;
struct gspca_dev {int dummy; } ;

/* Variables and functions */
 int sccb_reg_read (struct gspca_dev*,int) ; 
 int /*<<< orphan*/  sccb_reg_write (struct gspca_dev*,int,int) ; 
 int /*<<< orphan*/  setexposure (struct gspca_dev*) ; 

__attribute__((used)) static void setaec(struct gspca_dev *gspca_dev)
{
	struct sd *sd = (struct sd *) gspca_dev;

	if (sd->aec)
		sccb_reg_write(gspca_dev, 0x13,
				sccb_reg_read(gspca_dev, 0x13) | 0x01);
	else {
		sccb_reg_write(gspca_dev, 0x13,
				sccb_reg_read(gspca_dev, 0x13) & ~0x01);
		setexposure(gspca_dev);
	}
}