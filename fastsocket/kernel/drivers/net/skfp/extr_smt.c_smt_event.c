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
typedef  int u_long ;
struct TYPE_4__ {scalar_t__ please_reconnect; int smt_last_lem; int smt_last_notify; int smt_tvu; int smt_tvd; int* last_tok_time; int /*<<< orphan*/  smt_timer; scalar_t__* pend; } ;
struct TYPE_5__ {int fddiSMTTT_Notify; struct fddi_mib_m* m; } ;
struct s_smc {TYPE_1__ sm; TYPE_2__ mib; struct s_phy* y; } ;
struct s_phy {TYPE_3__* mib; scalar_t__ np; } ;
struct fddi_mib_m {int fddiMACLost_Ct; int fddiMACOld_Lost_Ct; int fddiMACError_Ct; int fddiMACOld_Error_Ct; int fddiMACFrame_Ct; int fddiMACOld_Frame_Ct; scalar_t__ fddiMACFrameErrorRatio; scalar_t__ fddiMACFrameErrorThreshold; int fddiMACFrameErrorFlag; int fddiMACNotCopied_Ct; int fddiMACOld_NotCopied_Ct; int fddiMACCopied_Ct; int fddiMACOld_Copied_Ct; scalar_t__ fddiMACNotCopiedRatio; scalar_t__ fddiMACNotCopiedThreshold; int fddiMACNotCopiedFlag; void* fddiMACDownstreamNbr; void* fddiMACOldDownstreamNbr; int /*<<< orphan*/  fddiMACUNDA_Flag; void* fddiMACUpstreamNbr; void* fddiMACOldUpstreamNbr; } ;
struct TYPE_6__ {int fddiPORTEBError_Ct; int fddiPORTOldEBError_Ct; int /*<<< orphan*/  fddiPORTHardwarePresent; } ;

