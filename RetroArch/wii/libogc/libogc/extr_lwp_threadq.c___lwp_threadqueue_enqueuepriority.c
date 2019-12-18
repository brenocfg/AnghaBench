#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_27__   TYPE_9__ ;
typedef  struct TYPE_26__   TYPE_8__ ;
typedef  struct TYPE_25__   TYPE_7__ ;
typedef  struct TYPE_24__   TYPE_6__ ;
typedef  struct TYPE_23__   TYPE_5__ ;
typedef  struct TYPE_22__   TYPE_4__ ;
typedef  struct TYPE_21__   TYPE_3__ ;
typedef  struct TYPE_20__   TYPE_2__ ;
typedef  struct TYPE_19__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u64 ;
typedef  size_t u32 ;
struct TYPE_19__ {TYPE_7__* priority; } ;
struct TYPE_24__ {size_t state; scalar_t__ sync_state; TYPE_1__ queues; } ;
typedef  TYPE_6__ lwp_thrqueue ;
struct TYPE_25__ {scalar_t__ last; scalar_t__ first; } ;
typedef  TYPE_7__ lwp_queue ;
struct TYPE_26__ {struct TYPE_26__* prev; struct TYPE_26__* next; } ;
typedef  TYPE_8__ lwp_node ;
struct TYPE_23__ {TYPE_4__* queue; int /*<<< orphan*/  ret_code; int /*<<< orphan*/  block2n; } ;
struct TYPE_20__ {scalar_t__ prev; scalar_t__ next; } ;
struct TYPE_21__ {TYPE_2__ node; } ;
struct TYPE_27__ {size_t cur_prio; int /*<<< orphan*/  timer; TYPE_5__ wait; TYPE_3__ object; int /*<<< orphan*/  cur_state; } ;
typedef  TYPE_9__ lwp_cntrl ;
struct TYPE_22__ {int /*<<< orphan*/  timeout_state; } ;

/* Variables and functions */
 int LWP_PRIO_MAX ; 
 size_t LWP_PRIO_MIN ; 
#define  LWP_THREADQ_NOTHINGHAPPEND 131 
 size_t LWP_THREADQ_PRIOPERHEADER ; 
 size_t LWP_THREADQ_REVERSESEARCHMASK ; 
