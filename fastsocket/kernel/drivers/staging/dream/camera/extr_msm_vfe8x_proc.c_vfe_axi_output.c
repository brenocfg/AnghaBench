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
typedef  void* uint32_t ;
typedef  int uint16_t ;
struct TYPE_15__ {int /*<<< orphan*/ * addressBuffer; } ;
struct TYPE_13__ {int /*<<< orphan*/ * addressBuffer; } ;
struct vfe_output_path_combo {TYPE_6__ cbcrPath; TYPE_4__ yPath; } ;
struct TYPE_16__ {int imageWidth; int outRowIncrement; int /*<<< orphan*/  outRowCount; int /*<<< orphan*/  imageHeight; } ;
struct TYPE_14__ {int imageWidth; int outRowIncrement; int /*<<< orphan*/  outRowCount; int /*<<< orphan*/  imageHeight; } ;
struct TYPE_17__ {TYPE_7__ outputCbcr; TYPE_5__ outputY; } ;
struct TYPE_11__ {int imageWidth; int outRowIncrement; int /*<<< orphan*/  outRowCount; int /*<<< orphan*/  imageHeight; } ;
struct TYPE_10__ {int imageWidth; int outRowIncrement; int /*<<< orphan*/  outRowCount; int /*<<< orphan*/  imageHeight; } ;
struct TYPE_12__ {TYPE_2__ outputCbcr; TYPE_1__ outputY; } ;
struct vfe_cmd_axi_output_config {TYPE_8__ output1; TYPE_3__ output2; } ;
struct vfe_axi_out_cfg {int out2YImageWidthin64bit; int out2YRowIncrementIn64bit; int out2CbcrImageWidthIn64bit; int out2CbcrRowIncrementIn64bit; int out1YImageWidthin64bit; int out1YRowIncrementIn64bit; int out1CbcrImageWidthIn64bit; int out1CbcrRowIncrementIn64bit; int /*<<< orphan*/  out1CbcrNumRows; void* out1CbcrBurstLength; int /*<<< orphan*/  out1CbcrImageHeight; int /*<<< orphan*/  out1CbcrPongAddr; int /*<<< orphan*/  out1CbcrPingAddr; int /*<<< orphan*/  out1YNumRows; void* out1YBurstLength; int /*<<< orphan*/  out1YImageHeight; int /*<<< orphan*/  out1YPongAddr; int /*<<< orphan*/  out1YPingAddr; int /*<<< orphan*/  out2CbcrNumRows; void* out2CbcrBurstLength; int /*<<< orphan*/  out2CbcrImageHeight; int /*<<< orphan*/  out2CbcrPongAddr; int /*<<< orphan*/  out2CbcrPingAddr; int /*<<< orphan*/  out2YNumRows; void* out2YBurstLength; int /*<<< orphan*/  out2YImageHeight; int /*<<< orphan*/  out2YPongAddr; int /*<<< orphan*/  out2YPingAddr; } ;
typedef  int /*<<< orphan*/  cmd ;
struct TYPE_18__ {scalar_t__ vfebase; } ;

/* Variables and functions */
 scalar_t__ VFE_BUS_ENC_Y_WR_PING_ADDR ; 
 TYPE_9__* ctrl ; 
 int /*<<< orphan*/  vfe_prog_hw (scalar_t__,void**,int) ; 

__attribute__((used)) static void vfe_axi_output(struct vfe_cmd_axi_output_config *in,
	struct vfe_output_path_combo *out1,
	struct vfe_output_path_combo *out2, uint16_t out)
{
	struct vfe_axi_out_cfg cmd;

	uint16_t temp;
	uint32_t burstLength;

	/* force it to burst length 4, hardware does not support it. */
	burstLength = 1;

	/* AXI Output 2 Y Configuration*/
	/* VFE_BUS_ENC_Y_WR_PING_ADDR  */
	cmd.out2YPingAddr = out2->yPath.addressBuffer[0];

	/* VFE_BUS_ENC_Y_WR_PONG_ADDR  */
	cmd.out2YPongAddr = out2->yPath.addressBuffer[1];

