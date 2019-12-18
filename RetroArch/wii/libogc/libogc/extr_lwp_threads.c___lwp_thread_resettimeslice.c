#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_10__ {scalar_t__ first; } ;
typedef  TYPE_2__ lwp_queue ;
struct TYPE_9__ {int /*<<< orphan*/  node; } ;
struct TYPE_11__ {TYPE_1__ object; TYPE_2__* ready; } ;
typedef  TYPE_3__ lwp_cntrl ;

/* Variables and functions */
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  _CPU_ISR_Disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _CPU_ISR_Flash (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _CPU_ISR_Restore (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __lwp_queue_appendI (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  __lwp_queue_extractI (int /*<<< orphan*/ *) ; 
 scalar_t__ __lwp_queue_onenode (TYPE_2__*) ; 
 scalar_t__ __lwp_thread_isheir (TYPE_3__*) ; 
 int /*<<< orphan*/  _context_switch_want ; 
 TYPE_3__* _thr_executing ; 
 TYPE_3__* _thr_heir ; 

void __lwp_thread_resettimeslice()
{
	u32 level;
	lwp_cntrl *exec;
	lwp_queue *ready;

	exec = _thr_executing;
	ready = exec->ready;

	_CPU_ISR_Disable(level);
	if(__lwp_queue_onenode(ready)) {
		_CPU_ISR_Restore(level);
		return;
	}

	__lwp_queue_extractI(&exec->object.node);
	__lwp_queue_appendI(ready,&exec->object.node);

	_CPU_ISR_Flash(level);

	if(__lwp_thread_isheir(exec))
		_thr_heir = (lwp_cntrl*)ready->first;

	_context_switch_want = TRUE;
	_CPU_ISR_Restore(level);
}