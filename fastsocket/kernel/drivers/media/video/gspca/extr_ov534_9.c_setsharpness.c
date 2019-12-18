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
struct sd {int sharpness; } ;
struct gspca_dev {int dummy; } ;
typedef  int s8 ;

/* Variables and functions */
 int sccb_read (struct gspca_dev*,int) ; 
 int /*<<< orphan*/  sccb_write (struct gspca_dev*,int,int) ; 

__attribute__((used)) static void setsharpness(struct gspca_dev *gspca_dev)
{
	struct sd *sd = (struct sd *) gspca_dev;
	s8 val;

	val = sd->sharpness;
	if (val < 0) {				/* auto */
		val = sccb_read(gspca_dev, 0x42);	/* com17 */
		sccb_write(gspca_dev, 0xff, 0x00);
		sccb_write(gspca_dev, 0x42, val | 0x40);
				/* Edge enhancement strength auto adjust */
		return;
	}
	if (val != 0)
		val = 1 << (val - 1);
	sccb_write(gspca_dev, 0x3f,	/* edge - edge enhance. factor */
			val);
	val = sccb_read(gspca_dev, 0x42);		/* com17 */
	sccb_write(gspca_dev, 0xff, 0x00);
	sccb_write(gspca_dev, 0x42, val & 0xbf);
}