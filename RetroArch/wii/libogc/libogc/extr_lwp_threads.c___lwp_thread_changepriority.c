#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct TYPE_8__ {int /*<<< orphan*/  node; } ;
struct TYPE_9__ {TYPE_1__ object; int /*<<< orphan*/  ready; int /*<<< orphan*/  priomap; int /*<<< orphan*/  cur_state; scalar_t__ cur_prio; } ;
typedef  TYPE_2__ lwp_cntrl ;
struct TYPE_10__ {scalar_t__ is_preemptible; } ;

/* Variables and functions */
 int /*<<< orphan*/  LWP_STATES_TRANSIENT ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  _CPU_ISR_Disable (scalar_t__) ; 
 int /*<<< orphan*/  _CPU_ISR_Flash (scalar_t__) ; 
 int /*<<< orphan*/  _CPU_ISR_Restore (scalar_t__) ; 
 int /*<<< orphan*/  __lwp_clearstate (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __lwp_priomap_addto (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  __lwp_queue_appendI (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  __lwp_queue_prependI (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  __lwp_stateready (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __lwp_thread_calcheir () ; 
 int /*<<< orphan*/  __lwp_thread_setpriority (TYPE_2__*,scalar_t__) ; 
 int /*<<< orphan*/  __lwp_thread_settransient (TYPE_2__*) ; 
 int /*<<< orphan*/  _context_switch_want ; 
 TYPE_3__* _thr_executing ; 
 TYPE_3__* _thr_heir ; 

void __lwp_thread_changepriority(lwp_cntrl *thethread,u32 prio,u32 prependit)
{
	u32 level;

	__lwp_thread_settransient(thethread);

	if(thethread->cur_prio!=prio)
		__lwp_thread_setpriority(thethread,prio);

	_CPU_ISR_Disable(level);

	thethread->cur_state = __lwp_clearstate(thethread->cur_state,LWP_STATES_TRANSIENT);
	if(!__lwp_stateready(thethread->cur_state)) {
		_CPU_ISR_Restore(level);
		return;
	}

	__lwp_priomap_addto(&thethread->priomap);
	if(prependit)
		__lwp_queue_prependI(thethread->ready,&thethread->object.node);
	else
		__lwp_queue_appendI(thethread->ready,&thethread->object.node);

	_CPU_ISR_Flash(level);

	__lwp_thread_calcheir();

	if(!(_thr_executing==_thr_heir)
		&& _thr_executing->is_preemptible)
		_context_switch_want = TRUE;

	_CPU_ISR_Restore(level);
}