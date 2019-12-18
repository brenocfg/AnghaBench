#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* thread_t ;
typedef  int ast_t ;
struct TYPE_4__ {int state; } ;

/* Variables and functions */
 int AST_PREEMPT ; 
 scalar_t__ AST_PREEMPTION ; 
 scalar_t__ AST_URGENT ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  THREAD_CONTINUE_NULL ; 
 int TH_IDLE ; 
 int /*<<< orphan*/  assert (int) ; 
 int ast_consume (scalar_t__) ; 
 int /*<<< orphan*/  ast_off (scalar_t__) ; 
 scalar_t__ ast_peek (scalar_t__) ; 
 int /*<<< orphan*/  c_ast_taken_block ; 
 int /*<<< orphan*/  counter (int /*<<< orphan*/ ) ; 
 TYPE_1__* current_thread () ; 
 scalar_t__ ml_get_interrupts_enabled () ; 
 int /*<<< orphan*/  thread_block_reason (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 scalar_t__ waitq_wait_possible (TYPE_1__*) ; 

void
ast_taken_kernel(void)
{
	assert(ml_get_interrupts_enabled() == FALSE);

	thread_t thread = current_thread();

	/* Idle threads handle preemption themselves */
	if ((thread->state & TH_IDLE)) {
		ast_off(AST_PREEMPTION);
		return;
	}

	/*
	 * It's possible for this to be called after AST_URGENT
	 * has already been handled, due to races in enable_preemption
	 */
	if (ast_peek(AST_URGENT) != AST_URGENT)
		return;

	/*
	 * Don't preempt if the thread is already preparing to block.
	 * TODO: the thread can cheese this with clear_wait()
	 */
	if (waitq_wait_possible(thread) == FALSE) {
		/* Consume AST_URGENT or the interrupt will call us again */
		ast_consume(AST_URGENT);
		return;
	}

	/* TODO: Should we csw_check again to notice if conditions have changed? */

	ast_t urgent_reason = ast_consume(AST_PREEMPTION);

	assert(urgent_reason & AST_PREEMPT);

	counter(c_ast_taken_block++);

	thread_block_reason(THREAD_CONTINUE_NULL, NULL, urgent_reason);

	assert(ml_get_interrupts_enabled() == FALSE);
}