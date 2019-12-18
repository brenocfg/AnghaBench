#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ wait_result_t ;
typedef  int vm_size_t ;
typedef  int /*<<< orphan*/  vm_offset_t ;
typedef  size_t token_idx_t ;
struct token {int next; scalar_t__ count; size_t prev; } ;
typedef  TYPE_1__* purgeable_q_t ;
typedef  scalar_t__ kern_return_t ;
typedef  int int64_t ;
typedef  int int32_t ;
typedef  int /*<<< orphan*/  event_t ;
typedef  enum purgeable_q_type { ____Placeholder_purgeable_q_type } purgeable_q_type ;
struct TYPE_6__ {int new_pages; } ;
struct TYPE_5__ {scalar_t__ type; scalar_t__ new_pages; size_t token_q_tail; size_t token_q_head; size_t token_q_unripe; int /*<<< orphan*/  debug_count_tokens; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_MACH_VM ; 
 int /*<<< orphan*/  KERNEL_DEBUG_CONSTANT (int /*<<< orphan*/ ,scalar_t__,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ KERN_ABORTED ; 
 scalar_t__ KERN_RESOURCE_SHORTAGE ; 
 scalar_t__ KERN_SUCCESS ; 
 int /*<<< orphan*/  LCK_MTX_ASSERT (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LCK_MTX_ASSERT_OWNED ; 
 int /*<<< orphan*/  LCK_SLEEP_DEFAULT ; 
 int /*<<< orphan*/  MACHDBG_CODE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int PAGE_SIZE ; 
 size_t PURGEABLE_Q_TYPE_FIFO ; 
 size_t PURGEABLE_Q_TYPE_LIFO ; 
 int PURGEABLE_Q_TYPE_MAX ; 
 scalar_t__ PURGEABLE_Q_TYPE_OBSOLETE ; 
 scalar_t__ THREAD_AWAKENED ; 
 int /*<<< orphan*/  THREAD_UNINT ; 
 int /*<<< orphan*/  TOKEN_ADD ; 
 int TOKEN_COUNT_MAX ; 
 int /*<<< orphan*/  VM_KERN_MEMORY_OSFMK ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  available_for_purge ; 
 int /*<<< orphan*/  kernel_map ; 
 scalar_t__ kmem_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kmem_free (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ kmem_realloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 scalar_t__ lck_mtx_sleep (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__* purgeable_queues ; 
 int /*<<< orphan*/  thread_wakeup (int /*<<< orphan*/ ) ; 
 int token_free_idx ; 
 scalar_t__ token_init_idx ; 
 int token_new_pagecount ; 
 int token_q_allocating ; 
 int token_q_cur_size ; 
 scalar_t__ token_q_max_cnt ; 
 struct token* tokens ; 
 int /*<<< orphan*/  vm_page_lock_queues () ; 
 int /*<<< orphan*/  vm_page_queue_lock ; 
 int /*<<< orphan*/  vm_page_unlock_queues () ; 
 int /*<<< orphan*/  vm_purgeable_token_check_queue (TYPE_2__*) ; 

kern_return_t
vm_purgeable_token_add(purgeable_q_t queue)
{
	LCK_MTX_ASSERT(&vm_page_queue_lock, LCK_MTX_ASSERT_OWNED);
	
	/* new token */
	token_idx_t     token;
	enum purgeable_q_type i;

find_available_token:

	if (token_free_idx) {				/* unused tokens available */
		token = token_free_idx;
		token_free_idx = tokens[token_free_idx].next;
	} else if (token_init_idx < token_q_max_cnt) {	/* lazy token array init */
		token = token_init_idx;
		token_init_idx++;
	} else {					/* allocate more memory */
		/* Wait if another thread is inside the memory alloc section */
		while(token_q_allocating) {
			wait_result_t res = lck_mtx_sleep(&vm_page_queue_lock,
							  LCK_SLEEP_DEFAULT,
							  (event_t)&token_q_allocating,
							  THREAD_UNINT);
			if(res != THREAD_AWAKENED) return KERN_ABORTED;
		};
		
		/* Check whether memory is still maxed out */
		if(token_init_idx < token_q_max_cnt)
			goto find_available_token;
		
		/* Still no memory. Allocate some. */
		token_q_allocating = 1;
		
		/* Drop page queue lock so we can allocate */
		vm_page_unlock_queues();
		
		struct token *new_loc;
		vm_size_t alloc_size = token_q_cur_size + PAGE_SIZE;
		kern_return_t result;
		
		if (alloc_size / sizeof (struct token) > TOKEN_COUNT_MAX) {
			result = KERN_RESOURCE_SHORTAGE;
		} else {
			if (token_q_cur_size) {
				result = kmem_realloc(kernel_map,
						      (vm_offset_t) tokens,
						      token_q_cur_size,
						      (vm_offset_t *) &new_loc,
						      alloc_size, VM_KERN_MEMORY_OSFMK);
			} else {
				result = kmem_alloc(kernel_map,
						    (vm_offset_t *) &new_loc,
						    alloc_size, VM_KERN_MEMORY_OSFMK);
			}
		}
		
		vm_page_lock_queues();
		
		if (result) {
			/* Unblock waiting threads */
			token_q_allocating = 0;
			thread_wakeup((event_t)&token_q_allocating);
			return result;
		}
		
		/* If we get here, we allocated new memory. Update pointers and
		 * dealloc old range */
		struct token *old_tokens=tokens;
		tokens=new_loc;
		vm_size_t old_token_q_cur_size=token_q_cur_size;
		token_q_cur_size=alloc_size;
		token_q_max_cnt = (token_idx_t) (token_q_cur_size /
						 sizeof(struct token));
		assert (token_init_idx < token_q_max_cnt);	/* We must have a free token now */
		
		if (old_token_q_cur_size) {	/* clean up old mapping */
			vm_page_unlock_queues();
			/* kmem_realloc leaves the old region mapped. Get rid of it. */
			kmem_free(kernel_map, (vm_offset_t)old_tokens, old_token_q_cur_size);
			vm_page_lock_queues();
		}
		
		/* Unblock waiting threads */
		token_q_allocating = 0;
		thread_wakeup((event_t)&token_q_allocating);
		
		goto find_available_token;
	}
	
	assert (token);
	
	/*
	 * the new pagecount we got need to be applied to all queues except
	 * obsolete
	 */
	for (i = PURGEABLE_Q_TYPE_FIFO; i < PURGEABLE_Q_TYPE_MAX; i++) {
		int64_t pages = purgeable_queues[i].new_pages += token_new_pagecount;
		assert(pages >= 0);
		assert(pages <= TOKEN_COUNT_MAX);
		purgeable_queues[i].new_pages = (int32_t) pages;
		assert(purgeable_queues[i].new_pages == pages);
	}
	token_new_pagecount = 0;

	/* set token counter value */
	if (queue->type != PURGEABLE_Q_TYPE_OBSOLETE)
		tokens[token].count = queue->new_pages;
	else
		tokens[token].count = 0;	/* all obsolete items are
						 * ripe immediately */
	queue->new_pages = 0;

	/* put token on token counter list */
	tokens[token].next = 0;
	if (queue->token_q_tail == 0) {
		assert(queue->token_q_head == 0 && queue->token_q_unripe == 0);
		queue->token_q_head = token;
		tokens[token].prev = 0;
	} else {
		tokens[queue->token_q_tail].next = token;
		tokens[token].prev = queue->token_q_tail;
	}
	if (queue->token_q_unripe == 0) {	/* only ripe tokens (token
						 * count == 0) in queue */
		if (tokens[token].count > 0)
			queue->token_q_unripe = token;	/* first unripe token */
		else
			available_for_purge++;	/* added a ripe token?
						 * increase available count */
	}
	queue->token_q_tail = token;

#if MACH_ASSERT
	queue->debug_count_tokens++;
	/* Check both queues, since we modified the new_pages count on each */
	vm_purgeable_token_check_queue(&purgeable_queues[PURGEABLE_Q_TYPE_FIFO]);
	vm_purgeable_token_check_queue(&purgeable_queues[PURGEABLE_Q_TYPE_LIFO]);

	KERNEL_DEBUG_CONSTANT((MACHDBG_CODE(DBG_MACH_VM, TOKEN_ADD)),
			      queue->type,
			      tokens[token].count,	/* num pages on token
							 * (last token) */
			      queue->debug_count_tokens,
			      0,
			      0);
#endif

	return KERN_SUCCESS;
}