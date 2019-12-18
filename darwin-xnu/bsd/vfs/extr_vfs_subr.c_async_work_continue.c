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
typedef  scalar_t__ vnode_t ;
typedef  int /*<<< orphan*/  thread_continue_t ;
struct async_work_lst {int dummy; } ;

/* Variables and functions */
 scalar_t__ NULLVP ; 
 scalar_t__ TAILQ_EMPTY (struct async_work_lst*) ; 
 scalar_t__ TAILQ_FIRST (struct async_work_lst*) ; 
 int /*<<< orphan*/  THREAD_UNINT ; 
 int /*<<< orphan*/  assert_wait (struct async_work_lst*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  async_work_handled ; 
 int /*<<< orphan*/  panic (char*,scalar_t__) ; 
 scalar_t__ process_vp (scalar_t__,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  thread_block (int /*<<< orphan*/ ) ; 
 struct async_work_lst vnode_async_work_list ; 
 int /*<<< orphan*/  vnode_list_lock () ; 
 int /*<<< orphan*/  vnode_list_unlock () ; 

__attribute__((used)) __attribute__((noreturn))
static void
async_work_continue(void)
{
	struct async_work_lst *q;
	int	deferred;
	vnode_t	vp;

	q = &vnode_async_work_list;

	for (;;) {

		vnode_list_lock();

		if ( TAILQ_EMPTY(q) ) {
			assert_wait(q, (THREAD_UNINT));
	
			vnode_list_unlock();
			
			thread_block((thread_continue_t)async_work_continue);

			continue;
		}
		async_work_handled++;

		vp = TAILQ_FIRST(q);

		vp = process_vp(vp, 0, &deferred);

		if (vp != NULLVP)
			panic("found VBAD vp (%p) on async queue", vp);
	}
}