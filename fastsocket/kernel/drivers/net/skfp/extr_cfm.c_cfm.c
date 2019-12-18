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
struct TYPE_8__ {int fddiSMTCF_State; int fddiSMTPeerWrapFlag; TYPE_3__* m; } ;
struct s_smc {TYPE_4__ mib; TYPE_2__* y; } ;
struct TYPE_7__ {int /*<<< orphan*/  fddiMACDownstreamPORTType; } ;
struct TYPE_6__ {scalar_t__ pc_mode; TYPE_1__* mib; } ;
struct TYPE_5__ {scalar_t__ fddiPORTNeighborType; } ;

/* Variables and functions */
 int AFLAG ; 
 int /*<<< orphan*/  DB_CFM (char*,char*,int /*<<< orphan*/ ) ; 
 int FALSE ; 
 int /*<<< orphan*/  INDEX_MAC ; 
 size_t MAC0 ; 
 size_t PA ; 
 size_t PB ; 
 scalar_t__ PM_PEER ; 
 size_t PS ; 
 int SC10_C_WRAP_B ; 
 int SC11_C_WRAP_S ; 
 int SC9_C_WRAP_A ; 
 int /*<<< orphan*/  SMT_COND_SMT_PEER_WRAP ; 
 int /*<<< orphan*/  SMT_EVENT_MAC_PATH_CHANGE ; 
 int TRUE ; 
 scalar_t__ TS ; 
 int /*<<< orphan*/  all_selection_criteria (struct s_smc*) ; 
 int /*<<< orphan*/  cem_priv_state (struct s_smc*,int) ; 
 int /*<<< orphan*/ * cf_to_ptype ; 
 char** cfm_events ; 
 int /*<<< orphan*/  cfm_fsm (struct s_smc*,int) ; 
 int /*<<< orphan*/  cfm_state_change (struct s_smc*,int) ; 
 int /*<<< orphan*/ * cfm_states ; 
 int /*<<< orphan*/  smt_srf_event (struct s_smc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

void cfm(struct s_smc *smc, int event)
{
	int	state ;		/* remember last state */
	int	cond ;
	int	oldstate ;

	/* We will do the following: */
	/*  - compute the variable WC_Flag for every port (This is where */
	/*    we can extend the requested path checking !!) */
	/*  - do the old (SMT 6.2 like) state machine */
	/*  - do the resulting station states */

	all_selection_criteria (smc);

	/* We will check now whether a state transition is allowed or not */
	/*  - change the portstates */
	cem_priv_state (smc, event);

	oldstate = smc->mib.fddiSMTCF_State ;
	do {
		DB_CFM("CFM : state %s%s",
			(smc->mib.fddiSMTCF_State & AFLAG) ? "ACTIONS " : "",
			cfm_states[smc->mib.fddiSMTCF_State & ~AFLAG]) ;
		DB_CFM(" event %s\n",cfm_events[event],0) ;
		state = smc->mib.fddiSMTCF_State ;
		cfm_fsm(smc,event) ;
		event = 0 ;
	} while (state != smc->mib.fddiSMTCF_State) ;

#ifndef	SLIM_SMT
	/*
	 * check peer wrap condition
	 */
	cond = FALSE ;
	if (	(smc->mib.fddiSMTCF_State == SC9_C_WRAP_A &&
		smc->y[PA].pc_mode == PM_PEER) 	||
		(smc->mib.fddiSMTCF_State == SC10_C_WRAP_B &&
		smc->y[PB].pc_mode == PM_PEER) 	||
		(smc->mib.fddiSMTCF_State == SC11_C_WRAP_S &&
		smc->y[PS].pc_mode == PM_PEER &&
		smc->y[PS].mib->fddiPORTNeighborType != TS ) ) {
			cond = TRUE ;
	}
	if (cond != smc->mib.fddiSMTPeerWrapFlag)
		smt_srf_event(smc,SMT_COND_SMT_PEER_WRAP,0,cond) ;

#if	0
	/*
	 * Don't send ever MAC_PATH_CHANGE events. Our MAC is hard-wired
	 * to the primary path.
	 */
	/*
	 * path change
	 */
	if (smc->mib.fddiSMTCF_State != oldstate) {
		smt_srf_event(smc,SMT_EVENT_MAC_PATH_CHANGE,INDEX_MAC,0) ;
	}
#endif
#endif	/* no SLIM_SMT */

	/*
	 * set MAC port type
	 */
	smc->mib.m[MAC0].fddiMACDownstreamPORTType =
		cf_to_ptype[smc->mib.fddiSMTCF_State] ;
	cfm_state_change(smc,(int)smc->mib.fddiSMTCF_State) ;
}