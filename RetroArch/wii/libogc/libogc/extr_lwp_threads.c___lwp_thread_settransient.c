#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  lwp_queue ;
struct TYPE_4__ {int /*<<< orphan*/  node; } ;
struct TYPE_5__ {TYPE_1__ object; int /*<<< orphan*/  priomap; int /*<<< orphan*/  cur_state; int /*<<< orphan*/ * ready; } ;
typedef  TYPE_2__ lwp_cntrl ;

/* Variables and functions */
 int /*<<< orphan*/  LWP_STATES_TRANSIENT ; 
 int /*<<< orphan*/  _CPU_ISR_Disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _CPU_ISR_Restore (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __lwp_priomap_removefrom (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  __lwp_queue_extractI (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  __lwp_queue_init_empty (int /*<<< orphan*/ *) ; 
 scalar_t__ __lwp_queue_onenode (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  __lwp_setstate (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ __lwp_stateready (int /*<<< orphan*/ ) ; 

void __lwp_thread_settransient(lwp_cntrl *thethread)
{
	u32 level,oldstates;
	lwp_queue *ready;

	ready = thethread->ready;

	_CPU_ISR_Disable(level);

	oldstates = thethread->cur_state;
	thethread->cur_state = __lwp_setstate(oldstates,LWP_STATES_TRANSIENT);

	if(__lwp_stateready(oldstates)) {
		if(__lwp_queue_onenode(ready)) {
			__lwp_queue_init_empty(ready);
			__lwp_priomap_removefrom(&thethread->priomap);
		} else {
			__lwp_queue_extractI(&thethread->object.node);
		}
	}

	_CPU_ISR_Restore(level);
}