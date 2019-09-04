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
typedef  int /*<<< orphan*/  thread_t ;
typedef  int /*<<< orphan*/  spl_t ;
typedef  int /*<<< orphan*/  processor_t ;
typedef  int ast_t ;

/* Variables and functions */
 int AST_NONE ; 
 int AST_PREEMPT ; 
 int /*<<< orphan*/  AST_YIELD ; 
 int /*<<< orphan*/  THREAD_CONTINUE_NULL ; 
 int /*<<< orphan*/  ast_on (int) ; 
 int* ast_pending () ; 
 int csw_check (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  current_processor () ; 
 int /*<<< orphan*/  current_thread () ; 
 int /*<<< orphan*/  splsched () ; 
 int /*<<< orphan*/  splx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  thread_block_reason (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  thread_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  thread_unlock (int /*<<< orphan*/ ) ; 

void
thread_yield_to_preemption()
{
	/* 
	 * ast_pending() should ideally be called with interrupts disabled, but 
	 * the check here is fine because csw_check() will do the right thing.
	 */
	ast_t *pending_ast = ast_pending();
	ast_t ast = AST_NONE;
	processor_t p;

	if (*pending_ast & AST_PREEMPT) {
		thread_t self = current_thread();

		spl_t s = splsched();

		p = current_processor();
		thread_lock(self);
		ast = csw_check(p, AST_YIELD);
		ast_on(ast);
		thread_unlock(self);

		if (ast != AST_NONE) {
			(void)thread_block_reason(THREAD_CONTINUE_NULL,	NULL, ast);
		}

		splx(s);
	}
}