	/* VFE_BUS_ENC_Y_WR_IMAGE_SIZE */
	cmd.out2YImageHeight = in->output2.outputY.imageHeight;
	/* convert the image width and row increment to be in
	 * unit of 64bit (8 bytes) */
	temp = (in->output2.outputY.imageWidth + (out - 1)) /
		out;
	cmd.out2YImageWidthin64bit = temp;

	/* VFE_BUS_ENC_Y_WR_BUFFER_CFG */
	cmd.out2YBurstLength = burstLength;
	cmd.out2YNumRows = in->output2.outputY.outRowCount;
	temp = (in->output2.outputY.outRowIncrement + (out - 1)) /
		out;
	cmd.out2YRowIncrementIn64bit = temp;

	/* AXI Output 2 Cbcr Configuration*/
	/* VFE_BUS_ENC_Cbcr_WR_PING_ADDR  */
	cmd.out2CbcrPingAddr = out2->cbcrPath.addressBuffer[0];

	/* VFE_BUS_ENC_Cbcr_WR_PONG_ADDR  */
	cmd.out2CbcrPongAddr = out2->cbcrPath.addressBuffer[1];

	/* VFE_BUS_ENC_Cbcr_WR_IMAGE_SIZE */
	cmd.out2CbcrImageHeight = in->output2.outputCbcr.imageHeight;
	temp = (in->output2.outputCbcr.imageWidth + (out - 1)) /
		out;
	cmd.out2CbcrImageWidthIn64bit = temp;

	/* VFE_BUS_ENC_Cbcr_WR_BUFFER_CFG */
	cmd.out2CbcrBurstLength = burstLength;
	cmd.out2CbcrNumRows = in->output2.outputCbcr.outRowCount;
	temp = (in->output2.outputCbcr.outRowIncrement + (out - 1)) /
		out;
	cmd.out2CbcrRowIncrementIn64bit = temp;

	/* AXI Output 1 Y Configuration */
	/* VFE_BUS_VIEW_Y_WR_PING_ADDR  */
	cmd.out1YPingAddr = out1->yPath.addressBuffer[0];

	/* VFE_BUS_VIEW_Y_WR_PONG_ADDR */
	cmd.out1YPongAddr = out1->yPath.addressBuffer[1];

	/* VFE_BUS_VIEW_Y_WR_IMAGE_SIZE */
	cmd.out1YImageHeight = in->output1.outputY.imageHeight;
	temp = (in->output1.outputY.imageWidth + (out - 1)) /
		out;
	cmd.out1YImageWidthin64bit = temp;

	/* VFE_BUS_VIEW_Y_WR_BUFFER_CFG     */
	cmd.out1YBurstLength = burstLength;
	cmd.out1YNumRows = in->output1.outputY.outRowCount;

	temp =
		(in->output1.outputY.outRowIncrement +
		 (out - 1)) / out;
	cmd.out1YRowIncrementIn64bit = temp;

	/* AXI Output 1 Cbcr Configuration*/
	cmd.out1CbcrPingAddr = out1->cbcrPath.addressBuffer[0];

	/* VFE_BUS_VIEW_Cbcr_WR_PONG_ADDR  */
	cmd.out1CbcrPongAddr =
		out1->cbcrPath.addressBuffer[1];

	/* VFE_BUS_VIEW_Cbcr_WR_IMAGE_SIZE */
	cmd.out1CbcrImageHeight = in->output1.outputCbcr.imageHeight;
	temp = (in->output1.outputCbcr.imageWidth +
		(out - 1)) / out;
	cmd.out1CbcrImageWidthIn64bit = temp;

	cmd.out1CbcrBurstLength = burstLength;
	cmd.out1CbcrNumRows = in->output1.outputCbcr.outRowCount;
	temp =
		(in->output1.outputCbcr.outRowIncrement +
		 (out - 1)) / out;

	cmd.out1CbcrRowIncrementIn64bit = temp;

	vfe_prog_hw(ctrl->vfebase + VFE_BUS_ENC_Y_WR_PING_ADDR,
		(uint32_t *)&cmd, sizeof(cmd));
}