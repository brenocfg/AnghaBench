#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
typedef  int s32 ;
typedef  int /*<<< orphan*/  mutex_t ;
struct TYPE_3__ {int /*<<< orphan*/  mutex; } ;
typedef  TYPE_1__ mutex_st ;

/* Variables and functions */
 TYPE_1__* __lwp_mutex_open (int /*<<< orphan*/ ) ; 
 int __lwp_mutex_surrender (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  __lwp_thread_dispatchenable () ; 

s32 LWP_MutexUnlock(mutex_t mutex)
{
	u32 ret;
	mutex_st *lock;

	lock = __lwp_mutex_open(mutex);
	if(!lock) return -1;

	ret = __lwp_mutex_surrender(&lock->mutex);
	__lwp_thread_dispatchenable();

	return ret;
}