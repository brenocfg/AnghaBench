#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_2__* thread_t ;
typedef  int /*<<< orphan*/  spl_t ;
typedef  void* mach_exception_data_type_t ;
struct TYPE_7__ {void* subcode; void* code; } ;
struct TYPE_8__ {scalar_t__ task; TYPE_1__ guard_exc_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  AST_GUARD ; 
 int EXC_GUARD_DECODE_GUARD_TYPE (void*) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  ast_propagate (TYPE_2__*) ; 
 TYPE_2__* current_thread () ; 
 scalar_t__ kernel_task ; 
 int /*<<< orphan*/  splsched () ; 
 int /*<<< orphan*/  splx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  thread_ast_set (TYPE_2__*,int /*<<< orphan*/ ) ; 

void
thread_guard_violation(thread_t thread,
    mach_exception_data_type_t code, mach_exception_data_type_t subcode)
{
	assert(thread == current_thread());

	/* don't set up the AST for kernel threads */
	if (thread->task == kernel_task)
		return;

	spl_t s = splsched();
	/*
	 * Use the saved state area of the thread structure
	 * to store all info required to handle the AST when
	 * returning to userspace
	 */
	assert(EXC_GUARD_DECODE_GUARD_TYPE(code));
	thread->guard_exc_info.code = code;
	thread->guard_exc_info.subcode = subcode;
	thread_ast_set(thread, AST_GUARD);
	ast_propagate(thread);

	splx(s);
}