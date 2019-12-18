#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct FsmTimer {int /*<<< orphan*/  tl; TYPE_1__* fi; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* printdebug ) (TYPE_1__*,char*,long,int) ;scalar_t__ debug; } ;

/* Variables and functions */
 int /*<<< orphan*/  del_timer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*,char*,long,int) ; 

void
mISDN_FsmDelTimer(struct FsmTimer *ft, int where)
{
#if FSM_TIMER_DEBUG
	if (ft->fi->debug)
		ft->fi->printdebug(ft->fi, "mISDN_FsmDelTimer %lx %d",
			(long) ft, where);
#endif
	del_timer(&ft->tl);
}