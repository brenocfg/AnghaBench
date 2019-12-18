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
typedef  size_t u8 ;
struct reply_pool {int* head; size_t current_entry; int wraparound; } ;
struct ctlr_info {size_t max_commands; int /*<<< orphan*/  lock; int /*<<< orphan*/  commands_outstanding; scalar_t__ vaddr; scalar_t__ msix_vector; scalar_t__ msi_vector; struct reply_pool* reply_queue; } ;

/* Variables and functions */
 unsigned long FIFO_EMPTY ; 
 scalar_t__ SA5_OUTDB_CLEAR ; 
 int /*<<< orphan*/  SA5_OUTDB_CLEAR_PERF_BIT ; 
 scalar_t__ SA5_OUTDB_STATUS ; 
 unsigned long readl (scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static unsigned long SA5_performant_completed(struct ctlr_info *h, u8 q)
{
	struct reply_pool *rq = &h->reply_queue[q];
	unsigned long flags, register_value = FIFO_EMPTY;

	/* msi auto clears the interrupt pending bit. */
	if (!(h->msi_vector || h->msix_vector)) {
		/* flush the controller write of the reply queue by reading
		 * outbound doorbell status register.
		 */
		register_value = readl(h->vaddr + SA5_OUTDB_STATUS);
		writel(SA5_OUTDB_CLEAR_PERF_BIT, h->vaddr + SA5_OUTDB_CLEAR);
		/* Do a read in order to flush the write to the controller
		 * (as per spec.)
		 */
		register_value = readl(h->vaddr + SA5_OUTDB_STATUS);
	}

	if ((rq->head[rq->current_entry] & 1) == rq->wraparound) {
		register_value = rq->head[rq->current_entry];
		rq->current_entry++;
		spin_lock_irqsave(&h->lock, flags);
		h->commands_outstanding--;
		spin_unlock_irqrestore(&h->lock, flags);
	} else {
		register_value = FIFO_EMPTY;
	}
	/* Check for wraparound */
	if (rq->current_entry == h->max_commands) {
		rq->current_entry = 0;
		rq->wraparound ^= 1;
	}
	return register_value;
}