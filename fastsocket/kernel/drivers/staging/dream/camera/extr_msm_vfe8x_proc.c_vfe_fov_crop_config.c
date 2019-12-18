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
struct vfe_fov_crop_cfg {int /*<<< orphan*/  firstLine; int /*<<< orphan*/  lastLine; int /*<<< orphan*/  firstPixel; int /*<<< orphan*/  lastPixel; } ;
struct vfe_cmd_fov_crop_config {int /*<<< orphan*/  firstLine; int /*<<< orphan*/  lastLine; int /*<<< orphan*/  firstPixel; int /*<<< orphan*/  lastPixel; int /*<<< orphan*/  enable; } ;
typedef  int /*<<< orphan*/  cmd ;
struct TYPE_3__ {int /*<<< orphan*/  cropEnable; } ;
struct TYPE_4__ {scalar_t__ vfebase; TYPE_1__ vfeModuleEnableLocal; } ;

/* Variables and functions */
 scalar_t__ VFE_CROP_WIDTH_CFG ; 
 TYPE_2__* ctrl ; 
 int /*<<< orphan*/  memset (struct vfe_fov_crop_cfg*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  vfe_prog_hw (scalar_t__,int /*<<< orphan*/ *,int) ; 

void vfe_fov_crop_config(struct vfe_cmd_fov_crop_config *in)
{
	struct vfe_fov_crop_cfg cmd;
	memset(&cmd, 0, sizeof(cmd));

	ctrl->vfeModuleEnableLocal.cropEnable = in->enable;

	/* FOV Corp, Part 1 */
	cmd.lastPixel  = in->lastPixel;
	cmd.firstPixel = in->firstPixel;

	/* FOV Corp, Part 2 */
	cmd.lastLine   = in->lastLine;
	cmd.firstLine  = in->firstLine;

	vfe_prog_hw(ctrl->vfebase + VFE_CROP_WIDTH_CFG,
		(uint32_t *)&cmd, sizeof(cmd));
}