#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_9__ ;
typedef  struct TYPE_17__   TYPE_8__ ;
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_17__ {scalar_t__ enable; scalar_t__ lineindex; } ;
struct TYPE_16__ {scalar_t__ enable; scalar_t__ lineindex; } ;
struct TYPE_15__ {int /*<<< orphan*/  pixelskipwrap; int /*<<< orphan*/  frameskipmode; int /*<<< orphan*/  frameskip; int /*<<< orphan*/  lineskipmask; int /*<<< orphan*/  pixelskipmask; } ;
struct TYPE_14__ {scalar_t__ firstpixel; scalar_t__ lastpixel; scalar_t__ firstline; scalar_t__ lastline; } ;
struct TYPE_13__ {scalar_t__ pixelsPerLine; scalar_t__ linesPerFrame; } ;
struct TYPE_12__ {int /*<<< orphan*/  efsstartofframe; int /*<<< orphan*/  efsendofframe; int /*<<< orphan*/  efsstartofline; int /*<<< orphan*/  efsendofline; } ;
struct vfe_cmd_camif_config {TYPE_8__ epoch2; TYPE_7__ epoch1; TYPE_6__ subsample; TYPE_5__ window; TYPE_4__ frame; TYPE_3__ EFS; int /*<<< orphan*/  camifConfig; } ;
struct vfe_camifcfg {scalar_t__ frameConfigPixelsPerLine; scalar_t__ frameConfigLinesPerFrame; scalar_t__ windowWidthCfgLastPixel; scalar_t__ windowWidthCfgFirstPixel; scalar_t__ windowHeightCfglastLine; scalar_t__ windowHeightCfgfirstLine; scalar_t__ epoch1Line; scalar_t__ epoch2Line; int /*<<< orphan*/  subsample2CfgPixelSkipWrap; int /*<<< orphan*/  subsample2CfgFrameSkipMode; int /*<<< orphan*/  subsample2CfgFrameSkip; int /*<<< orphan*/  subsample1CfgLineSkip; int /*<<< orphan*/  subsample1CfgPixelSkip; int /*<<< orphan*/  efsStartOfFrame; int /*<<< orphan*/  efsEndOfFrame; int /*<<< orphan*/  efsStartOfLine; int /*<<< orphan*/  efsEndOfLine; } ;
typedef  int /*<<< orphan*/  cmd ;
struct TYPE_11__ {int /*<<< orphan*/  camifCfgFromCmd; } ;
struct TYPE_10__ {int camifEpoch1Irq; int camifEpoch2Irq; } ;
struct TYPE_18__ {scalar_t__ vfebase; TYPE_2__ vfeCamifConfigLocal; TYPE_1__ vfeImaskLocal; } ;

/* Variables and functions */
 scalar_t__ CAMIF_EFS_CONFIG ; 
 int /*<<< orphan*/  CDBG (char*,scalar_t__) ; 
 scalar_t__ TRUE ; 
 TYPE_9__* ctrl ; 
 int /*<<< orphan*/  memset (struct vfe_camifcfg*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  vfe_prog_hw (scalar_t__,int /*<<< orphan*/ *,int) ; 

void vfe_camif_config(struct vfe_cmd_camif_config *in)
{
	struct vfe_camifcfg cmd;
	memset(&cmd, 0, sizeof(cmd));

	CDBG("camif.frame pixelsPerLine = %d\n", in->frame.pixelsPerLine);
	CDBG("camif.frame linesPerFrame = %d\n", in->frame.linesPerFrame);
	CDBG("camif.window firstpixel = %d\n", in->window.firstpixel);
	CDBG("camif.window lastpixel = %d\n",  in->window.lastpixel);
	CDBG("camif.window firstline = %d\n",  in->window.firstline);
	CDBG("camif.window lastline = %d\n",   in->window.lastline);

	/* determine if epoch interrupt needs to be enabled.  */
	if ((in->epoch1.enable == TRUE) &&
			(in->epoch1.lineindex <=
			 in->frame.linesPerFrame))
		ctrl->vfeImaskLocal.camifEpoch1Irq = 1;

	if ((in->epoch2.enable == TRUE) &&
			(in->epoch2.lineindex <=
			 in->frame.linesPerFrame)) {
		ctrl->vfeImaskLocal.camifEpoch2Irq = 1;
	}

	/*  save the content to program CAMIF_CONFIG seperately. */
	ctrl->vfeCamifConfigLocal.camifCfgFromCmd = in->camifConfig;

	/* EFS_Config */
	cmd.efsEndOfLine     = in->EFS.efsendofline;
	cmd.efsStartOfLine   = in->EFS.efsstartofline;
	cmd.efsEndOfFrame    = in->EFS.efsendofframe;
	cmd.efsStartOfFrame  = in->EFS.efsstartofframe;

	/* Frame Config */
	cmd.frameConfigPixelsPerLine = in->frame.pixelsPerLine;
	cmd.frameConfigLinesPerFrame = in->frame.linesPerFrame;

	/* Window Width Config */
	cmd.windowWidthCfgLastPixel  = in->window.lastpixel;
	cmd.windowWidthCfgFirstPixel = in->window.firstpixel;

	/* Window Height Config */
	cmd.windowHeightCfglastLine   = in->window.lastline;
	cmd.windowHeightCfgfirstLine  = in->window.firstline;

	/* Subsample 1 Config */
	cmd.subsample1CfgPixelSkip = in->subsample.pixelskipmask;
	cmd.subsample1CfgLineSkip  = in->subsample.lineskipmask;

	/* Subsample 2 Config */
	cmd.subsample2CfgFrameSkip      = in->subsample.frameskip;
	cmd.subsample2CfgFrameSkipMode  = in->subsample.frameskipmode;
	cmd.subsample2CfgPixelSkipWrap  = in->subsample.pixelskipwrap;

	/* Epoch Interrupt */
	cmd.epoch1Line = in->epoch1.lineindex;
	cmd.epoch2Line = in->epoch2.lineindex;

	vfe_prog_hw(ctrl->vfebase + CAMIF_EFS_CONFIG,
		(uint32_t *)&cmd, sizeof(cmd));
}