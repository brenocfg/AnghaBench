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
typedef  int /*<<< orphan*/  pthread_once_t ;

/* Variables and functions */
 int /*<<< orphan*/  __wait (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  __wake (int /*<<< orphan*/ *,int,int) ; 
 int a_cas (int /*<<< orphan*/ *,int,int) ; 
 int a_swap (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  pthread_cleanup_pop (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pthread_cleanup_push (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  undo ; 

int __pthread_once_full(pthread_once_t *control, void (*init)(void))
{
	/* Try to enter initializing state. Four possibilities:
	 *  0 - we're the first or the other cancelled; run init
	 *  1 - another thread is running init; wait
	 *  2 - another thread finished running init; just return
	 *  3 - another thread is running init, waiters present; wait */

	for (;;) switch (a_cas(control, 0, 1)) {
	case 0:
		pthread_cleanup_push(undo, control);
		init();
		pthread_cleanup_pop(0);

		if (a_swap(control, 2) == 3)
			__wake(control, -1, 1);
		return 0;
	case 1:
		/* If this fails, so will __wait. */
		a_cas(control, 1, 3);
	case 3:
		__wait(control, 0, 3, 1);
		continue;
	case 2:
		return 0;
	}
}