#define  LWP_THREADQ_SATISFIED 130 
#define  LWP_THREADQ_SYNCHRONIZED 129 
#define  LWP_THREADQ_TIMEOUT 128 
 int /*<<< orphan*/  _CPU_ISR_Disable (size_t) ; 
 int /*<<< orphan*/  _CPU_ISR_Flash (size_t) ; 
 int /*<<< orphan*/  _CPU_ISR_Restore (size_t) ; 
 int /*<<< orphan*/  __lwp_queue_init_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  __lwp_queue_ishead (TYPE_7__*,TYPE_8__*) ; 
 int /*<<< orphan*/  __lwp_queue_istail (TYPE_7__*,TYPE_8__*) ; 
 TYPE_8__* __lwp_queue_tail (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  __lwp_statesset (int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  __lwp_thread_unblock (TYPE_9__*) ; 
 int /*<<< orphan*/  __lwp_wd_deactivate (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  __lwp_wd_isactive (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  __lwp_wd_remove_ticks (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*,TYPE_9__*,...) ; 

void __lwp_threadqueue_enqueuepriority(lwp_thrqueue *queue,lwp_cntrl *thethread,u64 timeout)
{
	u32 level,search_prio,header_idx,prio,block_state,sync_state;
	lwp_cntrl *search_thread;
	lwp_queue *header;
	lwp_node *cur_node,*next_node,*prev_node,*search_node;

	__lwp_queue_init_empty(&thethread->wait.block2n);

	prio = thethread->cur_prio;
	header_idx = prio/LWP_THREADQ_PRIOPERHEADER;
	header = &queue->queues.priority[header_idx];
	block_state = queue->state;

	if(prio&LWP_THREADQ_REVERSESEARCHMASK) {
#ifdef _LWPTHRQ_DEBUG
		printf("__lwp_threadqueue_enqueuepriority(%p,reverse_search)\n",thethread);
#endif
		goto reverse_search;
	}

#ifdef _LWPTHRQ_DEBUG
	printf("__lwp_threadqueue_enqueuepriority(%p,forward_search)\n",thethread);
#endif
forward_search:
	search_prio = LWP_PRIO_MIN - 1;
	_CPU_ISR_Disable(level);
	search_thread = (lwp_cntrl*)header->first;
	while(!__lwp_queue_istail(header,(lwp_node*)search_thread)) {
		search_prio = search_thread->cur_prio;
		if(prio<=search_prio) break;
		_CPU_ISR_Flash(level);

		if(!__lwp_statesset(search_thread->cur_state,block_state)) {
			_CPU_ISR_Restore(level);
			goto forward_search;
		}
		search_thread = (lwp_cntrl*)search_thread->object.node.next;
	}
	if(queue->sync_state!=LWP_THREADQ_NOTHINGHAPPEND) goto synchronize;
	queue->sync_state = LWP_THREADQ_SYNCHRONIZED;
	if(prio==search_prio) goto equal_prio;

	search_node = (lwp_node*)search_thread;
	prev_node = search_node->prev;
	cur_node = (lwp_node*)thethread;

	cur_node->next = search_node;
	cur_node->prev = prev_node;
	prev_node->next = cur_node;
	search_node->prev = cur_node;
	_CPU_ISR_Restore(level);
	return;

reverse_search:
	search_prio = LWP_PRIO_MAX + 1;
	_CPU_ISR_Disable(level);
	search_thread = (lwp_cntrl*)header->last;
	while(!__lwp_queue_ishead(header,(lwp_node*)search_thread)) {
		search_prio = search_thread->cur_prio;
		if(prio>=search_prio) break;
		_CPU_ISR_Flash(level);

		if(!__lwp_statesset(search_thread->cur_state,block_state)) {
			_CPU_ISR_Restore(level);
			goto reverse_search;
		}
		search_thread = (lwp_cntrl*)search_thread->object.node.prev;
	}
	if(queue->sync_state!=LWP_THREADQ_NOTHINGHAPPEND) goto synchronize;
	queue->sync_state = LWP_THREADQ_SYNCHRONIZED;
	if(prio==search_prio) goto equal_prio;

	search_node = (lwp_node*)search_thread;
	next_node = search_node->next;
	cur_node = (lwp_node*)thethread;

	cur_node->next = next_node;
	cur_node->prev = search_node;
	search_node->next = cur_node;
	next_node->prev = cur_node;
	_CPU_ISR_Restore(level);
	return;

equal_prio:
#ifdef _LWPTHRQ_DEBUG
	printf("__lwp_threadqueue_enqueuepriority(%p,equal_prio)\n",thethread);
#endif
	search_node = __lwp_queue_tail(&search_thread->wait.block2n);
	prev_node = search_node->prev;
	cur_node = (lwp_node*)thethread;

	cur_node->next = search_node;
	cur_node->prev = prev_node;
	prev_node->next = cur_node;
	search_node->prev = cur_node;
	_CPU_ISR_Restore(level);
	return;

synchronize:
	sync_state = queue->sync_state;
	queue->sync_state = LWP_THREADQ_SYNCHRONIZED;

#ifdef _LWPTHRQ_DEBUG
	printf("__lwp_threadqueue_enqueuepriority(%p,sync_state = %d)\n",thethread,sync_state);
#endif
	switch(sync_state) {
		case LWP_THREADQ_SYNCHRONIZED:
			break;
		case LWP_THREADQ_NOTHINGHAPPEND:
			break;
		case LWP_THREADQ_TIMEOUT:
			thethread->wait.ret_code = thethread->wait.queue->timeout_state;
			_CPU_ISR_Restore(level);
			break;
		case LWP_THREADQ_SATISFIED:
			if(__lwp_wd_isactive(&thethread->timer)) {
				__lwp_wd_deactivate(&thethread->timer);
				_CPU_ISR_Restore(level);
				__lwp_wd_remove_ticks(&thethread->timer);
			} else
				_CPU_ISR_Restore(level);
			break;
	}
	__lwp_thread_unblock(thethread);
}