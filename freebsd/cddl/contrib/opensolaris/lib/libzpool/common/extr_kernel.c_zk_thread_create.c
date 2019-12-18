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
typedef  void kthread_t ;

/* Variables and functions */
 int /*<<< orphan*/  THR_DETACHED ; 
 int /*<<< orphan*/  VERIFY (int) ; 
 scalar_t__ thr_create (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void* (*) (void*),void*,int /*<<< orphan*/ ,scalar_t__*) ; 

kthread_t *
zk_thread_create(void (*func)(), void *arg)
{
	thread_t tid;

	VERIFY(thr_create(0, 0, (void *(*)(void *))func, arg, THR_DETACHED,
	    &tid) == 0);

	return ((void *)(uintptr_t)tid);
}