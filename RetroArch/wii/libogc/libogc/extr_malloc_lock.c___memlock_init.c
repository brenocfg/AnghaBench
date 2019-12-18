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
struct TYPE_3__ {int prioceil; int /*<<< orphan*/  onlyownerrelease; int /*<<< orphan*/  nest_behavior; int /*<<< orphan*/  mode; } ;
typedef  TYPE_1__ lwp_mutex_attr ;

/* Variables and functions */
 int /*<<< orphan*/  LWP_MUTEX_FIFO ; 
 int /*<<< orphan*/  LWP_MUTEX_NEST_ACQUIRE ; 
 int /*<<< orphan*/  LWP_MUTEX_UNLOCKED ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  __lwp_mutex_initialize (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __lwp_thread_dispatchdisable () ; 
 int /*<<< orphan*/  __lwp_thread_dispatchunnest () ; 
 int initialized ; 
 int /*<<< orphan*/  mem_lock ; 

void __memlock_init()
{
	__lwp_thread_dispatchdisable();
	if(!initialized) {
		lwp_mutex_attr attr;

		initialized = 1;

		attr.mode = LWP_MUTEX_FIFO;
		attr.nest_behavior = LWP_MUTEX_NEST_ACQUIRE;
		attr.onlyownerrelease = TRUE;
		attr.prioceil = 1;
		__lwp_mutex_initialize(&mem_lock,&attr,LWP_MUTEX_UNLOCKED);
	}
	__lwp_thread_dispatchunnest();
}