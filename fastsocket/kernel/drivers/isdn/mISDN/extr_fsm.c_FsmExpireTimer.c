#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct FsmTimer {int /*<<< orphan*/  arg; int /*<<< orphan*/  event; TYPE_1__* fi; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* printdebug ) (TYPE_1__*,char*,long) ;scalar_t__ debug; } ;

/* Variables and functions */
 int /*<<< orphan*/  mISDN_FsmEvent (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*,char*,long) ; 

__attribute__((used)) static void
FsmExpireTimer(struct FsmTimer *ft)
{
#if FSM_TIMER_DEBUG
	if (ft->fi->debug)
		ft->fi->printdebug(ft->fi, "FsmExpireTimer %lx", (long) ft);
#endif
	mISDN_FsmEvent(ft->fi, ft->event, ft->arg);
}