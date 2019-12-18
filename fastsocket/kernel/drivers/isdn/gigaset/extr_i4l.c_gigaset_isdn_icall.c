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
struct TYPE_8__ {int (* statcallb ) (TYPE_4__*) ;} ;
struct cardstate {int /*<<< orphan*/  dev; TYPE_3__ iif; int /*<<< orphan*/  myid; } ;
struct bc_state {int /*<<< orphan*/  chstate; scalar_t__ channel; } ;
struct at_state_t {scalar_t__* str_var; struct bc_state* bcs; struct cardstate* cs; } ;
struct TYPE_6__ {int si1; int si2; scalar_t__* eazmsn; scalar_t__* phone; scalar_t__ plan; scalar_t__ screen; } ;
struct TYPE_7__ {TYPE_1__ setup; } ;
struct TYPE_9__ {int /*<<< orphan*/  driver; scalar_t__ arg; int /*<<< orphan*/  command; TYPE_2__ parm; } ;
typedef  TYPE_4__ isdn_ctrl ;

/* Variables and functions */
 int /*<<< orphan*/  CHS_NOTIFY_LL ; 
 int /*<<< orphan*/  DEBUG_CMD ; 
 int ICALL_ACCEPT ; 
 int ICALL_IGNORE ; 
 int ICALL_REJECT ; 
 int /*<<< orphan*/  ISDN_STAT_ICALL ; 
 int /*<<< orphan*/  ISDN_STAT_ICALLW ; 
 size_t STR_NMBR ; 
 size_t STR_ZBC ; 
 size_t STR_ZCPN ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  dev_notice (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  gig_dbg (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  strcmp (scalar_t__,char*) ; 
 int /*<<< orphan*/  strncpy (scalar_t__*,scalar_t__,int) ; 
 int stub1 (TYPE_4__*) ; 

int gigaset_isdn_icall(struct at_state_t *at_state)
{
	struct cardstate *cs = at_state->cs;
	struct bc_state *bcs = at_state->bcs;
	isdn_ctrl response;
	int retval;

	/* fill ICALL structure */
	response.parm.setup.si1 = 0;	/* default: unknown */
	response.parm.setup.si2 = 0;
	response.parm.setup.screen = 0;	//FIXME how to set these?
	response.parm.setup.plan = 0;
	if (!at_state->str_var[STR_ZBC]) {
		/* no BC (internal call): assume speech, A-law */
		response.parm.setup.si1 = 1;
	} else if (!strcmp(at_state->str_var[STR_ZBC], "8890")) {
		/* unrestricted digital information */
		response.parm.setup.si1 = 7;
	} else if (!strcmp(at_state->str_var[STR_ZBC], "8090A3")) {
		/* speech, A-law */
		response.parm.setup.si1 = 1;
	} else if (!strcmp(at_state->str_var[STR_ZBC], "9090A3")) {
		/* 3,1 kHz audio, A-law */
		response.parm.setup.si1 = 1;
		response.parm.setup.si2 = 2;
	} else {
		dev_warn(cs->dev, "RING ignored - unsupported BC %s\n",
		     at_state->str_var[STR_ZBC]);
		return ICALL_IGNORE;
	}
	if (at_state->str_var[STR_NMBR]) {
		strncpy(response.parm.setup.phone, at_state->str_var[STR_NMBR],
			sizeof response.parm.setup.phone - 1);
		response.parm.setup.phone[sizeof response.parm.setup.phone - 1] = 0;
	} else
		response.parm.setup.phone[0] = 0;
	if (at_state->str_var[STR_ZCPN]) {
		strncpy(response.parm.setup.eazmsn, at_state->str_var[STR_ZCPN],
			sizeof response.parm.setup.eazmsn - 1);
		response.parm.setup.eazmsn[sizeof response.parm.setup.eazmsn - 1] = 0;
	} else
		response.parm.setup.eazmsn[0] = 0;

	if (!bcs) {
		dev_notice(cs->dev, "no channel for incoming call\n");
		response.command = ISDN_STAT_ICALLW;
		response.arg = 0; //FIXME
	} else {
		gig_dbg(DEBUG_CMD, "Sending ICALL");
		response.command = ISDN_STAT_ICALL;
		response.arg = bcs->channel; //FIXME
	}
	response.driver = cs->myid;
	retval = cs->iif.statcallb(&response);
	gig_dbg(DEBUG_CMD, "Response: %d", retval);
	switch (retval) {
	case 0:	/* no takers */
		return ICALL_IGNORE;
	case 1:	/* alerting */
		bcs->chstate |= CHS_NOTIFY_LL;
		return ICALL_ACCEPT;
	case 2:	/* reject */
		return ICALL_REJECT;
	case 3:	/* incomplete */
		dev_warn(cs->dev,
		       "LL requested unsupported feature: Incomplete Number\n");
		return ICALL_IGNORE;
	case 4:	/* proceeding */
		/* Gigaset will send ALERTING anyway.
		 * There doesn't seem to be a way to avoid this.
		 */
		return ICALL_ACCEPT;
	case 5:	/* deflect */
		dev_warn(cs->dev,
			 "LL requested unsupported feature: Call Deflection\n");
		return ICALL_IGNORE;
	default:
		dev_err(cs->dev, "LL error %d on ICALL\n", retval);
		return ICALL_IGNORE;
	}
}