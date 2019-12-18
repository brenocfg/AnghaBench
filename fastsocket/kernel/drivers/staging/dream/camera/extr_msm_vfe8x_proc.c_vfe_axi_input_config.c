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
typedef  int uint8_t ;
typedef  void* uint32_t ;
struct vfe_cmd_axi_input_config {int pixelSize; int xOffset; int xSize; int rowIncrement; int /*<<< orphan*/  padBottomLineCount; int /*<<< orphan*/  padTopLineCount; int /*<<< orphan*/  padRightStopCycle3; int /*<<< orphan*/  padRightStopCycle2; int /*<<< orphan*/  padRightStopCycle1; int /*<<< orphan*/  padRightStopCycle0; int /*<<< orphan*/  padRightComponentSelectCycle3; int /*<<< orphan*/  padRightComponentSelectCycle2; int /*<<< orphan*/  padRightComponentSelectCycle1; int /*<<< orphan*/  padRightComponentSelectCycle0; int /*<<< orphan*/  padLeftStopCycle3; int /*<<< orphan*/  padLeftStopCycle2; int /*<<< orphan*/  padLeftStopCycle1; int /*<<< orphan*/  padLeftStopCycle0; int /*<<< orphan*/  padLeftComponentSelectCycle3; int /*<<< orphan*/  padLeftComponentSelectCycle2; int /*<<< orphan*/  padLeftComponentSelectCycle1; int /*<<< orphan*/  padLeftComponentSelectCycle0; int /*<<< orphan*/  padRepeatCountBottom; int /*<<< orphan*/  padRepeatCountTop; int /*<<< orphan*/  padRepeatCountRight; int /*<<< orphan*/  padRepeatCountLeft; int /*<<< orphan*/  unpackPhase; scalar_t__ unpackHbi; int /*<<< orphan*/  ySize; int /*<<< orphan*/  numOfRows; int /*<<< orphan*/ * fragAddr; } ;
struct VFE_AxiInputCmdType {int burstLength; int RowIncrement; int mainUnpackWidth; int /*<<< orphan*/  bottomUnapckPattern; int /*<<< orphan*/  topUnapckPattern; int /*<<< orphan*/  rightUnpackStop3; int /*<<< orphan*/  rightUnpackStop2; int /*<<< orphan*/  rightUnpackStop1; int /*<<< orphan*/  rightUnpackStop0; int /*<<< orphan*/  rightUnpackPattern3; int /*<<< orphan*/  rightUnpackPattern2; int /*<<< orphan*/  rightUnpackPattern1; int /*<<< orphan*/  rightUnpackPattern0; int /*<<< orphan*/  leftUnpackStop3; int /*<<< orphan*/  leftUnpackStop2; int /*<<< orphan*/  leftUnpackStop1; int /*<<< orphan*/  leftUnpackStop0; int /*<<< orphan*/  leftUnpackPattern3; int /*<<< orphan*/  leftUnpackPattern2; int /*<<< orphan*/  leftUnpackPattern1; int /*<<< orphan*/  leftUnpackPattern0; int /*<<< orphan*/  padBottom; int /*<<< orphan*/  padTop; int /*<<< orphan*/  padRight; int /*<<< orphan*/  padLeft; void* unpackPattern; int /*<<< orphan*/  mainUnpackPhase; void* mainUnpackHbiSel; int /*<<< orphan*/  mainUnpackHeight; int /*<<< orphan*/  NumOfRows; void* xSizeWord; scalar_t__ yOffsetDelta; int /*<<< orphan*/  ySize; int /*<<< orphan*/  stripeStartAddr3; int /*<<< orphan*/  stripeStartAddr2; int /*<<< orphan*/  stripeStartAddr1; int /*<<< orphan*/  stripeStartAddr0; } ;
typedef  int /*<<< orphan*/  cmd ;
struct TYPE_3__ {int /*<<< orphan*/  rdPingpongIrq; } ;
struct TYPE_4__ {int axiInputDataSize; scalar_t__ vfebase; TYPE_1__ vfeImaskLocal; } ;

/* Variables and functions */
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ VFE_BUS_PINGPONG_IRQ_EN ; 
 scalar_t__ VFE_BUS_STRIPE_RD_ADDR_0 ; 
