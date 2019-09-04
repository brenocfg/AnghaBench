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
 int __pthread_once_full (int /*<<< orphan*/ *,void (*) ()) ; 
 int /*<<< orphan*/  a_barrier () ; 

int __pthread_once(pthread_once_t *control, void (*init)(void))
{
	/* Return immediately if init finished before, but ensure that
	 * effects of the init routine are visible to the caller. */
	if (*(volatile int *)control == 2) {
		a_barrier();
		return 0;
	}
	return __pthread_once_full(control, init);
}