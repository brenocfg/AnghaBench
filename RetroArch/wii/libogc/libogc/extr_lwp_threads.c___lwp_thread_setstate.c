#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  lwp_queue ;
struct TYPE_7__ {int /*<<< orphan*/  node; } ;
struct TYPE_8__ {int /*<<< orphan*/  cur_state; TYPE_1__ object; int /*<<< orphan*/  priomap; int /*<<< orphan*/ * ready; } ;
typedef  TYPE_2__ lwp_cntrl ;

/* Variables and functions */
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  _CPU_ISR_Disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _CPU_ISR_Flash (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _CPU_ISR_Restore (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __lwp_clearstate (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __lwp_priomap_removefrom (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  __lwp_queue_extractI (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  __lwp_queue_init_empty (int /*<<< orphan*/ *) ; 
 scalar_t__ __lwp_queue_onenode (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  __lwp_stateready (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __lwp_thread_calcheir () ; 
 scalar_t__ __lwp_thread_isexec (TYPE_2__*) ; 
 scalar_t__ __lwp_thread_isheir (TYPE_2__*) ; 
 int /*<<< orphan*/  _context_switch_want ; 
 int /*<<< orphan*/  _thr_heir ; 
 int /*<<< orphan*/  kprintf (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ) ; 

void __lwp_thread_setstate(lwp_cntrl *thethread,u32 state)
{
	u32 level;
	lwp_queue *ready;

	ready = thethread->ready;
#ifdef _LWPTHREADS_DEBUG
	kprintf("__lwp_thread_setstate(%d,%p,%p,%08x)\n",_context_switch_want,_thr_heir,thethread,thethread->cur_state);
#endif
	_CPU_ISR_Disable(level);
	if(!__lwp_stateready(thethread->cur_state)) {
		thethread->cur_state = __lwp_clearstate(thethread->cur_state,state);
		_CPU_ISR_Restore(level);
		return;
	}

	thethread->cur_state = state;
	if(__lwp_queue_onenode(ready)) {
		__lwp_queue_init_empty(ready);
		__lwp_priomap_removefrom(&thethread->priomap);
	} else
		__lwp_queue_extractI(&thethread->object.node);
	_CPU_ISR_Flash(level);

	if(__lwp_thread_isheir(thethread))
		__lwp_thread_calcheir();
	if(__lwp_thread_isexec(thethread))
		_context_switch_want = TRUE;
#ifdef _LWPTHREADS_DEBUG
	kprintf("__lwp_thread_setstate(%d,%p,%p,%08x)\n",_context_switch_want,_thr_heir,thethread,thethread->cur_state);
#endif
	_CPU_ISR_Restore(level);
}