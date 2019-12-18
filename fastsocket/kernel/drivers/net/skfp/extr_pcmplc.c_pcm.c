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
struct TYPE_2__ {scalar_t__ sas; } ;
struct s_smc {struct s_phy* y; TYPE_1__ s; } ;
struct s_phy {scalar_t__ np; int /*<<< orphan*/  phy_name; struct fddi_mib_p* mib; } ;
struct fddi_mib_p {int fddiPORTPCMState; int fddiPORTPCMStateX; scalar_t__ fddiPORTIndex; } ;

/* Variables and functions */
 int AFLAG ; 
 int /*<<< orphan*/  DB_PCM (char*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  DB_SNMP (char*,int,int) ; 
 scalar_t__ INDEX_PORT ; 
 int PC0_OFF ; 
 int PC2_TRACE ; 
 int PC3_CONNECT ; 
 int PC5_SIGNAL ; 
 int PC8_ACTIVE ; 
 int const PS ; 
 int /*<<< orphan*/  SMT_EVENT_PORT_PATH_CHANGE ; 
 scalar_t__ SMT_SAS ; 
 char** pcm_events ; 
 int /*<<< orphan*/  pcm_fsm (struct s_smc*,struct s_phy*,int) ; 
 int /*<<< orphan*/  pcm_state_change (struct s_smc*,int const,int) ; 
 int /*<<< orphan*/ * pcm_states ; 
 int /*<<< orphan*/  smt_srf_event (struct s_smc*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snmp_fddi_trap (struct s_smc*,int,int) ; 

void pcm(struct s_smc *smc, const int np, int event)
{
	int	state ;
	int	oldstate ;
	struct s_phy	*phy ;
	struct fddi_mib_p	*mib ;

#ifndef	CONCENTRATOR
	/*
	 * ignore 2nd PHY if SAS
	 */
	if ((np != PS) && (smc->s.sas == SMT_SAS))
		return ;
#endif
	phy = &smc->y[np] ;
	mib = phy->mib ;
	oldstate = mib->fddiPORTPCMState ;
	do {
		DB_PCM("PCM %c: state %s",
			phy->phy_name,
			(mib->fddiPORTPCMState & AFLAG) ? "ACTIONS " : "") ;
		DB_PCM("%s, event %s\n",
			pcm_states[mib->fddiPORTPCMState & ~AFLAG],
			pcm_events[event]) ;
		state = mib->fddiPORTPCMState ;
		pcm_fsm(smc,phy,event) ;
		event = 0 ;
	} while (state != mib->fddiPORTPCMState) ;
	/*
	 * because the PLC does the bit signaling for us,
	 * we're always in SIGNAL state
	 * the MIB want's to see CONNECT
	 * we therefore fake an entry in the MIB
	 */
	if (state == PC5_SIGNAL)
		mib->fddiPORTPCMStateX = PC3_CONNECT ;
	else
		mib->fddiPORTPCMStateX = state ;

#ifndef	SLIM_SMT
	/*
	 * path change
	 */
	if (	mib->fddiPORTPCMState != oldstate &&
		((oldstate == PC8_ACTIVE) || (mib->fddiPORTPCMState == PC8_ACTIVE))) {
		smt_srf_event(smc,SMT_EVENT_PORT_PATH_CHANGE,
			(int) (INDEX_PORT+ phy->np),0) ;
	}
#endif

#ifdef FDDI_MIB
	/* check whether a snmp-trap has to be sent */

	if ( mib->fddiPORTPCMState != oldstate ) {
		/* a real state change took place */
		DB_SNMP ("PCM from %d to %d\n", oldstate, mib->fddiPORTPCMState);
		if ( mib->fddiPORTPCMState == PC0_OFF ) {
			/* send first trap */
			snmp_fddi_trap (smc, 1, (int) mib->fddiPORTIndex );
		} else if ( oldstate == PC0_OFF ) {
			/* send second trap */
			snmp_fddi_trap (smc, 2, (int) mib->fddiPORTIndex );
		} else if ( mib->fddiPORTPCMState != PC2_TRACE &&
			oldstate == PC8_ACTIVE ) {
			/* send third trap */
			snmp_fddi_trap (smc, 3, (int) mib->fddiPORTIndex );
		} else if ( mib->fddiPORTPCMState == PC8_ACTIVE ) {
			/* send fourth trap */
			snmp_fddi_trap (smc, 4, (int) mib->fddiPORTIndex );
		}
	}
#endif

	pcm_state_change(smc,np,state) ;
}