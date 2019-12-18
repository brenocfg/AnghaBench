#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct vfe_cmd_bus_pm_start {scalar_t__ output2YWrPmEnable; scalar_t__ output2CbcrWrPmEnable; scalar_t__ output1YWrPmEnable; scalar_t__ output1CbcrWrPmEnable; } ;
struct TYPE_6__ {void* pmEnabled; } ;
struct TYPE_5__ {void* pmEnabled; } ;
struct TYPE_7__ {scalar_t__ encYWrPathEn; scalar_t__ encCbcrWrPathEn; scalar_t__ viewYWrPathEn; scalar_t__ viewCbcrWrPathEn; } ;
struct TYPE_8__ {scalar_t__ vfebase; TYPE_2__ encPath; TYPE_1__ viewPath; TYPE_3__ vfeBusConfigLocal; } ;

/* Variables and functions */
 void* TRUE ; 
 scalar_t__ VFE_BUS_PM_CMD ; 
 int /*<<< orphan*/  VFE_PERFORMANCE_MONITOR_GO ; 
 TYPE_4__* ctrl ; 
 int /*<<< orphan*/  vfe_pm_start (struct vfe_cmd_bus_pm_start*) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void vfe_8k_pm_start(struct vfe_cmd_bus_pm_start *in)
{
	in->output1CbcrWrPmEnable = ctrl->vfeBusConfigLocal.viewCbcrWrPathEn;
	in->output1YWrPmEnable    = ctrl->vfeBusConfigLocal.viewYWrPathEn;
	in->output2CbcrWrPmEnable = ctrl->vfeBusConfigLocal.encCbcrWrPathEn;
	in->output2YWrPmEnable    = ctrl->vfeBusConfigLocal.encYWrPathEn;

	if (in->output1CbcrWrPmEnable || in->output1YWrPmEnable)
		ctrl->viewPath.pmEnabled = TRUE;

	if (in->output2CbcrWrPmEnable || in->output2YWrPmEnable)
		ctrl->encPath.pmEnabled = TRUE;

	vfe_pm_start(in);

	writel(VFE_PERFORMANCE_MONITOR_GO, ctrl->vfebase + VFE_BUS_PM_CMD);
}