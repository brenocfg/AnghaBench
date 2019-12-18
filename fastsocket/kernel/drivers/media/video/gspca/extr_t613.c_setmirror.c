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
struct sd {scalar_t__ mirror; } ;
struct gspca_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  reg_w_buf (struct gspca_dev*,int*,int) ; 

__attribute__((used)) static void setmirror(struct gspca_dev *gspca_dev)
{
	struct sd *sd = (struct sd *) gspca_dev;
	u8 hflipcmd[8] =
		{0x62, 0x07, 0x63, 0x03, 0x64, 0x00, 0x60, 0x09};

	if (sd->mirror)
		hflipcmd[3] = 0x01;

	reg_w_buf(gspca_dev, hflipcmd, sizeof hflipcmd);
}