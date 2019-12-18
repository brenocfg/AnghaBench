#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_7__ {int /*<<< orphan*/  context; } ;
typedef  TYPE_1__ lwp_cntrl ;

/* Variables and functions */
 int /*<<< orphan*/  _CPU_ISR_Disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _CPU_ISR_Restore (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __lwp_dumpcontext_fp (TYPE_1__*,TYPE_1__*) ; 
 int /*<<< orphan*/  __lwp_thread_isallocatedfp (TYPE_1__*) ; 
 int /*<<< orphan*/  _cpu_context_restore_fp (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _cpu_context_save_fp (int /*<<< orphan*/ *) ; 
 TYPE_1__* _thr_allocated_fp ; 
 TYPE_1__* _thr_executing ; 

void __thread_dispatch_fp()
{
	u32 level;
	lwp_cntrl *exec;

	_CPU_ISR_Disable(level);
	exec = _thr_executing;
#ifdef _LWPTHREADS_DEBUG
	__lwp_dumpcontext_fp(exec,_thr_allocated_fp);
#endif
	if(!__lwp_thread_isallocatedfp(exec)) {
		if(_thr_allocated_fp) _cpu_context_save_fp(&_thr_allocated_fp->context);
		_cpu_context_restore_fp(&exec->context);
		_thr_allocated_fp = exec;
	}
	_CPU_ISR_Restore(level);
}