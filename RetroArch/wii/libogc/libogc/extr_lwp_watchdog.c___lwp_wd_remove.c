#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int state; int /*<<< orphan*/  node; } ;
typedef  TYPE_1__ wd_cntrl ;
typedef  int u32 ;
typedef  int /*<<< orphan*/  lwp_queue ;

/* Variables and functions */
#define  LWP_WD_ACTIVE 131 
#define  LWP_WD_INACTIVE 130 
#define  LWP_WD_INSERTED 129 
#define  LWP_WD_REMOVE 128 
 int /*<<< orphan*/  _CPU_ISR_Disable (int) ; 
 int /*<<< orphan*/  _CPU_ISR_Restore (int) ; 
 int /*<<< orphan*/  __lwp_isr_in_progress () ; 
 int /*<<< orphan*/  __lwp_queue_extractI (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  __lwp_queue_isempty (int /*<<< orphan*/ *) ; 
 TYPE_1__* __lwp_wd_first (int /*<<< orphan*/ *) ; 
 TYPE_1__* __lwp_wd_next (TYPE_1__*) ; 
 int /*<<< orphan*/  __lwp_wd_settimer (TYPE_1__*) ; 
 int /*<<< orphan*/  _wd_sync_count ; 
 int /*<<< orphan*/  _wd_sync_level ; 
 int /*<<< orphan*/  printf (char*,TYPE_1__*) ; 

u32 __lwp_wd_remove(lwp_queue *header,wd_cntrl *wd)
{
	u32 level;
	u32 prev_state;
	wd_cntrl *next;
#ifdef _LWPWD_DEBUG
	printf("__lwp_wd_remove(%p)\n",wd);
#endif
	_CPU_ISR_Disable(level);
	prev_state = wd->state;
	switch(prev_state) {
		case LWP_WD_INACTIVE:
			break;
		case  LWP_WD_INSERTED:
			wd->state = LWP_WD_INACTIVE;
			break;
		case LWP_WD_ACTIVE:
		case LWP_WD_REMOVE:
			wd->state = LWP_WD_INACTIVE;
			next = __lwp_wd_next(wd);
			if(_wd_sync_count) _wd_sync_level = __lwp_isr_in_progress();
			__lwp_queue_extractI(&wd->node);
			if(!__lwp_queue_isempty(header) && __lwp_wd_first(header)==next) __lwp_wd_settimer(next);
			break;
	}
	_CPU_ISR_Restore(level);
	return prev_state;
}