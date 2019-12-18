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
struct sd {size_t effect; } ;
struct gspca_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  D_CONF ; 
 int /*<<< orphan*/  PDEBUG (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * effects_table ; 
 int /*<<< orphan*/  reg_w (struct gspca_dev*,int) ; 
 int /*<<< orphan*/  reg_w_buf (struct gspca_dev*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void seteffect(struct gspca_dev *gspca_dev)
{
	struct sd *sd = (struct sd *) gspca_dev;

	reg_w_buf(gspca_dev, effects_table[sd->effect],
				sizeof effects_table[0]);
	if (sd->effect == 1 || sd->effect == 5) {
		PDEBUG(D_CONF,
		       "This effect have been disabled for webcam \"safety\"");
		return;
	}

	if (sd->effect == 1 || sd->effect == 4)
		reg_w(gspca_dev, 0x4aa6);
	else
		reg_w(gspca_dev, 0xfaa6);
}