/* Variables and functions */
 int /*<<< orphan*/  DB_SMT (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EC_CONNECT ; 
 int /*<<< orphan*/  EVENT_ECM ; 
 int /*<<< orphan*/  EVENT_SMT ; 
 int /*<<< orphan*/  EV_TOKEN (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  FC_SMT_NSA ; 
 int INDEX_MAC ; 
 scalar_t__ INDEX_PORT ; 
 size_t MAC0 ; 
 int NUMMACS ; 
 int NUMPHYS ; 
 int /*<<< orphan*/  SMT_COND_MAC_FRAME_ERROR ; 
 int /*<<< orphan*/  SMT_COND_MAC_NOT_COPIED ; 
 int /*<<< orphan*/  SMT_COND_PORT_EB_ERROR ; 
 int /*<<< orphan*/  SMT_EVENT_MAC_NEIGHBOR_CHANGE ; 
 int /*<<< orphan*/  SMT_REQUEST ; 
 size_t SMT_TID_NIF ; 
 void* SMT_Unknown ; 
 int SM_FAST ; 
 int /*<<< orphan*/  SM_TIMER ; 
 int TICKS_PER_SECOND ; 
 void* div_ratio (int,int) ; 
 int /*<<< orphan*/  ess_timer_poll (struct s_smc*) ; 
 int /*<<< orphan*/  fddi_broadcast ; 
 int /*<<< orphan*/  is_equal (void**,void**) ; 
 int /*<<< orphan*/  mac_update_counter (struct s_smc*) ; 
 int /*<<< orphan*/  queue_event (struct s_smc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sba_timer_poll (struct s_smc*) ; 
 int /*<<< orphan*/  sm_lem_evaluate (struct s_smc*) ; 
 int /*<<< orphan*/  smt_emulate_token_ct (struct s_smc*,int) ; 
 scalar_t__ smt_get_tid (struct s_smc*) ; 
 int smt_get_time () ; 
 int /*<<< orphan*/  smt_send_nif (struct s_smc*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smt_srf_event (struct s_smc*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  smt_start_watchdog (struct s_smc*) ; 
 int /*<<< orphan*/  smt_timer_poll (struct s_smc*) ; 
 int /*<<< orphan*/  smt_timer_start (struct s_smc*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  update_dac (struct s_smc*,int /*<<< orphan*/ ) ; 

void smt_event(struct s_smc *smc, int event)
{
	u_long		time ;
#ifndef SMT_REAL_TOKEN_CT
	int		i ;
#endif


	if (smc->sm.please_reconnect) {
		smc->sm.please_reconnect -- ;
		if (smc->sm.please_reconnect == 0) {
			/* Counted down */
			queue_event(smc,EVENT_ECM,EC_CONNECT) ;
		}
	}

	if (event == SM_FAST)
		return ;

	/*
	 * timer for periodic cleanup in driver
	 * reset and start the watchdog (FM2)
	 * ESS timer
	 * SBA timer
	 */
	smt_timer_poll(smc) ;
	smt_start_watchdog(smc) ;
#ifndef	SLIM_SMT
#ifndef BOOT
#ifdef	ESS
	ess_timer_poll(smc) ;
#endif
#endif
#ifdef	SBA
	sba_timer_poll(smc) ;
#endif

	smt_srf_event(smc,0,0,0) ;

#endif	/* no SLIM_SMT */

	time = smt_get_time() ;

	if (time - smc->sm.smt_last_lem >= TICKS_PER_SECOND*8) {
		/*
		 * Use 8 sec. for the time intervall, it simplifies the
		 * LER estimation.
		 */
		struct fddi_mib_m	*mib ;
		u_long			upper ;
		u_long			lower ;
		int			cond ;
		int			port;
		struct s_phy		*phy ;
		/*
		 * calculate LEM bit error rate
		 */
		sm_lem_evaluate(smc) ;
		smc->sm.smt_last_lem = time ;

		/*
		 * check conditions
		 */
#ifndef	SLIM_SMT
		mac_update_counter(smc) ;
		mib = smc->mib.m ;
		upper =
		(mib->fddiMACLost_Ct - mib->fddiMACOld_Lost_Ct) +
		(mib->fddiMACError_Ct - mib->fddiMACOld_Error_Ct) ;
		lower =
		(mib->fddiMACFrame_Ct - mib->fddiMACOld_Frame_Ct) +
		(mib->fddiMACLost_Ct - mib->fddiMACOld_Lost_Ct) ;
		mib->fddiMACFrameErrorRatio = div_ratio(upper,lower) ;

		cond =
			((!mib->fddiMACFrameErrorThreshold &&
			mib->fddiMACError_Ct != mib->fddiMACOld_Error_Ct) ||
			(mib->fddiMACFrameErrorRatio >
			mib->fddiMACFrameErrorThreshold)) ;

		if (cond != mib->fddiMACFrameErrorFlag)
			smt_srf_event(smc,SMT_COND_MAC_FRAME_ERROR,
				INDEX_MAC,cond) ;

		upper =
		(mib->fddiMACNotCopied_Ct - mib->fddiMACOld_NotCopied_Ct) ;
		lower =
		upper +
		(mib->fddiMACCopied_Ct - mib->fddiMACOld_Copied_Ct) ;
		mib->fddiMACNotCopiedRatio = div_ratio(upper,lower) ;

		cond =
			((!mib->fddiMACNotCopiedThreshold &&
			mib->fddiMACNotCopied_Ct !=
				mib->fddiMACOld_NotCopied_Ct)||
			(mib->fddiMACNotCopiedRatio >
			mib->fddiMACNotCopiedThreshold)) ;

		if (cond != mib->fddiMACNotCopiedFlag)
			smt_srf_event(smc,SMT_COND_MAC_NOT_COPIED,
				INDEX_MAC,cond) ;

		/*
		 * set old values
		 */
		mib->fddiMACOld_Frame_Ct = mib->fddiMACFrame_Ct ;
		mib->fddiMACOld_Copied_Ct = mib->fddiMACCopied_Ct ;
		mib->fddiMACOld_Error_Ct = mib->fddiMACError_Ct ;
		mib->fddiMACOld_Lost_Ct = mib->fddiMACLost_Ct ;
		mib->fddiMACOld_NotCopied_Ct = mib->fddiMACNotCopied_Ct ;

		/*
		 * Check port EBError Condition
		 */
		for (port = 0; port < NUMPHYS; port ++) {
			phy = &smc->y[port] ;

			if (!phy->mib->fddiPORTHardwarePresent) {
				continue;
			}

			cond = (phy->mib->fddiPORTEBError_Ct -
				phy->mib->fddiPORTOldEBError_Ct > 5) ;

			/* If ratio is more than 5 in 8 seconds
			 * Set the condition.
			 */
			smt_srf_event(smc,SMT_COND_PORT_EB_ERROR,
				(int) (INDEX_PORT+ phy->np) ,cond) ;

			/*
			 * set old values
			 */
			phy->mib->fddiPORTOldEBError_Ct =
				phy->mib->fddiPORTEBError_Ct ;
		}

#endif	/* no SLIM_SMT */
	}

#ifndef	SLIM_SMT

	if (time - smc->sm.smt_last_notify >= (u_long)
		(smc->mib.fddiSMTTT_Notify * TICKS_PER_SECOND) ) {
		/*
		 * we can either send an announcement or a request
		 * a request will trigger a reply so that we can update
		 * our dna
		 * note: same tid must be used until reply is received
		 */
		if (!smc->sm.pend[SMT_TID_NIF])
			smc->sm.pend[SMT_TID_NIF] = smt_get_tid(smc) ;
		smt_send_nif(smc,&fddi_broadcast, FC_SMT_NSA,
			smc->sm.pend[SMT_TID_NIF], SMT_REQUEST,0) ;
		smc->sm.smt_last_notify = time ;
	}

	/*
	 * check timer
	 */
	if (smc->sm.smt_tvu &&
	    time - smc->sm.smt_tvu > 228*TICKS_PER_SECOND) {
		DB_SMT("SMT : UNA expired\n",0,0) ;
		smc->sm.smt_tvu = 0 ;

		if (!is_equal(&smc->mib.m[MAC0].fddiMACUpstreamNbr,
			&SMT_Unknown)){
			/* Do not update unknown address */
			smc->mib.m[MAC0].fddiMACOldUpstreamNbr=
				smc->mib.m[MAC0].fddiMACUpstreamNbr ;
		}
		smc->mib.m[MAC0].fddiMACUpstreamNbr = SMT_Unknown ;
		smc->mib.m[MAC0].fddiMACUNDA_Flag = FALSE ;
		/*
		 * Make sure the fddiMACUNDA_Flag = FALSE is
		 * included in the SRF so we don't generate
		 * a separate SRF for the deassertion of this
		 * condition
		 */
		update_dac(smc,0) ;
		smt_srf_event(smc, SMT_EVENT_MAC_NEIGHBOR_CHANGE,
			INDEX_MAC,0) ;
	}
	if (smc->sm.smt_tvd &&
	    time - smc->sm.smt_tvd > 228*TICKS_PER_SECOND) {
		DB_SMT("SMT : DNA expired\n",0,0) ;
		smc->sm.smt_tvd = 0 ;
		if (!is_equal(&smc->mib.m[MAC0].fddiMACDownstreamNbr,
			&SMT_Unknown)){
			/* Do not update unknown address */
			smc->mib.m[MAC0].fddiMACOldDownstreamNbr=
				smc->mib.m[MAC0].fddiMACDownstreamNbr ;
		}
		smc->mib.m[MAC0].fddiMACDownstreamNbr = SMT_Unknown ;
		smt_srf_event(smc, SMT_EVENT_MAC_NEIGHBOR_CHANGE,
			INDEX_MAC,0) ;
	}

#endif	/* no SLIM_SMT */

#ifndef SMT_REAL_TOKEN_CT
	/*
	 * Token counter emulation section. If hardware supports the token
	 * count, the token counter will be updated in mac_update_counter.
	 */
	for (i = MAC0; i < NUMMACS; i++ ){
		if (time - smc->sm.last_tok_time[i] > 2*TICKS_PER_SECOND ){
			smt_emulate_token_ct( smc, i );
		}
	}
#endif

	smt_timer_start(smc,&smc->sm.smt_timer, (u_long)1000000L,
		EV_TOKEN(EVENT_SMT,SM_TIMER)) ;
}