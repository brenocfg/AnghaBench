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
struct vfe_statsawbae_update {int /*<<< orphan*/  awbYMax; int /*<<< orphan*/  awbYMin; int /*<<< orphan*/  aeSubregionCfg; int /*<<< orphan*/  aeRegionCfg; int /*<<< orphan*/  c4; int /*<<< orphan*/  c3; int /*<<< orphan*/  c2; int /*<<< orphan*/  c1; int /*<<< orphan*/  m4; int /*<<< orphan*/  m3; int /*<<< orphan*/  m2; int /*<<< orphan*/  m1; } ;
struct vfe_statsawb_update {int /*<<< orphan*/  awbYMax; int /*<<< orphan*/  awbYMin; int /*<<< orphan*/  aeSubregionCfg; int /*<<< orphan*/  aeRegionCfg; int /*<<< orphan*/  c4; int /*<<< orphan*/  c3; int /*<<< orphan*/  c2; int /*<<< orphan*/  c1; int /*<<< orphan*/  m4; int /*<<< orphan*/  m3; int /*<<< orphan*/  m2; int /*<<< orphan*/  m1; } ;
struct vfe_cmd_stats_wb_exp_update {int /*<<< orphan*/  awbYMax; int /*<<< orphan*/  awbYMin; int /*<<< orphan*/  wbExpSubRegion; int /*<<< orphan*/  wbExpRegions; int /*<<< orphan*/ * awbCCFG; int /*<<< orphan*/ * awbMCFG; } ;
typedef  int /*<<< orphan*/  cmd2 ;
typedef  int /*<<< orphan*/  cmd ;
struct TYPE_2__ {scalar_t__ vfebase; } ;

/* Variables and functions */
 scalar_t__ VFE_STATS_AWBAE_CFG ; 
 scalar_t__ VFE_STATS_AWB_MCFG ; 
 TYPE_1__* ctrl ; 
 int /*<<< orphan*/  memset (struct vfe_statsawbae_update*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  vfe_prog_hw (scalar_t__,int /*<<< orphan*/ *,int) ; 

void vfe_stats_update_wb_exp(struct vfe_cmd_stats_wb_exp_update *in)
{
	struct vfe_statsawb_update   cmd;
	struct vfe_statsawbae_update cmd2;

	memset(&cmd, 0, sizeof(cmd));
	memset(&cmd2, 0, sizeof(cmd2));

	cmd.m1  = in->awbMCFG[0];
	cmd.m2  = in->awbMCFG[1];
	cmd.m3  = in->awbMCFG[2];
	cmd.m4  = in->awbMCFG[3];
	cmd.c1  = in->awbCCFG[0];
	cmd.c2  = in->awbCCFG[1];
	cmd.c3  = in->awbCCFG[2];
	cmd.c4  = in->awbCCFG[3];
	vfe_prog_hw(ctrl->vfebase + VFE_STATS_AWB_MCFG,
		(uint32_t *)&cmd, sizeof(cmd));

	cmd2.aeRegionCfg    = in->wbExpRegions;
	cmd2.aeSubregionCfg = in->wbExpSubRegion;
	cmd2.awbYMin        = in->awbYMin;
	cmd2.awbYMax        = in->awbYMax;
	vfe_prog_hw(ctrl->vfebase + VFE_STATS_AWBAE_CFG,
		(uint32_t *)&cmd2, sizeof(cmd2));
}