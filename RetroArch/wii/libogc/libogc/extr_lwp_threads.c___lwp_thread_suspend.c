#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  lwp_queue ;
struct TYPE_6__ {int /*<<< orphan*/  node; } ;
struct TYPE_7__ {TYPE_1__ object; int /*<<< orphan*/  priomap; int /*<<< orphan*/  cur_state; int /*<<< orphan*/  suspendcnt; int /*<<< orphan*/ * ready; } ;
typedef  TYPE_2__ lwp_cntrl ;

/* Variables and functions */
 int /*<<< orphan*/  LWP_STATES_SUSPENDED ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  _CPU_ISR_Disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _CPU_ISR_Flash (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _CPU_ISR_Restore (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __lwp_priomap_removefrom (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  __lwp_queue_extractI (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  __lwp_queue_init_empty (int /*<<< orphan*/ *) ; 
 scalar_t__ __lwp_queue_onenode (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  __lwp_setstate (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __lwp_stateready (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __lwp_thread_calcheir () ; 
 scalar_t__ __lwp_thread_isexec (TYPE_2__*) ; 
 scalar_t__ __lwp_thread_isheir (TYPE_2__*) ; 
 int /*<<< orphan*/  _context_switch_want ; 

void __lwp_thread_suspend(lwp_cntrl *thethread)
{
	u32 level;
	lwp_queue *ready;

	ready = thethread->ready;

	_CPU_ISR_Disable(level);
	thethread->suspendcnt++;
	if(!__lwp_stateready(thethread->cur_state)) {
		thethread->cur_state = __lwp_setstate(thethread->cur_state,LWP_STATES_SUSPENDED);
		_CPU_ISR_Restore(level);
		return;
	}

	thethread->cur_state = LWP_STATES_SUSPENDED;
	if(__lwp_queue_onenode(ready)) {
		__lwp_queue_init_empty(ready);
		__lwp_priomap_removefrom(&thethread->priomap);
	} else {
		__lwp_queue_extractI(&thethread->object.node);
	}
	_CPU_ISR_Flash(level);

	if(__lwp_thread_isheir(thethread))
		__lwp_thread_calcheir();

	if(__lwp_thread_isexec(thethread))
		_context_switch_want = TRUE;

	_CPU_ISR_Restore(level);
}