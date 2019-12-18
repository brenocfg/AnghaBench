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
struct TYPE_3__ {int /*<<< orphan*/  object; } ;
typedef  TYPE_1__ mutex_st ;

/* Variables and functions */
 scalar_t__ __lwp_objmgr_allocate (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  __lwp_objmgr_open (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  __lwp_thread_dispatchdisable () ; 
 int /*<<< orphan*/  __lwp_thread_dispatchunnest () ; 
 int /*<<< orphan*/  _lwp_mutex_objects ; 

__attribute__((used)) static mutex_st* __lwp_mutex_allocate()
{
	mutex_st *lock;

	__lwp_thread_dispatchdisable();
	lock = (mutex_st*)__lwp_objmgr_allocate(&_lwp_mutex_objects);
	if(lock) {
		__lwp_objmgr_open(&_lwp_mutex_objects,&lock->object);
		return lock;
	}
	__lwp_thread_dispatchunnest();
	return NULL;
}