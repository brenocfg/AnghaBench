#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_6__ {int /*<<< orphan*/  node; } ;
struct TYPE_7__ {int cur_state; scalar_t__ cur_prio; TYPE_1__ object; int /*<<< orphan*/  ready; int /*<<< orphan*/  priomap; } ;
typedef  TYPE_2__ lwp_cntrl ;
struct TYPE_8__ {scalar_t__ is_preemptible; } ;

/* Variables and functions */
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  _CPU_ISR_Disable (int) ; 
 int /*<<< orphan*/  _CPU_ISR_Flash (int) ; 
 int /*<<< orphan*/  _CPU_ISR_Restore (int) ; 
 int __lwp_clearstate (int,int) ; 
 int /*<<< orphan*/  __lwp_priomap_addto (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  __lwp_queue_appendI (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ __lwp_stateready (int) ; 
 int /*<<< orphan*/  _context_switch_want ; 
 TYPE_4__* _thr_executing ; 
 TYPE_2__* _thr_heir ; 

void __lwp_thread_clearstate(lwp_cntrl *thethread,u32 state)
{
	u32 level,cur_state;

	_CPU_ISR_Disable(level);

	cur_state = thethread->cur_state;
	if(cur_state&state) {
		cur_state = thethread->cur_state = __lwp_clearstate(cur_state,state);
		if(__lwp_stateready(cur_state)) {
			__lwp_priomap_addto(&thethread->priomap);
			__lwp_queue_appendI(thethread->ready,&thethread->object.node);
			_CPU_ISR_Flash(level);

			if(thethread->cur_prio<_thr_heir->cur_prio) {
				_thr_heir = thethread;
				if(_thr_executing->is_preemptible
					|| thethread->cur_prio==0)
				_context_switch_want = TRUE;
			}
		}
	}

	_CPU_ISR_Restore(level);
}