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
struct TYPE_2__ {long data; void* function; } ;
struct FsmTimer {TYPE_1__ tl; struct FsmInst* fi; } ;
struct FsmInst {int /*<<< orphan*/  (* printdebug ) (struct FsmInst*,char*,long) ;scalar_t__ debug; } ;

/* Variables and functions */
 scalar_t__ FsmExpireTimer ; 
 int /*<<< orphan*/  init_timer (TYPE_1__*) ; 
 int /*<<< orphan*/  stub1 (struct FsmInst*,char*,long) ; 

void
mISDN_FsmInitTimer(struct FsmInst *fi, struct FsmTimer *ft)
{
	ft->fi = fi;
	ft->tl.function = (void *) FsmExpireTimer;
	ft->tl.data = (long) ft;
#if FSM_TIMER_DEBUG
	if (ft->fi->debug)
		ft->fi->printdebug(ft->fi, "mISDN_FsmInitTimer %lx", (long) ft);
#endif
	init_timer(&ft->tl);
}