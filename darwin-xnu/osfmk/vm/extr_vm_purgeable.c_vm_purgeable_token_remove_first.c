#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_4__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int token_idx_t ;
typedef  TYPE_1__* purgeable_q_t ;
struct TYPE_6__ {scalar_t__ next; int /*<<< orphan*/  count; scalar_t__ prev; } ;
struct TYPE_5__ {int token_q_head; int token_q_tail; int token_q_unripe; int /*<<< orphan*/  type; int /*<<< orphan*/  debug_count_tokens; int /*<<< orphan*/  new_pages; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_MACH_VM ; 
 int /*<<< orphan*/  KERNEL_DEBUG_CONSTANT (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LCK_MTX_ASSERT (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LCK_MTX_ASSERT_OWNED ; 
 int /*<<< orphan*/  MACHDBG_CODE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TOKEN_DELETE ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ available_for_purge ; 
 int /*<<< orphan*/  token_new_pagecount ; 
 TYPE_4__* tokens ; 
 int /*<<< orphan*/  vm_page_queue_lock ; 
 int /*<<< orphan*/  vm_purgeable_token_check_queue (TYPE_1__*) ; 

__attribute__((used)) static token_idx_t 
vm_purgeable_token_remove_first(purgeable_q_t queue)
{
	LCK_MTX_ASSERT(&vm_page_queue_lock, LCK_MTX_ASSERT_OWNED);
	
	token_idx_t     token;
	token = queue->token_q_head;

	assert(token);

	if (token) {
		assert(queue->token_q_tail);
		if (queue->token_q_head == queue->token_q_unripe) {
			/* no ripe tokens... must move unripe pointer */
			queue->token_q_unripe = tokens[token].next;
		} else {
			/* we're removing a ripe token. decrease count */
			available_for_purge--;
			assert(available_for_purge >= 0);
		}

		if (queue->token_q_tail == queue->token_q_head)
			assert(tokens[token].next == 0);

		queue->token_q_head = tokens[token].next;
		if (queue->token_q_head) {
			tokens[queue->token_q_head].count += tokens[token].count;
			tokens[queue->token_q_head].prev = 0;
		} else {
			/* currently no other tokens in the queue */
			/*
			 * the page count must be added to the next newly
			 * created token
			 */
			queue->new_pages += tokens[token].count;
			/* if head is zero, tail is too */
			queue->token_q_tail = 0;
		}

#if MACH_ASSERT
		queue->debug_count_tokens--;
		vm_purgeable_token_check_queue(queue);

		KERNEL_DEBUG_CONSTANT((MACHDBG_CODE(DBG_MACH_VM, TOKEN_DELETE)),
				      queue->type,
				      tokens[queue->token_q_head].count,	/* num pages on new
										 * first token */
				      token_new_pagecount,	/* num pages waiting for
								 * next token */
				      available_for_purge,
				      0);
#endif
	}
	return token;
}