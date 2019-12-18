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
struct txx9aclc_dmadata {scalar_t__ frag_count; scalar_t__ dmacount; int /*<<< orphan*/  dma_lock; int /*<<< orphan*/  tasklet; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  tasklet_schedule (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void txx9aclc_dma_complete(void *arg)
{
	struct txx9aclc_dmadata *dmadata = arg;
	unsigned long flags;

	/* dma completion handler cannot submit new operations */
	spin_lock_irqsave(&dmadata->dma_lock, flags);
	if (dmadata->frag_count >= 0) {
		dmadata->dmacount--;
		BUG_ON(dmadata->dmacount < 0);
		tasklet_schedule(&dmadata->tasklet);
	}
	spin_unlock_irqrestore(&dmadata->dma_lock, flags);
}