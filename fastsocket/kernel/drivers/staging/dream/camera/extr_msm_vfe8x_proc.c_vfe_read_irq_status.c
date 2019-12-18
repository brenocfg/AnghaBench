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
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_6__ {void* cbcrWrPmStats1; void* cbcrWrPmStats0; void* yWrPmStats1; void* yWrPmStats0; } ;
struct TYPE_5__ {void* cbcrWrPmStats1; void* cbcrWrPmStats0; void* yWrPmStats1; void* yWrPmStats0; } ;
struct TYPE_7__ {TYPE_2__ viewPathPmInfo; TYPE_1__ encPathPmInfo; } ;
struct vfe_irq_thread_msg {TYPE_3__ pmInfo; void* camifStatus; void* vfeIrqStatus; } ;
struct TYPE_8__ {scalar_t__ vfebase; } ;

/* Variables and functions */
 scalar_t__ CAMIF_COMMAND ; 
 scalar_t__ CAMIF_STATUS ; 
 int /*<<< orphan*/  CDBG (char*,void*) ; 
 scalar_t__ VFE_IRQ_STATUS ; 
 TYPE_4__* ctrl ; 
 int /*<<< orphan*/  memset (struct vfe_irq_thread_msg*,int /*<<< orphan*/ ,int) ; 
 void* readl (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static inline void vfe_read_irq_status(struct vfe_irq_thread_msg *out)
{
	uint32_t *temp;

	memset(out, 0, sizeof(struct vfe_irq_thread_msg));

	temp = (uint32_t *)(ctrl->vfebase + VFE_IRQ_STATUS);
	out->vfeIrqStatus = readl(temp);

	temp = (uint32_t *)(ctrl->vfebase + CAMIF_STATUS);
	out->camifStatus = readl(temp);
	writel(0x7, ctrl->vfebase + CAMIF_COMMAND);
	writel(0x3, ctrl->vfebase + CAMIF_COMMAND);
	CDBG("camifStatus  = 0x%x\n", out->camifStatus);

/*
	temp = (uint32_t *)(ctrl->vfebase + VFE_DEMOSAIC_STATUS);
	out->demosaicStatus = readl(temp);

	temp = (uint32_t *)(ctrl->vfebase + VFE_ASF_MAX_EDGE);
	out->asfMaxEdge = readl(temp);

	temp = (uint32_t *)(ctrl->vfebase + VFE_BUS_ENC_Y_WR_PM_STATS_0);
*/

#if 0
	out->pmInfo.encPathPmInfo.yWrPmStats0      = readl(temp++);
	out->pmInfo.encPathPmInfo.yWrPmStats1      = readl(temp++);
	out->pmInfo.encPathPmInfo.cbcrWrPmStats0   = readl(temp++);
	out->pmInfo.encPathPmInfo.cbcrWrPmStats1   = readl(temp++);
	out->pmInfo.viewPathPmInfo.yWrPmStats0     = readl(temp++);
	out->pmInfo.viewPathPmInfo.yWrPmStats1     = readl(temp++);
	out->pmInfo.viewPathPmInfo.cbcrWrPmStats0  = readl(temp++);
	out->pmInfo.viewPathPmInfo.cbcrWrPmStats1  = readl(temp);
#endif /* if 0 Jeff */
}