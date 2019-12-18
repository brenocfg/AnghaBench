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
struct vfe_statsaf_update {int /*<<< orphan*/  entry33; int /*<<< orphan*/  entry32; int /*<<< orphan*/  entry31; int /*<<< orphan*/  entry30; int /*<<< orphan*/  entry23; int /*<<< orphan*/  entry22; int /*<<< orphan*/  entry21; int /*<<< orphan*/  entry20; int /*<<< orphan*/  entry13; int /*<<< orphan*/  entry12; int /*<<< orphan*/  entry11; int /*<<< orphan*/  entry10; int /*<<< orphan*/  entry03; int /*<<< orphan*/  entry02; int /*<<< orphan*/  entry01; int /*<<< orphan*/  entry00; int /*<<< orphan*/  afHeader; int /*<<< orphan*/  fvMetric; int /*<<< orphan*/  fvMax; int /*<<< orphan*/  a24; int /*<<< orphan*/  a23; int /*<<< orphan*/  a22; int /*<<< orphan*/  a21; int /*<<< orphan*/  a20; int /*<<< orphan*/  a04; int /*<<< orphan*/  a00; int /*<<< orphan*/  windowWidth; int /*<<< orphan*/  windowHeight; int /*<<< orphan*/  windowMode; int /*<<< orphan*/  windowHOffset; int /*<<< orphan*/  windowVOffset; } ;
struct vfe_statsaf_cfg {int /*<<< orphan*/  entry33; int /*<<< orphan*/  entry32; int /*<<< orphan*/  entry31; int /*<<< orphan*/  entry30; int /*<<< orphan*/  entry23; int /*<<< orphan*/  entry22; int /*<<< orphan*/  entry21; int /*<<< orphan*/  entry20; int /*<<< orphan*/  entry13; int /*<<< orphan*/  entry12; int /*<<< orphan*/  entry11; int /*<<< orphan*/  entry10; int /*<<< orphan*/  entry03; int /*<<< orphan*/  entry02; int /*<<< orphan*/  entry01; int /*<<< orphan*/  entry00; int /*<<< orphan*/  afHeader; int /*<<< orphan*/  fvMetric; int /*<<< orphan*/  fvMax; int /*<<< orphan*/  a24; int /*<<< orphan*/  a23; int /*<<< orphan*/  a22; int /*<<< orphan*/  a21; int /*<<< orphan*/  a20; int /*<<< orphan*/  a04; int /*<<< orphan*/  a00; int /*<<< orphan*/  windowWidth; int /*<<< orphan*/  windowHeight; int /*<<< orphan*/  windowMode; int /*<<< orphan*/  windowHOffset; int /*<<< orphan*/  windowVOffset; } ;
struct vfe_cmd_stats_af_start {int /*<<< orphan*/ * gridForMultiWindows; int /*<<< orphan*/  bufferHeader; int /*<<< orphan*/  metricSelection; int /*<<< orphan*/  metricMax; int /*<<< orphan*/ * highPassCoef; int /*<<< orphan*/  windowWidth; int /*<<< orphan*/  windowHeight; int /*<<< orphan*/  windowMode; int /*<<< orphan*/  windowHOffset; int /*<<< orphan*/  windowVOffset; int /*<<< orphan*/  enable; } ;
typedef  int /*<<< orphan*/  cmd2 ;
typedef  int /*<<< orphan*/  cmd ;
struct TYPE_5__ {int /*<<< orphan*/  afPingpongIrq; } ;
struct TYPE_4__ {int /*<<< orphan*/  autoFocusEnable; } ;
struct TYPE_6__ {scalar_t__ vfebase; TYPE_2__ vfeImaskLocal; TYPE_1__ vfeStatsCmdLocal; } ;

/* Variables and functions */
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ VFE_STATS_AF_CFG ; 
 scalar_t__ VFE_STATS_AF_GRID_0 ; 
 TYPE_3__* ctrl ; 
 int /*<<< orphan*/  memset (struct vfe_statsaf_update*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  vfe_prog_hw (scalar_t__,int /*<<< orphan*/ *,int) ; 

void vfe_stats_start_af(struct vfe_cmd_stats_af_start *in)
{
	struct vfe_statsaf_update cmd;
	struct vfe_statsaf_cfg    cmd2;

	memset(&cmd, 0, sizeof(cmd));
	memset(&cmd2, 0, sizeof(cmd2));

ctrl->vfeStatsCmdLocal.autoFocusEnable = in->enable;
ctrl->vfeImaskLocal.afPingpongIrq = TRUE;

	cmd.windowVOffset = in->windowVOffset;
	cmd.windowHOffset = in->windowHOffset;
	cmd.windowMode    = in->windowMode;
	cmd.windowHeight  = in->windowHeight;
	cmd.windowWidth   = in->windowWidth;

	vfe_prog_hw(ctrl->vfebase + VFE_STATS_AF_CFG,
		(uint32_t *)&cmd, sizeof(cmd));

	cmd2.a00       = in->highPassCoef[0];
	cmd2.a04       = in->highPassCoef[1];
	cmd2.a20       = in->highPassCoef[2];
	cmd2.a21       = in->highPassCoef[3];
	cmd2.a22       = in->highPassCoef[4];
	cmd2.a23       = in->highPassCoef[5];
	cmd2.a24       = in->highPassCoef[6];
	cmd2.fvMax     = in->metricMax;
	cmd2.fvMetric  = in->metricSelection;
	cmd2.afHeader  = in->bufferHeader;
	cmd2.entry00   = in->gridForMultiWindows[0];
	cmd2.entry01   = in->gridForMultiWindows[1];
	cmd2.entry02   = in->gridForMultiWindows[2];
	cmd2.entry03   = in->gridForMultiWindows[3];
	cmd2.entry10   = in->gridForMultiWindows[4];
	cmd2.entry11   = in->gridForMultiWindows[5];
	cmd2.entry12   = in->gridForMultiWindows[6];
	cmd2.entry13   = in->gridForMultiWindows[7];
	cmd2.entry20   = in->gridForMultiWindows[8];
	cmd2.entry21   = in->gridForMultiWindows[9];
	cmd2.entry22   = in->gridForMultiWindows[10];
	cmd2.entry23   = in->gridForMultiWindows[11];
	cmd2.entry30   = in->gridForMultiWindows[12];
	cmd2.entry31   = in->gridForMultiWindows[13];
	cmd2.entry32   = in->gridForMultiWindows[14];
	cmd2.entry33   = in->gridForMultiWindows[15];

	vfe_prog_hw(ctrl->vfebase + VFE_STATS_AF_GRID_0,
		(uint32_t *)&cmd2, sizeof(cmd2));
}