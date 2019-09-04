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
typedef  int /*<<< orphan*/  thrd_t ;
typedef  scalar_t__ thrd_start_t ;

/* Variables and functions */
#define  EAGAIN 128 
 int /*<<< orphan*/  __ATTRP_C11_THREAD ; 
 int __pthread_create (int /*<<< orphan*/ *,int /*<<< orphan*/ ,void* (*) (void*),void*) ; 
 int thrd_error ; 
 int thrd_nomem ; 
 int thrd_success ; 

int thrd_create(thrd_t *thr, thrd_start_t func, void *arg)
{
	int ret = __pthread_create(thr, __ATTRP_C11_THREAD, (void *(*)(void *))func, arg);
	switch (ret) {
	case 0:      return thrd_success;
	case EAGAIN: return thrd_nomem;
	default:     return thrd_error;
	}
}