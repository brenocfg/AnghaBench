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
typedef  void* uint32_t ;
struct vfe_cmd_test_gen_start {int /*<<< orphan*/  testGenRandomSeed; int /*<<< orphan*/  colorBarsRotatePeriod; scalar_t__ colorBarsPixelPattern; int /*<<< orphan*/  colorBarsSplitEnable; int /*<<< orphan*/  unicolorBarEnable; int /*<<< orphan*/  unicolorBarSelect; int /*<<< orphan*/  endOfFrameDummyLine; int /*<<< orphan*/  startOfFrameDummyLine; int /*<<< orphan*/  vblEnable; int /*<<< orphan*/  vbl; int /*<<< orphan*/  hbi; int /*<<< orphan*/  endOfLineNOffset; int /*<<< orphan*/  startOfLineOffset; int /*<<< orphan*/  endOfFrameNOffset; int /*<<< orphan*/  startOfFrameOffset; int /*<<< orphan*/  imageHeight; int /*<<< orphan*/  imageWidth; scalar_t__ vsyncEdge; scalar_t__ hsyncEdge; scalar_t__ pixelDataSize; int /*<<< orphan*/  systematicDataSelect; int /*<<< orphan*/  pixelDataSelect; int /*<<< orphan*/  numFrame; } ;
struct VFE_TestGen_ConfigCmdType {int /*<<< orphan*/  randomSeed; int /*<<< orphan*/  rotatePeriod; void* pixelPattern; int /*<<< orphan*/  splitEnable; int /*<<< orphan*/  unicolorBarEnable; int /*<<< orphan*/  unicolorBarSelect; int /*<<< orphan*/  eofDummy; int /*<<< orphan*/  sofDummy; int /*<<< orphan*/  vBlankIntervalEnable; int /*<<< orphan*/  vBlankInterval; int /*<<< orphan*/  hBlankInterval; int /*<<< orphan*/  eolNOffset; int /*<<< orphan*/  solOffset; int /*<<< orphan*/  eofNOffset; int /*<<< orphan*/  sofOffset; int /*<<< orphan*/  imageHeight; int /*<<< orphan*/  imageWidth; void* vsyncEdge; void* hsyncEdge; void* pixelDataSize; int /*<<< orphan*/  systematicDataSelect; int /*<<< orphan*/  pixelDataSelect; int /*<<< orphan*/  numFrame; } ;
typedef  int /*<<< orphan*/  cmd ;
struct TYPE_2__ {scalar_t__ vfebase; } ;

/* Variables and functions */
 scalar_t__ VFE_HW_TESTGEN_CFG ; 
 TYPE_1__* ctrl ; 
 int /*<<< orphan*/  memset (struct VFE_TestGen_ConfigCmdType*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  vfe_prog_hw (scalar_t__,void**,int) ; 

void vfe_test_gen_start(struct vfe_cmd_test_gen_start *in)
{
	struct VFE_TestGen_ConfigCmdType cmd;

	memset(&cmd, 0, sizeof(cmd));

	cmd.numFrame              = in->numFrame;
	cmd.pixelDataSelect       = in->pixelDataSelect;
	cmd.systematicDataSelect  = in->systematicDataSelect;
	cmd.pixelDataSize         = (uint32_t)in->pixelDataSize;
	cmd.hsyncEdge             = (uint32_t)in->hsyncEdge;
	cmd.vsyncEdge             = (uint32_t)in->vsyncEdge;
	cmd.imageWidth            = in->imageWidth;
	cmd.imageHeight           = in->imageHeight;
	cmd.sofOffset             = in->startOfFrameOffset;
	cmd.eofNOffset            = in->endOfFrameNOffset;
	cmd.solOffset             = in->startOfLineOffset;
	cmd.eolNOffset            = in->endOfLineNOffset;
	cmd.hBlankInterval        = in->hbi;
	cmd.vBlankInterval        = in->vbl;
	cmd.vBlankIntervalEnable  = in->vblEnable;
	cmd.sofDummy              = in->startOfFrameDummyLine;
	cmd.eofDummy              = in->endOfFrameDummyLine;
	cmd.unicolorBarSelect     = in->unicolorBarSelect;
	cmd.unicolorBarEnable     = in->unicolorBarEnable;
	cmd.splitEnable           = in->colorBarsSplitEnable;
	cmd.pixelPattern          = (uint32_t)in->colorBarsPixelPattern;
	cmd.rotatePeriod          = in->colorBarsRotatePeriod;
	cmd.randomSeed            = in->testGenRandomSeed;

	vfe_prog_hw(ctrl->vfebase + VFE_HW_TESTGEN_CFG,
		(uint32_t *) &cmd, sizeof(cmd));
}