#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* thread_t ;
struct TYPE_6__ {scalar_t__ active; } ;

/* Variables and functions */
 int /*<<< orphan*/  AST_APC ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  assert (int) ; 
 TYPE_1__* current_thread () ; 
 int /*<<< orphan*/  panic (char*) ; 
 int /*<<< orphan*/  thread_apc_ast (TYPE_1__*) ; 
 int /*<<< orphan*/  thread_ast_clear (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  thread_terminate_internal (TYPE_1__*) ; 

void
thread_corpse_continue(void)
{
	thread_t thread = current_thread();

	thread_terminate_internal(thread);

	/*
	 * Handle the thread termination directly
	 * here instead of returning to userspace.
	 */
	assert(thread->active == FALSE);
	thread_ast_clear(thread, AST_APC);
	thread_apc_ast(thread);

	panic("thread_corpse_continue");
	/*NOTREACHED*/
}