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
struct vfe_frame_skip_cfg {int /*<<< orphan*/  output1CbCrPattern; int /*<<< orphan*/  output1YPattern; int /*<<< orphan*/  output1CbCrPeriod; int /*<<< orphan*/  output1YPeriod; int /*<<< orphan*/  output2CbCrPattern; int /*<<< orphan*/  output2YPattern; int /*<<< orphan*/  output2CbCrPeriod; int /*<<< orphan*/  output2YPeriod; } ;
struct vfe_cmd_frame_skip_config {int /*<<< orphan*/  output1Pattern; int /*<<< orphan*/  output1Period; int /*<<< orphan*/  output2Pattern; int /*<<< orphan*/  output2Period; } ;
typedef  int /*<<< orphan*/  cmd ;
struct TYPE_2__ {scalar_t__ vfebase; struct vfe_cmd_frame_skip_config vfeFrameSkip; } ;

/* Variables and functions */
 scalar_t__ VFE_FRAMEDROP_ENC_Y_CFG ; 
 TYPE_1__* ctrl ; 
 int /*<<< orphan*/  memset (struct vfe_frame_skip_cfg*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  vfe_prog_hw (scalar_t__,int /*<<< orphan*/ *,int) ; 

void vfe_frame_skip_config(struct vfe_cmd_frame_skip_config *in)
{
	struct vfe_frame_skip_cfg cmd;
	memset(&cmd, 0, sizeof(cmd));

	ctrl->vfeFrameSkip = *in;

	cmd.output2YPeriod     = in->output2Period;
	cmd.output2CbCrPeriod  = in->output2Period;
	cmd.output2YPattern    = in->output2Pattern;
	cmd.output2CbCrPattern = in->output2Pattern;
	cmd.output1YPeriod     = in->output1Period;
	cmd.output1CbCrPeriod  = in->output1Period;
	cmd.output1YPattern    = in->output1Pattern;
	cmd.output1CbCrPattern = in->output1Pattern;

	vfe_prog_hw(ctrl->vfebase + VFE_FRAMEDROP_ENC_Y_CFG,
		(uint32_t *)&cmd, sizeof(cmd));
}