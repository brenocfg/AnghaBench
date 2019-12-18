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
struct sd {int freq; } ;
struct gspca_dev {int dummy; } ;

/* Variables and functions */
 int sccb_read (struct gspca_dev*,int) ; 
 int /*<<< orphan*/  sccb_write (struct gspca_dev*,int,int) ; 

__attribute__((used)) static void setfreq(struct gspca_dev *gspca_dev)
{
	struct sd *sd = (struct sd *) gspca_dev;
	u8 val;

	val = sccb_read(gspca_dev, 0x13);		/* com8 */
	sccb_write(gspca_dev, 0xff, 0x00);
	if (sd->freq == 0) {
		sccb_write(gspca_dev, 0x13, val & 0xdf);
		return;
	}
	sccb_write(gspca_dev, 0x13, val | 0x20);

	val = sccb_read(gspca_dev, 0x42);		/* com17 */
	sccb_write(gspca_dev, 0xff, 0x00);
	if (sd->freq == 1)
		val |= 0x01;
	else
		val &= 0xfe;
	sccb_write(gspca_dev, 0x42, val);
}