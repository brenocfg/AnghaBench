#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_29__   TYPE_8__ ;
typedef  struct TYPE_28__   TYPE_7__ ;
typedef  struct TYPE_27__   TYPE_6__ ;
typedef  struct TYPE_26__   TYPE_5__ ;
typedef  struct TYPE_25__   TYPE_4__ ;
typedef  struct TYPE_24__   TYPE_3__ ;
typedef  struct TYPE_23__   TYPE_2__ ;
typedef  struct TYPE_22__   TYPE_1__ ;

/* Type definitions */
struct FsmInst {struct Channel* userdata; } ;
struct Channel {int chan; int debug; TYPE_8__* cs; TYPE_7__* proc; TYPE_6__* d_st; int /*<<< orphan*/  drel_timer; int /*<<< orphan*/  setup; } ;
typedef  int /*<<< orphan*/  setup_parm ;
struct TYPE_24__ {int /*<<< orphan*/  setup; } ;
struct TYPE_26__ {int arg; TYPE_3__ parm; int /*<<< orphan*/  command; int /*<<< orphan*/  driver; } ;
typedef  TYPE_5__ isdn_ctrl ;
struct TYPE_23__ {int (* statcallb ) (TYPE_5__*) ;} ;
struct TYPE_29__ {int /*<<< orphan*/  (* cardmsg ) (TYPE_8__*,int /*<<< orphan*/ ,void*) ;TYPE_2__ iif; int /*<<< orphan*/  myid; } ;
struct TYPE_22__ {int /*<<< orphan*/  setup; } ;
struct TYPE_28__ {TYPE_1__ para; } ;
struct TYPE_25__ {int /*<<< orphan*/  (* l4l3 ) (TYPE_6__*,int,TYPE_7__*) ;} ;
struct TYPE_27__ {TYPE_4__ lli; } ;

/* Variables and functions */
 int CC_ALERTING ; 
 int CC_IGNORE ; 
 int CC_MORE_INFO ; 
 int CC_PROCEED_SEND ; 
 int CC_REDIR ; 
 int /*<<< orphan*/  FsmChangeState (struct FsmInst*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FsmDelTimer (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ISDN_STAT_ICALL ; 
 int /*<<< orphan*/  ISDN_STAT_ICALLW ; 
 int /*<<< orphan*/  MDL_INFO_REL ; 
 int /*<<< orphan*/  MDL_INFO_SETUP ; 
 int REQUEST ; 
 int /*<<< orphan*/  ST_IN_ALERT_SENT ; 
 int /*<<< orphan*/  ST_IN_PROCEED_SEND ; 
 int /*<<< orphan*/  ST_IN_WAIT_LL ; 
 int /*<<< orphan*/  ST_NULL ; 
 int /*<<< orphan*/  link_debug (struct Channel*,int,char*,...) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  stub1 (TYPE_8__*,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  stub10 (TYPE_8__*,int /*<<< orphan*/ ,void*) ; 
 int stub2 (TYPE_5__*) ; 
 int /*<<< orphan*/  stub3 (TYPE_6__*,int,TYPE_7__*) ; 
 int /*<<< orphan*/  stub4 (TYPE_6__*,int,TYPE_7__*) ; 
 int /*<<< orphan*/  stub5 (TYPE_6__*,int,TYPE_7__*) ; 
 int /*<<< orphan*/  stub6 (TYPE_6__*,int,TYPE_7__*) ; 
 int /*<<< orphan*/  stub7 (TYPE_6__*,int,TYPE_7__*) ; 
 int /*<<< orphan*/  stub8 (TYPE_8__*,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  stub9 (TYPE_6__*,int,TYPE_7__*) ; 

__attribute__((used)) static void
lli_deliver_call(struct FsmInst *fi, int event, void *arg)
{
	struct Channel *chanp = fi->userdata;
	isdn_ctrl ic;
	int ret;

	chanp->cs->cardmsg(chanp->cs, MDL_INFO_SETUP, (void *) (long)chanp->chan);
	/*
	 * Report incoming calls only once to linklevel, use CallFlags
	 * which is set to 3 with each broadcast message in isdnl1.c
	 * and resetted if a interface  answered the STAT_ICALL.
	 */
	if (1) { /* for only one TEI */
		FsmChangeState(fi, ST_IN_WAIT_LL);
		if (chanp->debug & 1)
			link_debug(chanp, 0, (chanp->chan < 2) ? "STAT_ICALL" : "STAT_ICALLW");
		ic.driver = chanp->cs->myid;
		ic.command = ((chanp->chan < 2) ? ISDN_STAT_ICALL : ISDN_STAT_ICALLW);

		ic.arg = chanp->chan;
		/*
		 * No need to return "unknown" for calls without OAD,
		 * cause that's handled in linklevel now (replaced by '0')
		 */
		memcpy(&ic.parm.setup, &chanp->proc->para.setup, sizeof(setup_parm));
		ret = chanp->cs->iif.statcallb(&ic);
		if (chanp->debug & 1)
			link_debug(chanp, 1, "statcallb ret=%d", ret);

		switch (ret) {
			case 1:	/* OK, someone likes this call */
				FsmDelTimer(&chanp->drel_timer, 61);
				FsmChangeState(fi, ST_IN_ALERT_SENT);
				chanp->d_st->lli.l4l3(chanp->d_st, CC_ALERTING | REQUEST, chanp->proc);
				break;
			case 5: /* direct redirect */
			case 4: /* Proceeding desired */
				FsmDelTimer(&chanp->drel_timer, 61);
				FsmChangeState(fi, ST_IN_PROCEED_SEND);
				chanp->d_st->lli.l4l3(chanp->d_st, CC_PROCEED_SEND | REQUEST, chanp->proc);
				if (ret == 5) {
					memcpy(&chanp->setup, &ic.parm.setup, sizeof(setup_parm));
					chanp->d_st->lli.l4l3(chanp->d_st, CC_REDIR | REQUEST, chanp->proc);
				}
				break;
			case 2:	/* Rejecting Call */
				break;
			case 3:	/* incomplete number */
				FsmDelTimer(&chanp->drel_timer, 61);
				chanp->d_st->lli.l4l3(chanp->d_st, CC_MORE_INFO | REQUEST, chanp->proc);
				break;
			case 0:	/* OK, nobody likes this call */
			default:	/* statcallb problems */
				chanp->d_st->lli.l4l3(chanp->d_st, CC_IGNORE | REQUEST, chanp->proc);
				chanp->cs->cardmsg(chanp->cs, MDL_INFO_REL, (void *) (long)chanp->chan);
				FsmChangeState(fi, ST_NULL);
				break;
		}
	} else {
		chanp->d_st->lli.l4l3(chanp->d_st, CC_IGNORE | REQUEST, chanp->proc);
		chanp->cs->cardmsg(chanp->cs, MDL_INFO_REL, (void *) (long)chanp->chan);
	}
}