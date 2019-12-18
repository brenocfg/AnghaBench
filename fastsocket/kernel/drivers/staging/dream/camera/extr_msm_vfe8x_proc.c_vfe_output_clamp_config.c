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
struct vfe_output_clamp_cfg {int /*<<< orphan*/  crChanMin; int /*<<< orphan*/  cbChanMin; int /*<<< orphan*/  yChanMin; int /*<<< orphan*/  crChanMax; int /*<<< orphan*/  cbChanMax; int /*<<< orphan*/  yChanMax; } ;
struct vfe_cmd_output_clamp_config {int /*<<< orphan*/  minCh2; int /*<<< orphan*/  minCh1; int /*<<< orphan*/  minCh0; int /*<<< orphan*/  maxCh2; int /*<<< orphan*/  maxCh1; int /*<<< orphan*/  maxCh0; } ;
typedef  int /*<<< orphan*/  cmd ;
struct TYPE_2__ {scalar_t__ vfebase; } ;

/* Variables and functions */
 scalar_t__ VFE_CLAMP_MAX_CFG ; 
 TYPE_1__* ctrl ; 
 int /*<<< orphan*/  memset (struct vfe_output_clamp_cfg*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  vfe_prog_hw (scalar_t__,int /*<<< orphan*/ *,int) ; 

void vfe_output_clamp_config(struct vfe_cmd_output_clamp_config *in)
{
	struct vfe_output_clamp_cfg cmd;
	memset(&cmd, 0, sizeof(cmd));

	cmd.yChanMax  = in->maxCh0;
	cmd.cbChanMax = in->maxCh1;
	cmd.crChanMax = in->maxCh2;

	cmd.yChanMin  = in->minCh0;
	cmd.cbChanMin = in->minCh1;
	cmd.crChanMin = in->minCh2;

	vfe_prog_hw(ctrl->vfebase + VFE_CLAMP_MAX_CFG, (uint32_t *)&cmd,
		sizeof(cmd));
}