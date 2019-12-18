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
typedef  int /*<<< orphan*/  uint32_t ;
struct vfe_statsaxw_hdr_cfg {int /*<<< orphan*/  axwHeader; int /*<<< orphan*/  awbYMax; int /*<<< orphan*/  awbYMin; int /*<<< orphan*/  aeSubregionCfg; int /*<<< orphan*/  aeRegionCfg; int /*<<< orphan*/  c4; int /*<<< orphan*/  c3; int /*<<< orphan*/  c2; int /*<<< orphan*/  c1; int /*<<< orphan*/  m4; int /*<<< orphan*/  m3; int /*<<< orphan*/  m2; int /*<<< orphan*/  m1; } ;
struct vfe_statsawbae_update {int /*<<< orphan*/  axwHeader; int /*<<< orphan*/  awbYMax; int /*<<< orphan*/  awbYMin; int /*<<< orphan*/  aeSubregionCfg; int /*<<< orphan*/  aeRegionCfg; int /*<<< orphan*/  c4; int /*<<< orphan*/  c3; int /*<<< orphan*/  c2; int /*<<< orphan*/  c1; int /*<<< orphan*/  m4; int /*<<< orphan*/  m3; int /*<<< orphan*/  m2; int /*<<< orphan*/  m1; } ;
struct vfe_statsawb_update {int /*<<< orphan*/  axwHeader; int /*<<< orphan*/  awbYMax; int /*<<< orphan*/  awbYMin; int /*<<< orphan*/  aeSubregionCfg; int /*<<< orphan*/  aeRegionCfg; int /*<<< orphan*/  c4; int /*<<< orphan*/  c3; int /*<<< orphan*/  c2; int /*<<< orphan*/  c1; int /*<<< orphan*/  m4; int /*<<< orphan*/  m3; int /*<<< orphan*/  m2; int /*<<< orphan*/  m1; } ;
struct vfe_cmd_stats_wb_exp_start {int /*<<< orphan*/  axwHeader; int /*<<< orphan*/  awbYMax; int /*<<< orphan*/  awbYMin; int /*<<< orphan*/  wbExpSubRegion; int /*<<< orphan*/  wbExpRegions; int /*<<< orphan*/ * awbCCFG; int /*<<< orphan*/ * awbMCFG; int /*<<< orphan*/  enable; } ;
typedef  int /*<<< orphan*/  cmd3 ;
typedef  int /*<<< orphan*/  cmd2 ;
typedef  int /*<<< orphan*/  cmd ;
struct TYPE_5__ {int /*<<< orphan*/  awbPingpongIrq; } ;
struct TYPE_4__ {int /*<<< orphan*/  axwEnable; } ;
struct TYPE_6__ {scalar_t__ vfebase; TYPE_2__ vfeImaskLocal; TYPE_1__ vfeStatsCmdLocal; } ;

/* Variables and functions */
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ VFE_STATS_AWBAE_CFG ; 
 scalar_t__ VFE_STATS_AWB_MCFG ; 
 scalar_t__ VFE_STATS_AXW_HEADER ; 
 TYPE_3__* ctrl ; 
 int /*<<< orphan*/  memset (struct vfe_statsaxw_hdr_cfg*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  vfe_prog_hw (scalar_t__,int /*<<< orphan*/ *,int) ; 

void vfe_stats_start_wb_exp(struct vfe_cmd_stats_wb_exp_start *in)
{
	struct vfe_statsawb_update   cmd;
	struct vfe_statsawbae_update cmd2;
	struct vfe_statsaxw_hdr_cfg  cmd3;

	ctrl->vfeStatsCmdLocal.axwEnable   =  in->enable;
	ctrl->vfeImaskLocal.awbPingpongIrq = TRUE;

	memset(&cmd, 0, sizeof(cmd));
	memset(&cmd2, 0, sizeof(cmd2));
	memset(&cmd3, 0, sizeof(cmd3));

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

	cmd2.aeRegionCfg     = in->wbExpRegions;
	cmd2.aeSubregionCfg  = in->wbExpSubRegion;
	cmd2.awbYMin         = in->awbYMin;
	cmd2.awbYMax         = in->awbYMax;
	vfe_prog_hw(ctrl->vfebase + VFE_STATS_AWBAE_CFG,
		(uint32_t *)&cmd2, sizeof(cmd2));

	cmd3.axwHeader       = in->axwHeader;
	vfe_prog_hw(ctrl->vfebase + VFE_STATS_AXW_HEADER,
		(uint32_t *)&cmd3, sizeof(cmd3));
}