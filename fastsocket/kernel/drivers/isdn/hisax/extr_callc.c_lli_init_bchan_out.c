#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct FsmInst {struct Channel* userdata; } ;
struct Channel {int debug; TYPE_2__* b_st; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* l4l3 ) (TYPE_2__*,int,int /*<<< orphan*/ *) ;} ;
struct TYPE_4__ {TYPE_1__ lli; } ;

/* Variables and functions */
 int DL_ESTABLISH ; 
 int /*<<< orphan*/  FsmChangeState (struct FsmInst*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HL_LL (struct Channel*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ISDN_STAT_DCONN ; 
 int REQUEST ; 
 int /*<<< orphan*/  ST_WAIT_BCONN ; 
 int /*<<< orphan*/  init_b_st (struct Channel*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  link_debug (struct Channel*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
lli_init_bchan_out(struct FsmInst *fi, int event, void *arg)
{
	struct Channel *chanp = fi->userdata;

	FsmChangeState(fi, ST_WAIT_BCONN);
	if (chanp->debug & 1)
		link_debug(chanp, 0, "STAT_DCONN");
	HL_LL(chanp, ISDN_STAT_DCONN);
	init_b_st(chanp, 0);
	chanp->b_st->lli.l4l3(chanp->b_st, DL_ESTABLISH | REQUEST, NULL);
}