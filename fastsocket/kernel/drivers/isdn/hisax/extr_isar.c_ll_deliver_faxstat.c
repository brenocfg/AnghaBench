#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_8__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_char ;
struct Channel {int /*<<< orphan*/  chan; } ;
struct BCState {TYPE_8__* cs; TYPE_5__* st; } ;
struct TYPE_9__ {int /*<<< orphan*/  cmd; } ;
struct TYPE_10__ {TYPE_1__ aux; } ;
struct TYPE_14__ {TYPE_2__ parm; int /*<<< orphan*/  arg; int /*<<< orphan*/  command; int /*<<< orphan*/  driver; } ;
typedef  TYPE_6__ isdn_ctrl ;
struct TYPE_11__ {int /*<<< orphan*/  (* statcallb ) (TYPE_6__*) ;} ;
struct TYPE_15__ {int debug; TYPE_3__ iif; int /*<<< orphan*/  myid; } ;
struct TYPE_12__ {scalar_t__ userdata; } ;
struct TYPE_13__ {TYPE_4__ lli; } ;

/* Variables and functions */
 int /*<<< orphan*/  ISDN_STAT_FAXIND ; 
 int L1_DEB_HSCX ; 
 int /*<<< orphan*/  debugl1 (TYPE_8__*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (TYPE_6__*) ; 

__attribute__((used)) static void
ll_deliver_faxstat(struct BCState *bcs, u_char status)
{
        isdn_ctrl ic;
	struct Channel *chanp = (struct Channel *) bcs->st->lli.userdata;
 
	if (bcs->cs->debug & L1_DEB_HSCX)
		debugl1(bcs->cs, "HL->LL FAXIND %x", status);
	ic.driver = bcs->cs->myid;
	ic.command = ISDN_STAT_FAXIND;
	ic.arg = chanp->chan;
	ic.parm.aux.cmd = status;
	bcs->cs->iif.statcallb(&ic);
}