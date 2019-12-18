#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {TYPE_1__* cam_mode; } ;
struct gspca_dev {size_t curr_mode; int* usb_buf; TYPE_2__ cam; } ;
typedef  int __u8 ;
struct TYPE_3__ {int priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  D_ERR ; 
 int /*<<< orphan*/  PDEBUG (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * cxjpeg_176 ; 
 int /*<<< orphan*/ * cxjpeg_320 ; 
 int /*<<< orphan*/ * cxjpeg_352 ; 
 int /*<<< orphan*/ * cxjpeg_640 ; 
 int /*<<< orphan*/ * cxjpeg_qtable ; 
 int /*<<< orphan*/  reg10 ; 
 int /*<<< orphan*/  reg12 ; 
 int /*<<< orphan*/  reg51 ; 
 int reg70 ; 
 int /*<<< orphan*/  regE5_8 ; 
 int /*<<< orphan*/  regE5a ; 
 int /*<<< orphan*/  regE5b ; 
 int /*<<< orphan*/  regE5c ; 
 int /*<<< orphan*/  reg_r (struct gspca_dev*,int,int) ; 
 int /*<<< orphan*/  reg_w (struct gspca_dev*,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  reg_w_val (struct gspca_dev*,int,int) ; 

__attribute__((used)) static void cx11646_jpeg(struct gspca_dev*gspca_dev)
{
	int i;
	int length;
	__u8 Reg55;
	int retry;

	reg_w_val(gspca_dev, 0x00c0, 0x01);
	reg_w_val(gspca_dev, 0x00c3, 0x00);
	reg_w_val(gspca_dev, 0x00c0, 0x00);
	reg_r(gspca_dev, 0x0001, 1);
	length = 8;
	switch (gspca_dev->cam.cam_mode[gspca_dev->curr_mode].priv) {
	case 0:
		for (i = 0; i < 27; i++) {
			if (i == 26)
				length = 2;
			reg_w(gspca_dev, 0x0008, cxjpeg_640[i], length);
		}
		Reg55 = 0x28;
		break;
	case 1:
		for (i = 0; i < 27; i++) {
			if (i == 26)
				length = 2;
			reg_w(gspca_dev, 0x0008, cxjpeg_352[i], length);
		}
		Reg55 = 0x16;
		break;
	default:
/*	case 2: */
		for (i = 0; i < 27; i++) {
			if (i == 26)
				length = 2;
			reg_w(gspca_dev, 0x0008, cxjpeg_320[i], length);
		}
		Reg55 = 0x14;
		break;
	case 3:
		for (i = 0; i < 27; i++) {
			if (i == 26)
				length = 2;
			reg_w(gspca_dev, 0x0008, cxjpeg_176[i], length);
		}
		Reg55 = 0x0B;
		break;
	}

	reg_r(gspca_dev, 0x0002, 1);
	reg_w_val(gspca_dev, 0x0055, Reg55);
	reg_r(gspca_dev, 0x0002, 1);
	reg_w(gspca_dev, 0x0010, reg10, 2);
	reg_w_val(gspca_dev, 0x0054, 0x02);
	reg_w_val(gspca_dev, 0x0054, 0x01);
	reg_w_val(gspca_dev, 0x0000, 0x94);
	reg_w_val(gspca_dev, 0x0053, 0xc0);
	reg_w_val(gspca_dev, 0x00fc, 0xe1);
	reg_w_val(gspca_dev, 0x0000, 0x00);
	/* wait for completion */
	retry = 50;
	do {
		reg_r(gspca_dev, 0x0002, 1);
							/* 0x07 until 0x00 */
		if (gspca_dev->usb_buf[0] == 0x00)
			break;
		reg_w_val(gspca_dev, 0x0053, 0x00);
	} while (--retry);
	if (retry == 0)
		PDEBUG(D_ERR, "Damned Errors sending jpeg Table");
	/* send the qtable now */
	reg_r(gspca_dev, 0x0001, 1);		/* -> 0x18 */
	length = 8;
	for (i = 0; i < 18; i++) {
		if (i == 17)
			length = 2;
		reg_w(gspca_dev, 0x0008, cxjpeg_qtable[i], length);

	}
	reg_r(gspca_dev, 0x0002, 1);	/* 0x00 */
	reg_r(gspca_dev, 0x0053, 1);	/* 0x00 */
	reg_w_val(gspca_dev, 0x0054, 0x02);
	reg_w_val(gspca_dev, 0x0054, 0x01);
	reg_w_val(gspca_dev, 0x0000, 0x94);
	reg_w_val(gspca_dev, 0x0053, 0xc0);

	reg_r(gspca_dev, 0x0038, 1);		/* 0x40 */
	reg_r(gspca_dev, 0x0038, 1);		/* 0x40 */
	reg_r(gspca_dev, 0x001f, 1);		/* 0x38 */
	reg_w(gspca_dev, 0x0012, reg12, 5);
	reg_w(gspca_dev, 0x00e5, regE5_8, 8);
	reg_r(gspca_dev, 0x00e8, 8);
	reg_w(gspca_dev, 0x00e5, regE5a, 4);
	reg_r(gspca_dev, 0x00e8, 1);		/* 0x00 */
	reg_w_val(gspca_dev, 0x009a, 0x01);
	reg_w(gspca_dev, 0x00e5, regE5b, 4);
	reg_r(gspca_dev, 0x00e8, 1);		/* 0x00 */
	reg_w(gspca_dev, 0x00e5, regE5c, 4);
	reg_r(gspca_dev, 0x00e8, 1);		/* 0x00 */

	reg_w(gspca_dev, 0x0051, reg51, 2);
	reg_w(gspca_dev, 0x0010, reg10, 2);
	reg_w_val(gspca_dev, 0x0070, reg70);
}