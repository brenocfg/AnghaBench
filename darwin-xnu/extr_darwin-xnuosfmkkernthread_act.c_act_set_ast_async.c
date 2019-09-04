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
typedef  scalar_t__ thread_t ;
typedef  int /*<<< orphan*/  spl_t ;
typedef  int /*<<< orphan*/  ast_t ;

/* Variables and functions */
 int /*<<< orphan*/  ast_propagate (scalar_t__) ; 
 scalar_t__ current_thread () ; 
 int /*<<< orphan*/  splsched () ; 
 int /*<<< orphan*/  splx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  thread_ast_set (scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
act_set_ast_async(thread_t  thread,
                  ast_t     ast)
{
	thread_ast_set(thread, ast);

	if (thread == current_thread()) {
		spl_t s = splsched();
		ast_propagate(thread);
		splx(s);
	}
}