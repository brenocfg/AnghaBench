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
typedef  size_t u8 ;
typedef  int u32 ;
struct reply_pool {int* head; size_t current_entry; int wraparound; } ;
struct TYPE_2__ {int (* command_completed ) (struct ctlr_info*,size_t) ;} ;
struct ctlr_info {int transMethod; size_t max_commands; int /*<<< orphan*/  lock; int /*<<< orphan*/  commands_outstanding; TYPE_1__ access; struct reply_pool* reply_queue; } ;

/* Variables and functions */
 int CFGTBL_Trans_Performant ; 
 int FIFO_EMPTY ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int stub1 (struct ctlr_info*,size_t) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static inline u32 next_command(struct ctlr_info *h, u8 q)
{
	u32 a;
	struct reply_pool *rq = &h->reply_queue[q];
	unsigned long flags;

	if (unlikely(!(h->transMethod & CFGTBL_Trans_Performant)))
		return h->access.command_completed(h, q);

	if ((rq->head[rq->current_entry] & 1) == rq->wraparound) {
		a = rq->head[rq->current_entry];
		rq->current_entry++;
		spin_lock_irqsave(&h->lock, flags);
		h->commands_outstanding--;
		spin_unlock_irqrestore(&h->lock, flags);
	} else {
		a = FIFO_EMPTY;
	}
	/* Check for wraparound */
	if (rq->current_entry == h->max_commands) {
		rq->current_entry = 0;
		rq->wraparound ^= 1;
	}
	return a;
}