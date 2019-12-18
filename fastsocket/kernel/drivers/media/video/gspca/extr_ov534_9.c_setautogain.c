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
struct sd {scalar_t__ autogain; } ;
struct gspca_dev {int dummy; } ;

/* Variables and functions */
 int sccb_read (struct gspca_dev*,int) ; 
 int /*<<< orphan*/  sccb_write (struct gspca_dev*,int,int) ; 

__attribute__((used)) static void setautogain(struct gspca_dev *gspca_dev)
{
	struct sd *sd = (struct sd *) gspca_dev;
	u8 val;

/*fixme: should adjust agc/awb/aec by different controls */
	val = sccb_read(gspca_dev, 0x13);		/* com8 */
	sccb_write(gspca_dev, 0xff, 0x00);
	if (sd->autogain)
		val |= 0x05;		/* agc & aec */
	else
		val &= 0xfa;
	sccb_write(gspca_dev, 0x13, val);
}