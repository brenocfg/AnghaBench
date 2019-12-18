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
struct TYPE_4__ {int /*<<< orphan*/  rowEnd; int /*<<< orphan*/  rowStart; int /*<<< orphan*/  colEnd; int /*<<< orphan*/  colStart; } ;
struct TYPE_6__ {int /*<<< orphan*/  yuvOrder; int /*<<< orphan*/  subSample; int /*<<< orphan*/  videoSize; } ;
struct TYPE_5__ {TYPE_1__ roi; TYPE_3__ format; } ;
struct sd {TYPE_2__ params; } ;
struct gspca_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPIA_COMMAND_SetFormat ; 
 int /*<<< orphan*/  CPIA_COMMAND_SetROI ; 
 int do_command (struct gspca_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int command_setformat(struct gspca_dev *gspca_dev)
{
	struct sd *sd = (struct sd *) gspca_dev;
	int ret;

	ret = do_command(gspca_dev, CPIA_COMMAND_SetFormat,
			 sd->params.format.videoSize,
			 sd->params.format.subSample,
			 sd->params.format.yuvOrder, 0);
	if (ret)
		return ret;

	return do_command(gspca_dev, CPIA_COMMAND_SetROI,
			  sd->params.roi.colStart, sd->params.roi.colEnd,
			  sd->params.roi.rowStart, sd->params.roi.rowEnd);
}