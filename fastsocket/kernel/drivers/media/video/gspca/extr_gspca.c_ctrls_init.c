#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {struct gspca_ctrl* ctrls; } ;
struct gspca_dev {TYPE_4__* sd_desc; TYPE_1__ cam; } ;
struct gspca_ctrl {int /*<<< orphan*/  max; int /*<<< orphan*/  min; int /*<<< orphan*/  def; int /*<<< orphan*/  val; } ;
struct TYPE_8__ {int nctrls; TYPE_3__* ctrls; } ;
struct TYPE_6__ {int /*<<< orphan*/  maximum; int /*<<< orphan*/  minimum; int /*<<< orphan*/  default_value; } ;
struct TYPE_7__ {TYPE_2__ qctrl; } ;

/* Variables and functions */

__attribute__((used)) static void ctrls_init(struct gspca_dev *gspca_dev)
{
	struct gspca_ctrl *ctrl;
	int i;

	for (i = 0, ctrl = gspca_dev->cam.ctrls;
	     i < gspca_dev->sd_desc->nctrls;
	     i++, ctrl++) {
		ctrl->def = gspca_dev->sd_desc->ctrls[i].qctrl.default_value;
		ctrl->val = ctrl->def;
		ctrl->min = gspca_dev->sd_desc->ctrls[i].qctrl.minimum;
		ctrl->max = gspca_dev->sd_desc->ctrls[i].qctrl.maximum;
	}
}