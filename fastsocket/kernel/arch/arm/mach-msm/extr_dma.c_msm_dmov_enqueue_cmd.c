#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct msm_dmov_cmd {int /*<<< orphan*/  list; int /*<<< orphan*/  cmdptr; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMOV_CMD_PTR (unsigned int) ; 
 int /*<<< orphan*/  DMOV_CONFIG (unsigned int) ; 
 int /*<<< orphan*/  DMOV_CONFIG_IRQ_EN ; 
 int /*<<< orphan*/  DMOV_STATUS (unsigned int) ; 
 unsigned int DMOV_STATUS_CMD_PTR_RDY ; 
 int /*<<< orphan*/  INT_ADM_AARM ; 
 int /*<<< orphan*/  PRINT_ERROR (char*,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  PRINT_FLOW (char*,unsigned int) ; 
 int /*<<< orphan*/  PRINT_IO (char*,unsigned int,unsigned int) ; 
 int /*<<< orphan*/ * active_commands ; 
 unsigned int channel_active ; 
 int /*<<< orphan*/  enable_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  msm_dmov_lock ; 
 unsigned int readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ready_commands ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void msm_dmov_enqueue_cmd(unsigned id, struct msm_dmov_cmd *cmd)
{
	unsigned long irq_flags;
	unsigned int status;

	spin_lock_irqsave(&msm_dmov_lock, irq_flags);
	status = readl(DMOV_STATUS(id));
	if (list_empty(&ready_commands[id]) &&
		(status & DMOV_STATUS_CMD_PTR_RDY)) {
#if 0
		if (list_empty(&active_commands[id])) {
			PRINT_FLOW("msm_dmov_enqueue_cmd(%d), enable interrupt\n", id);
			writel(DMOV_CONFIG_IRQ_EN, DMOV_CONFIG(id));
		}
#endif
		PRINT_IO("msm_dmov_enqueue_cmd(%d), start command, status %x\n", id, status);
		list_add_tail(&cmd->list, &active_commands[id]);
		if (!channel_active)
			enable_irq(INT_ADM_AARM);
		channel_active |= 1U << id;
		writel(cmd->cmdptr, DMOV_CMD_PTR(id));
	} else {
		if (list_empty(&active_commands[id]))
			PRINT_ERROR("msm_dmov_enqueue_cmd(%d), error datamover stalled, status %x\n", id, status);

		PRINT_IO("msm_dmov_enqueue_cmd(%d), enqueue command, status %x\n", id, status);
		list_add_tail(&cmd->list, &ready_commands[id]);
	}
	spin_unlock_irqrestore(&msm_dmov_lock, irq_flags);
}