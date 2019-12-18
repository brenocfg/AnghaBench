#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int nmodes; struct gspca_ctrl* ctrls; TYPE_1__* cam_mode; } ;
struct gspca_dev {int curr_mode; TYPE_3__* sd_desc; TYPE_2__ cam; int /*<<< orphan*/  pixfmt; int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
struct gspca_ctrl {int /*<<< orphan*/  def; int /*<<< orphan*/  val; } ;
struct TYPE_6__ {int nctrls; } ;
struct TYPE_4__ {int /*<<< orphan*/  pixelformat; int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;

/* Variables and functions */

__attribute__((used)) static void gspca_set_default_mode(struct gspca_dev *gspca_dev)
{
	struct gspca_ctrl *ctrl;
	int i;

	i = gspca_dev->cam.nmodes - 1;	/* take the highest mode */
	gspca_dev->curr_mode = i;
	gspca_dev->width = gspca_dev->cam.cam_mode[i].width;
	gspca_dev->height = gspca_dev->cam.cam_mode[i].height;
	gspca_dev->pixfmt = gspca_dev->cam.cam_mode[i].pixelformat;

	/* set the current control values to their default values
	 * which may have changed in sd_init() */
	ctrl = gspca_dev->cam.ctrls;
	if (ctrl != NULL) {
		for (i = 0;
		     i < gspca_dev->sd_desc->nctrls;
		     i++, ctrl++)
			ctrl->val = ctrl->def;
	}
}