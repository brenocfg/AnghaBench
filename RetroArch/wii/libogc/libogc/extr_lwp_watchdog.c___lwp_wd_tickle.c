#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int fire; int start; int /*<<< orphan*/  usr_data; int /*<<< orphan*/  (* routine ) (int /*<<< orphan*/ ) ;} ;
typedef  TYPE_1__ wd_cntrl ;
typedef  int u64 ;
typedef  int u32 ;
typedef  int s64 ;
typedef  int /*<<< orphan*/  lwp_queue ;

/* Variables and functions */
#define  LWP_WD_ACTIVE 131 
#define  LWP_WD_INACTIVE 130 
#define  LWP_WD_INSERTED 129 
#define  LWP_WD_REMOVE 128 
 scalar_t__ __lwp_queue_isempty (int /*<<< orphan*/ *) ; 
 TYPE_1__* __lwp_wd_first (int /*<<< orphan*/ *) ; 
 int __lwp_wd_remove (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  __lwp_wd_reset (TYPE_1__*) ; 
 int diff_ticks (int,int) ; 
 int gettime () ; 
 int /*<<< orphan*/  printf (char*,TYPE_1__*,int,int,int,int,int,int,int,int) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 

void __lwp_wd_tickle(lwp_queue *queue)
{
	wd_cntrl *wd;
	u64 now;
	s64 diff;

	if(__lwp_queue_isempty(queue)) return;

	wd = __lwp_wd_first(queue);
	now = gettime();
	diff = diff_ticks(now,wd->fire);
#ifdef _LWPWD_DEBUG
	printf("__lwp_wd_tickle(%p,%08x%08x,%08x%08x,%08x%08x,%08x%08x)\n",wd,(u32)(now>>32),(u32)now,(u32)(wd->start>>32),(u32)wd->start,(u32)(wd->fire>>32),(u32)wd->fire,(u32)(diff>>32),(u32)diff);
#endif
	if(diff<=0) {
		do {
			switch(__lwp_wd_remove(queue,wd)) {
				case LWP_WD_ACTIVE:
					wd->routine(wd->usr_data);
					break;
				case LWP_WD_INACTIVE:
					break;
				case LWP_WD_INSERTED:
					break;
				case LWP_WD_REMOVE:
					break;
			}
			wd = __lwp_wd_first(queue);
		} while(!__lwp_queue_isempty(queue) && wd->fire==0);
	} else {
		__lwp_wd_reset(wd);
	}
}