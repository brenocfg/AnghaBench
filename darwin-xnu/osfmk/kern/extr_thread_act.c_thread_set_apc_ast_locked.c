#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* thread_t ;
typedef  TYPE_2__* processor_t ;
struct TYPE_10__ {scalar_t__ state; TYPE_1__* active_thread; } ;
struct TYPE_9__ {TYPE_2__* last_processor; } ;

/* Variables and functions */
 int /*<<< orphan*/  AST_APC ; 
 TYPE_2__* PROCESSOR_NULL ; 
 scalar_t__ PROCESSOR_RUNNING ; 
 int /*<<< orphan*/  ast_propagate (TYPE_1__*) ; 
 int /*<<< orphan*/  cause_ast_check (TYPE_2__*) ; 
 TYPE_1__* current_thread () ; 
 int /*<<< orphan*/  thread_ast_set (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
thread_set_apc_ast_locked(thread_t thread)
{
	thread_ast_set(thread, AST_APC);

	if (thread == current_thread()) {
		ast_propagate(thread);
	} else {
		processor_t processor = thread->last_processor;

		if (processor != PROCESSOR_NULL &&
		    processor->state == PROCESSOR_RUNNING &&
		    processor->active_thread == thread) {
			cause_ast_check(processor);
		}
	}
}