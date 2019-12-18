#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct FsmInst {struct Channel* userdata; } ;
struct Channel {scalar_t__ chan; TYPE_4__* cs; scalar_t__ Flags; } ;
struct TYPE_6__ {int /*<<< orphan*/  num; } ;
struct TYPE_8__ {TYPE_1__ parm; scalar_t__ arg; int /*<<< orphan*/  command; int /*<<< orphan*/  driver; } ;
typedef  TYPE_3__ isdn_ctrl ;
struct TYPE_7__ {int /*<<< orphan*/  (* statcallb ) (TYPE_3__*) ;} ;
struct TYPE_9__ {int /*<<< orphan*/  (* cardmsg ) (TYPE_4__*,int /*<<< orphan*/ ,void*) ;TYPE_2__ iif; int /*<<< orphan*/  myid; } ;

/* Variables and functions */
 int /*<<< orphan*/  FsmChangeState (struct FsmInst*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HL_LL (struct Channel*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ISDN_STAT_CAUSE ; 
 int /*<<< orphan*/  ISDN_STAT_DHUP ; 
 int /*<<< orphan*/  MDL_INFO_REL ; 
 int /*<<< orphan*/  ST_NULL ; 
 int /*<<< orphan*/  sprintf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (TYPE_3__*) ; 
 int /*<<< orphan*/  stub2 (TYPE_4__*,int /*<<< orphan*/ ,void*) ; 

__attribute__((used)) static void
lli_failure_l(struct FsmInst *fi, int event, void *arg)
{
	struct Channel *chanp = fi->userdata;
	isdn_ctrl ic;

	FsmChangeState(fi, ST_NULL);
	ic.driver = chanp->cs->myid;
	ic.command = ISDN_STAT_CAUSE;
	ic.arg = chanp->chan;
	sprintf(ic.parm.num, "L%02X%02X", 0, 0x2f);
	chanp->cs->iif.statcallb(&ic);
	HL_LL(chanp, ISDN_STAT_DHUP);
	chanp->Flags = 0;
	chanp->cs->cardmsg(chanp->cs, MDL_INFO_REL, (void *) (long)chanp->chan);
}