#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct mdp_info {int dummy; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_3__ {int /*<<< orphan*/  (* func ) (TYPE_1__*) ;} ;

/* Variables and functions */
 int DL0_DMA2_TERM_DONE ; 
 int DL0_ROI_DONE ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  MDP_INTR_CLEAR ; 
 int /*<<< orphan*/  MDP_INTR_STATUS ; 
 TYPE_1__* dma_callback ; 
 int /*<<< orphan*/  locked_disable_mdp_irq (struct mdp_info*,int) ; 
 int /*<<< orphan*/  mdp_dma2_waitqueue ; 
 int mdp_irq_mask ; 
 int /*<<< orphan*/  mdp_lock ; 
 int /*<<< orphan*/  mdp_ppp_waitqueue ; 
 int mdp_readl (struct mdp_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mdp_writel (struct mdp_info*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t mdp_isr(int irq, void *data)
{
	uint32_t status;
	unsigned long irq_flags;
	struct mdp_info *mdp = data;

	spin_lock_irqsave(&mdp_lock, irq_flags);

	status = mdp_readl(mdp, MDP_INTR_STATUS);
	mdp_writel(mdp, status, MDP_INTR_CLEAR);

	status &= mdp_irq_mask;
	if (status & DL0_DMA2_TERM_DONE) {
		if (dma_callback) {
			dma_callback->func(dma_callback);
			dma_callback = NULL;
		}
		wake_up(&mdp_dma2_waitqueue);
	}

	if (status & DL0_ROI_DONE)
		wake_up(&mdp_ppp_waitqueue);

	if (status)
		locked_disable_mdp_irq(mdp, status);

	spin_unlock_irqrestore(&mdp_lock, irq_flags);
	return IRQ_HANDLED;
}