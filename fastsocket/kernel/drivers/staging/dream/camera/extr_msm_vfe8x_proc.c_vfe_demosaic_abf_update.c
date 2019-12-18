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
struct vfe_demosaic_cfg {int /*<<< orphan*/  abfShift; int /*<<< orphan*/  forceAbfOn; int /*<<< orphan*/  abfEnable; } ;
struct vfe_demosaic_abf_cfg {int /*<<< orphan*/  maxValue; int /*<<< orphan*/  minValue; int /*<<< orphan*/  ratio; int /*<<< orphan*/  lpThreshold; } ;
struct TYPE_3__ {int /*<<< orphan*/  max; int /*<<< orphan*/  min; int /*<<< orphan*/  ratio; int /*<<< orphan*/  lpThreshold; int /*<<< orphan*/  shift; int /*<<< orphan*/  forceOn; int /*<<< orphan*/  enable; } ;
struct vfe_cmd_demosaic_abf_update {TYPE_1__ abfUpdate; } ;
typedef  int /*<<< orphan*/  cmdabf ;
typedef  int /*<<< orphan*/  cmd ;
struct TYPE_4__ {scalar_t__ vfebase; } ;

/* Variables and functions */
 scalar_t__ VFE_DEMOSAIC_ABF_CFG_0 ; 
 scalar_t__ VFE_DEMOSAIC_CFG ; 
 TYPE_2__* ctrl ; 
 int /*<<< orphan*/  memset (struct vfe_demosaic_cfg*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  readl (scalar_t__) ; 
 int /*<<< orphan*/  vfe_prog_hw (scalar_t__,int /*<<< orphan*/ *,int) ; 

void vfe_demosaic_abf_update(struct vfe_cmd_demosaic_abf_update *in)
{
struct vfe_demosaic_cfg cmd;
	struct vfe_demosaic_abf_cfg cmdabf;
	uint32_t temp;

	memset(&cmd, 0, sizeof(cmd));
	temp = readl(ctrl->vfebase + VFE_DEMOSAIC_CFG);

	cmd = *((struct vfe_demosaic_cfg *)(&temp));
	cmd.abfEnable       = in->abfUpdate.enable;
	cmd.forceAbfOn      = in->abfUpdate.forceOn;
	cmd.abfShift        = in->abfUpdate.shift;
	vfe_prog_hw(ctrl->vfebase + VFE_DEMOSAIC_CFG,
		(uint32_t *)&cmd, sizeof(cmd));

	cmdabf.lpThreshold  = in->abfUpdate.lpThreshold;
	cmdabf.ratio        = in->abfUpdate.ratio;
	cmdabf.minValue     = in->abfUpdate.min;
	cmdabf.maxValue     = in->abfUpdate.max;
	vfe_prog_hw(ctrl->vfebase + VFE_DEMOSAIC_ABF_CFG_0,
		(uint32_t *)&cmdabf, sizeof(cmdabf));
}