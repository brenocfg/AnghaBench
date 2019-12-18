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
struct TYPE_2__ {int vfeFrameSkipCount; int vfeFrameSkipPattern; scalar_t__ vfeSnapShotCount; int vfeFrameSkipPeriod; scalar_t__ vfebase; scalar_t__ vfeOperationMode; int /*<<< orphan*/  vfeFrameId; } ;

/* Variables and functions */
 scalar_t__ CAMIF_COMMAND ; 
 int /*<<< orphan*/  CAMIF_COMMAND_STOP_AT_FRAME_BOUNDARY ; 
 int /*<<< orphan*/  CDBG (char*,int /*<<< orphan*/ ) ; 
 TYPE_1__* ctrl ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void vfe_process_camif_sof_irq(void)
{
	/* increment the frame id number. */
	ctrl->vfeFrameId++;

	CDBG("camif_sof_irq, frameId = %d\n",
		ctrl->vfeFrameId);

	/* In snapshot mode, if frame skip is programmed,
	* need to check it accordingly to stop camif at
	* correct frame boundary. For the dropped frames,
	* there won't be any output path irqs, but there is
	* still SOF irq, which can help us determine when
	* to stop the camif.
	*/
	if (ctrl->vfeOperationMode) {
		if ((1 << ctrl->vfeFrameSkipCount) &
				ctrl->vfeFrameSkipPattern) {

			ctrl->vfeSnapShotCount--;
			if (ctrl->vfeSnapShotCount == 0)
				/* terminate vfe pipeline at frame boundary. */
				writel(CAMIF_COMMAND_STOP_AT_FRAME_BOUNDARY,
					ctrl->vfebase + CAMIF_COMMAND);
		}

		/* update frame skip counter for bit checking. */
		ctrl->vfeFrameSkipCount++;
		if (ctrl->vfeFrameSkipCount ==
				(ctrl->vfeFrameSkipPeriod + 1))
			ctrl->vfeFrameSkipCount = 0;
	}
}