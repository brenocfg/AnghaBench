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
typedef  int /*<<< orphan*/  uint32_t ;
struct vfe_cmds_camif_frame {int /*<<< orphan*/  linesPerFrame; int /*<<< orphan*/  pixelsPerLine; } ;
struct vfe_camifframe_update {int /*<<< orphan*/  linesPerFrame; int /*<<< orphan*/  pixelsPerLine; } ;
typedef  int /*<<< orphan*/  cmd ;
struct TYPE_2__ {scalar_t__ vfebase; } ;

/* Variables and functions */
 scalar_t__ CAMIF_FRAME_CONFIG ; 
 TYPE_1__* ctrl ; 
 int /*<<< orphan*/  memset (struct vfe_camifframe_update*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  vfe_prog_hw (scalar_t__,int /*<<< orphan*/ *,int) ; 

void vfe_camif_frame_update(struct vfe_cmds_camif_frame *in)
{
	struct vfe_camifframe_update cmd;

	memset(&cmd, 0, sizeof(cmd));

	cmd.pixelsPerLine = in->pixelsPerLine;
	cmd.linesPerFrame = in->linesPerFrame;

	vfe_prog_hw(ctrl->vfebase + CAMIF_FRAME_CONFIG, (uint32_t *)&cmd,
		sizeof(cmd));
}