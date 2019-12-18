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
typedef  int /*<<< orphan*/  uint32_t ;
struct vfe_cmd_bus_pm_start {int /*<<< orphan*/  output1CbcrWrPmEnable; int /*<<< orphan*/  output1YWrPmEnable; int /*<<< orphan*/  output2CbcrWrPmEnable; int /*<<< orphan*/  output2YWrPmEnable; } ;
struct VFE_Bus_Pm_ConfigCmdType {int /*<<< orphan*/  output1CbcrWrPmEnable; int /*<<< orphan*/  output1YWrPmEnable; int /*<<< orphan*/  output2CbcrWrPmEnable; int /*<<< orphan*/  output2YWrPmEnable; } ;
typedef  int /*<<< orphan*/  cmd ;
struct TYPE_2__ {scalar_t__ vfebase; } ;

/* Variables and functions */
 scalar_t__ VFE_BUS_PM_CFG ; 
 TYPE_1__* ctrl ; 
 int /*<<< orphan*/  memset (struct VFE_Bus_Pm_ConfigCmdType*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  vfe_prog_hw (scalar_t__,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void vfe_pm_start(struct vfe_cmd_bus_pm_start *in)
{
	struct VFE_Bus_Pm_ConfigCmdType cmd;
	memset(&cmd, 0, sizeof(struct VFE_Bus_Pm_ConfigCmdType));

	cmd.output2YWrPmEnable     = in->output2YWrPmEnable;
	cmd.output2CbcrWrPmEnable  = in->output2CbcrWrPmEnable;
	cmd.output1YWrPmEnable     = in->output1YWrPmEnable;
	cmd.output1CbcrWrPmEnable  = in->output1CbcrWrPmEnable;

	vfe_prog_hw(ctrl->vfebase + VFE_BUS_PM_CFG,
		(uint32_t *)&cmd, sizeof(cmd));
}