#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  s32 ;
typedef  int /*<<< orphan*/  mutex_t ;
struct TYPE_4__ {int /*<<< orphan*/  mutex; } ;
typedef  TYPE_1__ mutex_st ;

/* Variables and functions */
 int /*<<< orphan*/  EBUSY ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  __lwp_mutex_flush (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __lwp_mutex_free (TYPE_1__*) ; 
 scalar_t__ __lwp_mutex_locked (int /*<<< orphan*/ *) ; 
 TYPE_1__* __lwp_mutex_open (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __lwp_thread_dispatchenable () ; 

s32 LWP_MutexDestroy(mutex_t mutex)
{
	mutex_st *p = __lwp_mutex_open(mutex);
	if(!p) return 0;

	if(__lwp_mutex_locked(&p->mutex)) {
		__lwp_thread_dispatchenable();
		return EBUSY;
	}
	__lwp_mutex_flush(&p->mutex,EINVAL);
	__lwp_thread_dispatchenable();

	__lwp_mutex_free(p);
	return 0;
}