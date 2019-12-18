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
struct TYPE_4__ {scalar_t__ max_cnt; } ;
struct TYPE_5__ {scalar_t__ count; TYPE_1__ attrs; int /*<<< orphan*/  wait_queue; } ;
typedef  TYPE_2__ lwp_sema ;
typedef  int /*<<< orphan*/  lwp_cntrl ;

/* Variables and functions */
 int /*<<< orphan*/  LWP_SEMA_MAXCNT_EXCEEDED ; 
 int /*<<< orphan*/  LWP_SEMA_SUCCESSFUL ; 
 int /*<<< orphan*/  _CPU_ISR_Disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _CPU_ISR_Restore (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * __lwp_threadqueue_dequeue (int /*<<< orphan*/ *) ; 

u32 __lwp_sema_surrender(lwp_sema *sema,u32 id)
{
	u32 level,ret;
	lwp_cntrl *thethread;

	ret = LWP_SEMA_SUCCESSFUL;
	if((thethread=__lwp_threadqueue_dequeue(&sema->wait_queue))) return ret;
	else {
		_CPU_ISR_Disable(level);
		if(sema->count<=sema->attrs.max_cnt)
			++sema->count;
		else
			ret = LWP_SEMA_MAXCNT_EXCEEDED;
		_CPU_ISR_Restore(level);
	}
	return ret;
}