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
struct bc_state {TYPE_3__* cs; int /*<<< orphan*/  channel; } ;
struct TYPE_6__ {int /*<<< orphan*/  errcode; } ;
struct TYPE_9__ {TYPE_1__ parm; int /*<<< orphan*/  arg; int /*<<< orphan*/  command; int /*<<< orphan*/  driver; } ;
typedef  TYPE_4__ isdn_ctrl ;
struct TYPE_7__ {int /*<<< orphan*/  (* statcallb ) (TYPE_4__*) ;} ;
struct TYPE_8__ {TYPE_2__ iif; int /*<<< orphan*/  myid; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG_CMD ; 
 int /*<<< orphan*/  ISDN_STAT_L1ERR ; 
 int /*<<< orphan*/  ISDN_STAT_L1ERR_RECV ; 
 int /*<<< orphan*/  gig_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  stub1 (TYPE_4__*) ; 

__attribute__((used)) static inline void gigaset_isdn_rcv_err(struct bc_state *bcs)
{
	isdn_ctrl response;

	/* error -> LL */
	gig_dbg(DEBUG_CMD, "sending L1ERR");
	response.driver = bcs->cs->myid;
	response.command = ISDN_STAT_L1ERR;
	response.arg = bcs->channel;
	response.parm.errcode = ISDN_STAT_L1ERR_RECV;
	bcs->cs->iif.statcallb(&response);
}