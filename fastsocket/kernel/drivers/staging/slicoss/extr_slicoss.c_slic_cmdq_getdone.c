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
struct TYPE_2__ {int /*<<< orphan*/  flags; int /*<<< orphan*/  lock; } ;
struct slic_cmdqueue {TYPE_1__ lock; scalar_t__ count; int /*<<< orphan*/ * tail; int /*<<< orphan*/ * head; } ;
struct adapter {struct slic_cmdqueue cmdq_free; struct slic_cmdqueue cmdq_done; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void slic_cmdq_getdone(struct adapter *adapter)
{
	struct slic_cmdqueue *done_cmdq = &adapter->cmdq_done;
	struct slic_cmdqueue *free_cmdq = &adapter->cmdq_free;

	ASSERT(free_cmdq->head == NULL);
	spin_lock_irqsave(&done_cmdq->lock.lock, done_cmdq->lock.flags);

	free_cmdq->head = done_cmdq->head;
	free_cmdq->count = done_cmdq->count;
	done_cmdq->head = NULL;
	done_cmdq->tail = NULL;
	done_cmdq->count = 0;
	spin_unlock_irqrestore(&done_cmdq->lock.lock, done_cmdq->lock.flags);
}