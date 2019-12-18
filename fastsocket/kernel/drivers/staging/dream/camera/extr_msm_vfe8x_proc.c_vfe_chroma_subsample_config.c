#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct vfe_cmd_chroma_subsample_config {int /*<<< orphan*/  cropHeightFirstLine; int /*<<< orphan*/  cropHeightLastLine; int /*<<< orphan*/  cropWidthFirstPixel; int /*<<< orphan*/  cropWidthLastPixel; int /*<<< orphan*/  cropEnable; int /*<<< orphan*/  vsubSampleEnable; int /*<<< orphan*/  hsubSampleEnable; int /*<<< orphan*/  vCosited; int /*<<< orphan*/  hCosited; int /*<<< orphan*/  vCositedPhase; int /*<<< orphan*/  hCositedPhase; int /*<<< orphan*/  enable; } ;
struct vfe_chromasubsample_cfg {int /*<<< orphan*/  cropHeightFirstLine; int /*<<< orphan*/  cropHeightLastLine; int /*<<< orphan*/  cropWidthFirstPixel; int /*<<< orphan*/  cropWidthLastPixel; int /*<<< orphan*/  cropEnable; int /*<<< orphan*/  vsubSampleEnable; int /*<<< orphan*/  hsubSampleEnable; int /*<<< orphan*/  vCosited; int /*<<< orphan*/  hCosited; int /*<<< orphan*/  vCositedPhase; int /*<<< orphan*/  hCositedPhase; } ;
typedef  int /*<<< orphan*/  cmd ;
struct TYPE_3__ {int /*<<< orphan*/  chromaSubsampleEnable; } ;
struct TYPE_4__ {scalar_t__ vfebase; TYPE_1__ vfeModuleEnableLocal; } ;

/* Variables and functions */
 scalar_t__ VFE_CHROMA_SUBSAMPLE_CFG ; 
 TYPE_2__* ctrl ; 
 int /*<<< orphan*/  memset (struct vfe_chromasubsample_cfg*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  vfe_prog_hw (scalar_t__,int /*<<< orphan*/ *,int) ; 

void vfe_chroma_subsample_config(
	struct vfe_cmd_chroma_subsample_config *in)
{
	struct vfe_chromasubsample_cfg cmd;
	memset(&cmd, 0, sizeof(cmd));

	ctrl->vfeModuleEnableLocal.chromaSubsampleEnable = in->enable;

	cmd.hCositedPhase       = in->hCositedPhase;
	cmd.vCositedPhase       = in->vCositedPhase;
	cmd.hCosited            = in->hCosited;
	cmd.vCosited            = in->vCosited;
	cmd.hsubSampleEnable    = in->hsubSampleEnable;
	cmd.vsubSampleEnable    = in->vsubSampleEnable;
	cmd.cropEnable          = in->cropEnable;
	cmd.cropWidthLastPixel  = in->cropWidthLastPixel;
	cmd.cropWidthFirstPixel = in->cropWidthFirstPixel;
	cmd.cropHeightLastLine  = in->cropHeightLastLine;
	cmd.cropHeightFirstLine = in->cropHeightFirstLine;

	vfe_prog_hw(ctrl->vfebase + VFE_CHROMA_SUBSAMPLE_CFG,
		(uint32_t *)&cmd, sizeof(cmd));
}