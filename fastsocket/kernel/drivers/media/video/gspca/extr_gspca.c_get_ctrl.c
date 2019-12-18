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
struct gspca_dev {int ctrl_dis; TYPE_1__* sd_desc; } ;
struct TYPE_4__ {int id; } ;
struct ctrl {TYPE_2__ qctrl; } ;
struct TYPE_3__ {int nctrls; struct ctrl* ctrls; } ;

/* Variables and functions */

__attribute__((used)) static int get_ctrl(struct gspca_dev *gspca_dev,
				   int id)
{
	const struct ctrl *ctrls;
	int i;

	for (i = 0, ctrls = gspca_dev->sd_desc->ctrls;
	     i < gspca_dev->sd_desc->nctrls;
	     i++, ctrls++) {
		if (gspca_dev->ctrl_dis & (1 << i))
			continue;
		if (id == ctrls->qctrl.id)
			return i;
	}
	return -1;
}