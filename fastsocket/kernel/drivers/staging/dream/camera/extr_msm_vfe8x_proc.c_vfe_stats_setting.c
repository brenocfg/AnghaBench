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
struct vfe_statsframe {int /*<<< orphan*/  histBusPriorityEn; int /*<<< orphan*/  awbBusPriorityEn; int /*<<< orphan*/  afBusPriorityEn; int /*<<< orphan*/  histBusPriority; int /*<<< orphan*/  awbBusPriority; int /*<<< orphan*/  afBusPriority; int /*<<< orphan*/  lastLine; int /*<<< orphan*/  lastPixel; } ;
struct vfe_cmd_stats_setting {int /*<<< orphan*/ * histBuffer; int /*<<< orphan*/ * awbBuffer; int /*<<< orphan*/ * afBuffer; int /*<<< orphan*/  histBusPrioritySelection; int /*<<< orphan*/  awbBusPrioritySelection; int /*<<< orphan*/  afBusPrioritySelection; int /*<<< orphan*/  histBusPriority; int /*<<< orphan*/  awbBusPriority; int /*<<< orphan*/  afBusPriority; int /*<<< orphan*/  frameVDimension; int /*<<< orphan*/  frameHDimension; } ;
struct vfe_busstats_wrprio {int /*<<< orphan*/  histBusPriorityEn; int /*<<< orphan*/  awbBusPriorityEn; int /*<<< orphan*/  afBusPriorityEn; int /*<<< orphan*/  histBusPriority; int /*<<< orphan*/  awbBusPriority; int /*<<< orphan*/  afBusPriority; int /*<<< orphan*/  lastLine; int /*<<< orphan*/  lastPixel; } ;
typedef  int /*<<< orphan*/  cmd2 ;
typedef  int /*<<< orphan*/  cmd1 ;
struct TYPE_5__ {int /*<<< orphan*/  nextFrameAddrBuf; int /*<<< orphan*/ * addressBuffer; } ;
struct TYPE_4__ {int /*<<< orphan*/  nextFrameAddrBuf; int /*<<< orphan*/ * addressBuffer; } ;
struct TYPE_6__ {scalar_t__ vfebase; TYPE_2__ awbStatsControl; TYPE_1__ afStatsControl; } ;

/* Variables and functions */
 scalar_t__ VFE_BUS_STATS_AF_WR_PING_ADDR ; 
 scalar_t__ VFE_BUS_STATS_AF_WR_PONG_ADDR ; 
 scalar_t__ VFE_BUS_STATS_AWB_WR_PING_ADDR ; 
 scalar_t__ VFE_BUS_STATS_AWB_WR_PONG_ADDR ; 
 scalar_t__ VFE_BUS_STATS_HIST_WR_PING_ADDR ; 
 scalar_t__ VFE_BUS_STATS_HIST_WR_PONG_ADDR ; 
 scalar_t__ VFE_BUS_STATS_WR_PRIORITY ; 
 scalar_t__ VFE_STATS_FRAME_SIZE ; 
 TYPE_3__* ctrl ; 
 int /*<<< orphan*/  memset (struct vfe_statsframe*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  vfe_prog_hw (scalar_t__,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

void vfe_stats_setting(struct vfe_cmd_stats_setting *in)
{
	struct vfe_statsframe cmd1;
	struct vfe_busstats_wrprio cmd2;

	memset(&cmd1, 0, sizeof(cmd1));
	memset(&cmd2, 0, sizeof(cmd2));

	ctrl->afStatsControl.addressBuffer[0] = in->afBuffer[0];
	ctrl->afStatsControl.addressBuffer[1] = in->afBuffer[1];
	ctrl->afStatsControl.nextFrameAddrBuf = in->afBuffer[2];

	ctrl->awbStatsControl.addressBuffer[0] = in->awbBuffer[0];
	ctrl->awbStatsControl.addressBuffer[1] = in->awbBuffer[1];
	ctrl->awbStatsControl.nextFrameAddrBuf = in->awbBuffer[2];

	cmd1.lastPixel = in->frameHDimension;
	cmd1.lastLine  = in->frameVDimension;
	vfe_prog_hw(ctrl->vfebase + VFE_STATS_FRAME_SIZE,
		(uint32_t *)&cmd1, sizeof(cmd1));

	cmd2.afBusPriority    = in->afBusPriority;
	cmd2.awbBusPriority   = in->awbBusPriority;
	cmd2.histBusPriority  = in->histBusPriority;
	cmd2.afBusPriorityEn  = in->afBusPrioritySelection;
	cmd2.awbBusPriorityEn = in->awbBusPrioritySelection;
	cmd2.histBusPriorityEn = in->histBusPrioritySelection;

	vfe_prog_hw(ctrl->vfebase + VFE_BUS_STATS_WR_PRIORITY,
		(uint32_t *)&cmd2, sizeof(cmd2));

	/* Program the bus ping pong address for statistics modules. */
	writel(in->afBuffer[0], ctrl->vfebase + VFE_BUS_STATS_AF_WR_PING_ADDR);
	writel(in->afBuffer[1], ctrl->vfebase + VFE_BUS_STATS_AF_WR_PONG_ADDR);
	writel(in->awbBuffer[0],
		ctrl->vfebase + VFE_BUS_STATS_AWB_WR_PING_ADDR);
	writel(in->awbBuffer[1],
		ctrl->vfebase + VFE_BUS_STATS_AWB_WR_PONG_ADDR);
	writel(in->histBuffer[0],
		ctrl->vfebase + VFE_BUS_STATS_HIST_WR_PING_ADDR);
	writel(in->histBuffer[1],
		ctrl->vfebase + VFE_BUS_STATS_HIST_WR_PONG_ADDR);
}