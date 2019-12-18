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
struct vfe_rolloff_cfg {int /*<<< orphan*/  yDeltaAccum; int /*<<< orphan*/  pixelY; int /*<<< orphan*/  pixelX; int /*<<< orphan*/  gridY; int /*<<< orphan*/  gridX; int /*<<< orphan*/  yDelta; int /*<<< orphan*/  gridHeight; int /*<<< orphan*/  gridWidth; } ;
struct vfe_cmd_roll_off_config {int /*<<< orphan*/  yDeltaAccum; int /*<<< orphan*/  gridPixelYIndex; int /*<<< orphan*/  gridPixelXIndex; int /*<<< orphan*/  gridYIndex; int /*<<< orphan*/  gridXIndex; int /*<<< orphan*/  yDelta; int /*<<< orphan*/  gridHeight; int /*<<< orphan*/  gridWidth; int /*<<< orphan*/  enable; } ;
typedef  int /*<<< orphan*/  cmd ;
struct TYPE_3__ {int /*<<< orphan*/  lensRollOffEnable; } ;
struct TYPE_4__ {scalar_t__ vfebase; TYPE_1__ vfeModuleEnableLocal; } ;

/* Variables and functions */
 scalar_t__ VFE_ROLLOFF_CFG_0 ; 
 TYPE_2__* ctrl ; 
 int /*<<< orphan*/  memset (struct vfe_rolloff_cfg*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  vfe_prog_hw (scalar_t__,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  vfe_write_lens_roll_off_table (struct vfe_cmd_roll_off_config*) ; 

void vfe_roll_off_config(struct vfe_cmd_roll_off_config *in)
{
	struct vfe_rolloff_cfg cmd;
	memset(&cmd, 0, sizeof(cmd));

	ctrl->vfeModuleEnableLocal.lensRollOffEnable = in->enable;

	cmd.gridWidth   = in->gridWidth;
	cmd.gridHeight  = in->gridHeight;
	cmd.yDelta      = in->yDelta;
	cmd.gridX       = in->gridXIndex;
	cmd.gridY       = in->gridYIndex;
	cmd.pixelX      = in->gridPixelXIndex;
	cmd.pixelY      = in->gridPixelYIndex;
	cmd.yDeltaAccum = in->yDeltaAccum;

	vfe_prog_hw(ctrl->vfebase + VFE_ROLLOFF_CFG_0,
		(uint32_t *)&cmd, sizeof(cmd));

	vfe_write_lens_roll_off_table(in);
}