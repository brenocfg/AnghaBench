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
typedef  int uint32_t ;
struct ifnet {int dummy; } ;
struct dlil_threading_info {scalar_t__ input_thr; int input_waiting; int /*<<< orphan*/  input_lck; struct ifnet* ifp; } ;
typedef  int /*<<< orphan*/  caddr_t ;

/* Variables and functions */
 int DLIL_INPUT_TERMINATE ; 
 int DLIL_INPUT_TERMINATE_COMPLETE ; 
 int /*<<< orphan*/  OSAddAtomic (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VERIFY (int) ; 
 int /*<<< orphan*/  cur_dlil_input_threads ; 
 scalar_t__ current_thread () ; 
 struct dlil_threading_info* dlil_main_input_thread ; 
 scalar_t__ dlil_verbose ; 
 int if_input_thread_termination_spin ; 
 char* if_name (struct ifnet*) ; 
 int /*<<< orphan*/  lck_mtx_lock_spin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lck_mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  thread_deallocate (scalar_t__) ; 
 int /*<<< orphan*/  thread_terminate (scalar_t__) ; 
 int /*<<< orphan*/  wakeup_one (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
dlil_terminate_input_thread(struct dlil_threading_info *inp)
{
	struct ifnet *ifp = inp->ifp;

	VERIFY(current_thread() == inp->input_thr);
	VERIFY(inp != dlil_main_input_thread);

	OSAddAtomic(-1, &cur_dlil_input_threads);

#if TEST_INPUT_THREAD_TERMINATION
	{ /* do something useless that won't get optimized away */
		uint32_t	v = 1;
		for (uint32_t i = 0;
		     i < if_input_thread_termination_spin;
		     i++) {
			v = (i + 1) * v;
		}
		printf("the value is %d\n", v);
	}
#endif /* TEST_INPUT_THREAD_TERMINATION */

	lck_mtx_lock_spin(&inp->input_lck);
	VERIFY((inp->input_waiting & DLIL_INPUT_TERMINATE) != 0);
	inp->input_waiting |= DLIL_INPUT_TERMINATE_COMPLETE;
	wakeup_one((caddr_t)&inp->input_waiting);
	lck_mtx_unlock(&inp->input_lck);

	/* for the extra refcnt from kernel_thread_start() */
	thread_deallocate(current_thread());

	if (dlil_verbose) {
		printf("%s: input thread terminated\n",
		    if_name(ifp));
	}

	/* this is the end */
	thread_terminate(current_thread());
	/* NOTREACHED */
}