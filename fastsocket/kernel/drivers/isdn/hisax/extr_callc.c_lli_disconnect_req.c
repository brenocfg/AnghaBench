#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct FsmInst {struct Channel* userdata; } ;
struct Channel {TYPE_4__* proc; TYPE_3__* d_st; scalar_t__ leased; } ;
struct TYPE_5__ {int cause; } ;
struct TYPE_8__ {TYPE_1__ para; } ;
struct TYPE_6__ {int /*<<< orphan*/  (* l4l3 ) (TYPE_3__*,int,TYPE_4__*) ;} ;
struct TYPE_7__ {TYPE_2__ lli; } ;

/* Variables and functions */
 int CC_DISCONNECT ; 
 int /*<<< orphan*/  FsmChangeState (struct FsmInst*,int /*<<< orphan*/ ) ; 
 int REQUEST ; 
 int /*<<< orphan*/  ST_WAIT_DRELEASE ; 
 int /*<<< orphan*/  lli_leased_hup (struct FsmInst*,struct Channel*) ; 
 int /*<<< orphan*/  stub1 (TYPE_3__*,int,TYPE_4__*) ; 

__attribute__((used)) static void
lli_disconnect_req(struct FsmInst *fi, int event, void *arg)
{
	struct Channel *chanp = fi->userdata;

	if (chanp->leased) {
		lli_leased_hup(fi, chanp);
	} else {
		FsmChangeState(fi, ST_WAIT_DRELEASE);
		if (chanp->proc)
			chanp->proc->para.cause = 0x10;	/* Normal Call Clearing */
		chanp->d_st->lli.l4l3(chanp->d_st, CC_DISCONNECT | REQUEST,
			chanp->proc);
	}
}