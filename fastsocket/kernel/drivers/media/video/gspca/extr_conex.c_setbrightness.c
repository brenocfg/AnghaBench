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
struct sd {int brightness; int colors; } ;
struct gspca_dev {int dummy; } ;
typedef  int __u8 ;

/* Variables and functions */
 int* reg10 ; 
 int /*<<< orphan*/  reg70 ; 
 int* regE5c ; 
 int /*<<< orphan*/  reg_r (struct gspca_dev*,int,int) ; 
 int /*<<< orphan*/  reg_w (struct gspca_dev*,int,int*,int) ; 
 int /*<<< orphan*/  reg_w_val (struct gspca_dev*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void setbrightness(struct gspca_dev *gspca_dev)
{
	struct sd *sd = (struct sd *) gspca_dev;
	__u8 regE5cbx[] = { 0x88, 0x00, 0xd4, 0x01, 0x88, 0x01, 0x01, 0x01 };
	__u8 reg51c[2];
	__u8 bright;
	__u8 colors;

	bright = sd->brightness;
	regE5cbx[2] = bright;
	reg_w(gspca_dev, 0x00e5, regE5cbx, 8);
	reg_r(gspca_dev, 0x00e8, 8);
	reg_w(gspca_dev, 0x00e5, regE5c, 4);
	reg_r(gspca_dev, 0x00e8, 1);		/* 0x00 */

	colors = sd->colors;
	reg51c[0] = 0x77;
	reg51c[1] = colors;
	reg_w(gspca_dev, 0x0051, reg51c, 2);
	reg_w(gspca_dev, 0x0010, reg10, 2);
	reg_w_val(gspca_dev, 0x0070, reg70);
}