#define  VFE_RAW_PIXEL_DATA_SIZE_10BIT 130 
#define  VFE_RAW_PIXEL_DATA_SIZE_12BIT 129 
#define  VFE_RAW_PIXEL_DATA_SIZE_8BIT 128 
 TYPE_2__* ctrl ; 
 int /*<<< orphan*/  memset (struct VFE_AxiInputCmdType*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  vfe_prog_hw (scalar_t__,void**,int) ; 
 int /*<<< orphan*/  writel (void*,scalar_t__) ; 

void vfe_axi_input_config(struct vfe_cmd_axi_input_config *in)
{
	struct VFE_AxiInputCmdType cmd;
	uint32_t xSizeWord, axiRdUnpackPattern;
	uint8_t  axiInputPpw;
	uint32_t busPingpongRdIrqEnable;

	ctrl->vfeImaskLocal.rdPingpongIrq = TRUE;

	switch (in->pixelSize) {
	case VFE_RAW_PIXEL_DATA_SIZE_10BIT:
		ctrl->axiInputDataSize = VFE_RAW_PIXEL_DATA_SIZE_10BIT;
		break;

	case VFE_RAW_PIXEL_DATA_SIZE_12BIT:
		ctrl->axiInputDataSize = VFE_RAW_PIXEL_DATA_SIZE_12BIT;
		break;

	case VFE_RAW_PIXEL_DATA_SIZE_8BIT:
	default:
		ctrl->axiInputDataSize = VFE_RAW_PIXEL_DATA_SIZE_8BIT;
		break;
	}

	memset(&cmd, 0, sizeof(cmd));

	switch (in->pixelSize) {
	case VFE_RAW_PIXEL_DATA_SIZE_10BIT:
		axiInputPpw = 6;
		axiRdUnpackPattern = 0xD43210;
		break;

	case VFE_RAW_PIXEL_DATA_SIZE_12BIT:
		axiInputPpw = 5;
		axiRdUnpackPattern = 0xC3210;
		break;

	case VFE_RAW_PIXEL_DATA_SIZE_8BIT:
	default:
		axiInputPpw = 8;
		axiRdUnpackPattern = 0xF6543210;
		break;
	}

	xSizeWord =
		((((in->xOffset % axiInputPpw) + in->xSize) +
			(axiInputPpw-1)) / axiInputPpw) - 1;

	cmd.stripeStartAddr0  = in->fragAddr[0];
	cmd.stripeStartAddr1  = in->fragAddr[1];
	cmd.stripeStartAddr2  = in->fragAddr[2];
	cmd.stripeStartAddr3  = in->fragAddr[3];
	cmd.ySize             = in->ySize;
	cmd.yOffsetDelta      = 0;
	cmd.xSizeWord         = xSizeWord;
	cmd.burstLength       = 1;
	cmd.NumOfRows         = in->numOfRows;
	cmd.RowIncrement      =
		(in->rowIncrement + (axiInputPpw-1))/axiInputPpw;
	cmd.mainUnpackHeight  = in->ySize;
	cmd.mainUnpackWidth   = in->xSize - 1;
	cmd.mainUnpackHbiSel  = (uint32_t)in->unpackHbi;
	cmd.mainUnpackPhase   = in->unpackPhase;
	cmd.unpackPattern     = axiRdUnpackPattern;
	cmd.padLeft           = in->padRepeatCountLeft;
	cmd.padRight          = in->padRepeatCountRight;
	cmd.padTop            = in->padRepeatCountTop;
	cmd.padBottom         = in->padRepeatCountBottom;
	cmd.leftUnpackPattern0   = in->padLeftComponentSelectCycle0;
	cmd.leftUnpackPattern1   = in->padLeftComponentSelectCycle1;
	cmd.leftUnpackPattern2   = in->padLeftComponentSelectCycle2;
	cmd.leftUnpackPattern3   = in->padLeftComponentSelectCycle3;
	cmd.leftUnpackStop0      = in->padLeftStopCycle0;
	cmd.leftUnpackStop1      = in->padLeftStopCycle1;
	cmd.leftUnpackStop2      = in->padLeftStopCycle2;
	cmd.leftUnpackStop3      = in->padLeftStopCycle3;
	cmd.rightUnpackPattern0  = in->padRightComponentSelectCycle0;
	cmd.rightUnpackPattern1  = in->padRightComponentSelectCycle1;
	cmd.rightUnpackPattern2  = in->padRightComponentSelectCycle2;
	cmd.rightUnpackPattern3  = in->padRightComponentSelectCycle3;
	cmd.rightUnpackStop0     = in->padRightStopCycle0;
	cmd.rightUnpackStop1     = in->padRightStopCycle1;
	cmd.rightUnpackStop2     = in->padRightStopCycle2;
	cmd.rightUnpackStop3     = in->padRightStopCycle3;
	cmd.topUnapckPattern     = in->padTopLineCount;
	cmd.bottomUnapckPattern  = in->padBottomLineCount;

	/*  program vfe_bus_cfg */
	vfe_prog_hw(ctrl->vfebase + VFE_BUS_STRIPE_RD_ADDR_0,
		(uint32_t *)&cmd, sizeof(cmd));

	/* hacking code, put it to default value */
	busPingpongRdIrqEnable = 0xf;

	writel(busPingpongRdIrqEnable,
		ctrl->vfebase + VFE_BUS_PINGPONG_IRQ_EN);
}