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
struct FsmInst {int state; TYPE_1__* fsm; int /*<<< orphan*/  (* printdebug ) (struct FsmInst*,char*,int /*<<< orphan*/ ) ;scalar_t__ debug; } ;
struct TYPE_2__ {int /*<<< orphan*/ * strState; } ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct FsmInst*,char*,int /*<<< orphan*/ ) ; 

void
mISDN_FsmChangeState(struct FsmInst *fi, int newstate)
{
	fi->state = newstate;
	if (fi->debug)
		fi->printdebug(fi, "ChangeState %s",
			fi->fsm->strState[newstate]);
}