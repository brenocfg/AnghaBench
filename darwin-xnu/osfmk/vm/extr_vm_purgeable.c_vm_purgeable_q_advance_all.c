#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
typedef  TYPE_1__* purgeable_q_t ;
typedef  scalar_t__ int64_t ;
typedef  scalar_t__ int32_t ;
struct TYPE_6__ {scalar_t__ count; size_t next; } ;
struct TYPE_5__ {scalar_t__ new_pages; int token_q_unripe; size_t token_q_head; int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_MACH_VM ; 
 int /*<<< orphan*/  KERNEL_DEBUG_CONSTANT (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LCK_MTX_ASSERT (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LCK_MTX_ASSERT_OWNED ; 
 int /*<<< orphan*/  MACHDBG_CODE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int PURGEABLE_Q_TYPE_FIFO ; 
 int PURGEABLE_Q_TYPE_MAX ; 
 scalar_t__ TOKEN_COUNT_MAX ; 
 int TOKEN_NEW_PAGECOUNT_MAX ; 
 int /*<<< orphan*/  TOKEN_RIPEN ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  available_for_purge ; 
 TYPE_1__* purgeable_queues ; 
 int token_new_pagecount ; 
 TYPE_3__* tokens ; 
 int /*<<< orphan*/  vm_page_queue_lock ; 
 int /*<<< orphan*/  vm_purgeable_token_check_queue (TYPE_1__*) ; 

void
vm_purgeable_q_advance_all()
{
	LCK_MTX_ASSERT(&vm_page_queue_lock, LCK_MTX_ASSERT_OWNED);
	
	/* check queue counters - if they get really large, scale them back.
	 * They tend to get that large when there is no purgeable queue action */
	int i;
	if(token_new_pagecount > (TOKEN_NEW_PAGECOUNT_MAX >> 1))	/* a system idling years might get there */
	{
		for (i = PURGEABLE_Q_TYPE_FIFO; i < PURGEABLE_Q_TYPE_MAX; i++) {
			int64_t pages = purgeable_queues[i].new_pages += token_new_pagecount;
			assert(pages >= 0);
			assert(pages <= TOKEN_COUNT_MAX);
			purgeable_queues[i].new_pages = (int32_t) pages;
			assert(purgeable_queues[i].new_pages == pages);
		}
		token_new_pagecount = 0;
	}
	
	/*
	 * Decrement token counters. A token counter can be zero, this means the
	 * object is ripe to be purged. It is not purged immediately, because that
	 * could cause several objects to be purged even if purging one would satisfy
	 * the memory needs. Instead, the pageout thread purges one after the other
	 * by calling vm_purgeable_object_purge_one and then rechecking the memory
	 * balance.
	 *
	 * No need to advance obsolete queue - all items are ripe there,
	 * always
	 */
	for (i = PURGEABLE_Q_TYPE_FIFO; i < PURGEABLE_Q_TYPE_MAX; i++) {
		purgeable_q_t queue = &purgeable_queues[i];
		uint32_t num_pages = 1;
		
		/* Iterate over tokens as long as there are unripe tokens. */
		while (queue->token_q_unripe) {
			if (tokens[queue->token_q_unripe].count && num_pages)
			{
				tokens[queue->token_q_unripe].count -= 1;
				num_pages -= 1;
			}

			if (tokens[queue->token_q_unripe].count == 0) {
				queue->token_q_unripe = tokens[queue->token_q_unripe].next;
				available_for_purge++;
				KERNEL_DEBUG_CONSTANT((MACHDBG_CODE(DBG_MACH_VM, TOKEN_RIPEN)),
						      queue->type,
						      tokens[queue->token_q_head].count,	/* num pages on new
											 * first token */
						      0,
						      available_for_purge,
						      0);
				continue;	/* One token ripened. Make sure to
						 * check the next. */
			}
			if (num_pages == 0)
				break;	/* Current token not ripe and no more pages.
					 * Work done. */
		}

		/*
		 * if there are no unripe tokens in the queue, decrement the
		 * new_pages counter instead new_pages can be negative, but must be
		 * canceled out by token_new_pagecount -- since inactive queue as a
		 * whole always contains a nonnegative number of pages
		 */
		if (!queue->token_q_unripe) {
			queue->new_pages -= num_pages;
			assert((int32_t) token_new_pagecount + queue->new_pages >= 0);
		}
#if MACH_ASSERT
		vm_purgeable_token_check_queue(queue);
#endif
	}
}