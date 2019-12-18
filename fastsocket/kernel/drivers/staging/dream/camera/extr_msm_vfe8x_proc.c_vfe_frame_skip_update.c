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
struct vfe_cmd_frame_skip_update {int /*<<< orphan*/  output2Pattern; int /*<<< orphan*/  output1Pattern; } ;
struct VFE_FRAME_SKIP_UpdateCmdType {int /*<<< orphan*/  cbcrPattern; int /*<<< orphan*/  yPattern; } ;
typedef  int /*<<< orphan*/  cmd ;
struct TYPE_2__ {scalar_t__ vfebase; } ;

/* Variables and functions */
 scalar_t__ VFE_FRAMEDROP_ENC_Y_PATTERN ; 
 scalar_t__ VFE_FRAMEDROP_VIEW_Y_PATTERN ; 
 TYPE_1__* ctrl ; 
 int /*<<< orphan*/  vfe_prog_hw (scalar_t__,int /*<<< orphan*/ *,int) ; 

void vfe_frame_skip_update(struct vfe_cmd_frame_skip_update *in)
{
	struct VFE_FRAME_SKIP_UpdateCmdType cmd;

	cmd.yPattern    = in->output1Pattern;
	cmd.cbcrPattern = in->output1Pattern;
	vfe_prog_hw(ctrl->vfebase + VFE_FRAMEDROP_VIEW_Y_PATTERN,
		(uint32_t *)&cmd, sizeof(cmd));

	cmd.yPattern    = in->output2Pattern;
	cmd.cbcrPattern = in->output2Pattern;
	vfe_prog_hw(ctrl->vfebase + VFE_FRAMEDROP_ENC_Y_PATTERN,
		(uint32_t *)&cmd, sizeof(cmd));
}