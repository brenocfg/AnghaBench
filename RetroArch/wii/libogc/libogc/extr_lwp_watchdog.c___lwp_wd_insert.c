#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_9__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int /*<<< orphan*/  prev; } ;
struct TYPE_10__ {scalar_t__ fire; scalar_t__ state; TYPE_9__ node; int /*<<< orphan*/  start; } ;
typedef  TYPE_1__ wd_cntrl ;
typedef  scalar_t__ u64 ;
typedef  scalar_t__ u32 ;
typedef  int /*<<< orphan*/  lwp_queue ;

/* Variables and functions */
 scalar_t__ LWP_WD_INSERTED ; 
 int /*<<< orphan*/  _CPU_ISR_Disable (scalar_t__) ; 
 int /*<<< orphan*/  _CPU_ISR_Flash (scalar_t__) ; 
 int /*<<< orphan*/  _CPU_ISR_Restore (scalar_t__) ; 
 scalar_t__ __lwp_isr_in_progress () ; 
 int /*<<< orphan*/  __lwp_queue_insertI (int /*<<< orphan*/ ,TYPE_9__*) ; 
 int /*<<< orphan*/  __lwp_wd_activate (TYPE_1__*) ; 
 TYPE_1__* __lwp_wd_first (int /*<<< orphan*/ *) ; 
 TYPE_1__* __lwp_wd_next (TYPE_1__*) ; 
 int /*<<< orphan*/  __lwp_wd_settimer (TYPE_1__*) ; 
 int /*<<< orphan*/  _wd_sync_count ; 
 scalar_t__ _wd_sync_level ; 
 int /*<<< orphan*/  printf (char*,TYPE_1__*,int /*<<< orphan*/ ,scalar_t__) ; 

void __lwp_wd_insert(lwp_queue *header,wd_cntrl *wd)
{
	u32 level;
	u64 fire;
	u32 isr_nest_level;
	wd_cntrl *after;
#ifdef _LWPWD_DEBUG
	printf("__lwp_wd_insert(%p,%llu,%llu)\n",wd,wd->start,wd->fire);
#endif
	isr_nest_level = __lwp_isr_in_progress();
	wd->state = LWP_WD_INSERTED;

	_wd_sync_count++;
restart:
	_CPU_ISR_Disable(level);
	fire = wd->fire;
	for(after=__lwp_wd_first(header);;after=__lwp_wd_next(after)) {
		if(fire==0 || !__lwp_wd_next(after)) break;
		if(fire<after->fire) break;

		_CPU_ISR_Flash(level);
		if(wd->state!=LWP_WD_INSERTED) goto exit_insert;
		if(_wd_sync_level>isr_nest_level) {
			_wd_sync_level = isr_nest_level;
			_CPU_ISR_Restore(level);
			goto restart;
		}
	}
	__lwp_wd_activate(wd);
	wd->fire = fire;
	__lwp_queue_insertI(after->node.prev,&wd->node);
	if(__lwp_wd_first(header)==wd) __lwp_wd_settimer(wd);

exit_insert:
	_wd_sync_level = isr_nest_level;
	_wd_sync_count--;
	_CPU_ISR_Restore(level);
	return;
}