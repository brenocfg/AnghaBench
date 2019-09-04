#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* thread_t ;
typedef  int /*<<< orphan*/  kern_return_t ;
struct TYPE_8__ {scalar_t__ task; scalar_t__ active; } ;

/* Variables and functions */
 int /*<<< orphan*/  AST_APC ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  KERN_FAILURE ; 
 int /*<<< orphan*/  KERN_INVALID_ARGUMENT ; 
 TYPE_1__* THREAD_NULL ; 
 int /*<<< orphan*/  assert (int) ; 
 TYPE_1__* current_thread () ; 
 scalar_t__ kernel_task ; 
 int /*<<< orphan*/  panic (char*) ; 
 int /*<<< orphan*/  thread_apc_ast (TYPE_1__*) ; 
 int /*<<< orphan*/  thread_ast_clear (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  thread_terminate_internal (TYPE_1__*) ; 

kern_return_t
thread_terminate(
	thread_t		thread)
{
	if (thread == THREAD_NULL)
		return (KERN_INVALID_ARGUMENT);

	/* Kernel threads can't be terminated without their own cooperation */
	if (thread->task == kernel_task && thread != current_thread())
		return (KERN_FAILURE);

	kern_return_t result = thread_terminate_internal(thread);

	/*
	 * If a kernel thread is terminating itself, force handle the APC_AST here.
	 * Kernel threads don't pass through the return-to-user AST checking code,
	 * but all threads must finish their own termination in thread_apc_ast.
	 */
	if (thread->task == kernel_task) {
		assert(thread->active == FALSE);
		thread_ast_clear(thread, AST_APC);
		thread_apc_ast(thread);

		panic("thread_terminate");
		/* NOTREACHED */
	}

	return (result);
}