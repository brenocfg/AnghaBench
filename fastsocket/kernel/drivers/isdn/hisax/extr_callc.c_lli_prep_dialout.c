#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct FsmInst {struct Channel* userdata; } ;
struct Channel {TYPE_2__* d_st; scalar_t__ leased; scalar_t__ chan; TYPE_3__* cs; scalar_t__ incoming; int /*<<< orphan*/  l2_protocol; int /*<<< orphan*/  l2_active_protocol; int /*<<< orphan*/  dial_timer; int /*<<< orphan*/  drel_timer; } ;
struct TYPE_6__ {int /*<<< orphan*/  (* cardmsg ) (TYPE_3__*,int /*<<< orphan*/ ,void*) ;} ;
struct TYPE_4__ {int /*<<< orphan*/  (* l4l3 ) (TYPE_2__*,int,struct Channel*) ;} ;
struct TYPE_5__ {TYPE_1__ lli; } ;

/* Variables and functions */
 int CC_SETUP ; 
 int /*<<< orphan*/  FsmChangeState (struct FsmInst*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FsmDelTimer (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  MDL_INFO_SETUP ; 
 int REQUEST ; 
 int /*<<< orphan*/  ST_OUT_DIAL ; 
 int /*<<< orphan*/  lli_init_bchan_out (struct FsmInst*,int,void*) ; 
 int /*<<< orphan*/  stub1 (TYPE_3__*,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  stub2 (TYPE_2__*,int,struct Channel*) ; 

__attribute__((used)) static void
lli_prep_dialout(struct FsmInst *fi, int event, void *arg)
{
	struct Channel *chanp = fi->userdata;

	FsmDelTimer(&chanp->drel_timer, 60);
	FsmDelTimer(&chanp->dial_timer, 73);
	chanp->l2_active_protocol = chanp->l2_protocol;
	chanp->incoming = 0;
	chanp->cs->cardmsg(chanp->cs, MDL_INFO_SETUP, (void *) (long)chanp->chan);
	if (chanp->leased) {
		lli_init_bchan_out(fi, event, arg);
	} else {
		FsmChangeState(fi, ST_OUT_DIAL);
		chanp->d_st->lli.l4l3(chanp->d_st, CC_SETUP | REQUEST, chanp);
	}
}