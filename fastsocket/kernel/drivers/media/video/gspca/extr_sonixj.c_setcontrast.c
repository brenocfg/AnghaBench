#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct sd {TYPE_1__* ctrls; } ;
struct gspca_dev {int dummy; } ;
struct TYPE_2__ {int val; } ;

/* Variables and functions */
 size_t CONTRAST ; 
 int CONTRAST_MAX ; 
 int /*<<< orphan*/  reg_w (struct gspca_dev*,int,int*,int) ; 

__attribute__((used)) static void setcontrast(struct gspca_dev *gspca_dev)
{
	struct sd *sd = (struct sd *) gspca_dev;
	u8 k2;
	u8 contrast[6];

	k2 = sd->ctrls[CONTRAST].val * 0x30 / (CONTRAST_MAX + 1)
				+ 0x10;		/* 10..40 */
	contrast[0] = (k2 + 1) / 2;		/* red */
	contrast[1] = 0;
	contrast[2] = k2;			/* green */
	contrast[3] = 0;
	contrast[4] = (k2 + 1) / 5;		/* blue */
	contrast[5] = 0;
	reg_w(gspca_dev, 0x84, contrast, sizeof contrast);
}