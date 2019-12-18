#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {char* DisconnectFlag; scalar_t__ path_test; int /*<<< orphan*/  trace_prop; } ;
struct TYPE_8__ {char* fddiSMTECMState; } ;
struct TYPE_6__ {int numphys; } ;
struct s_smc {TYPE_4__ e; TYPE_3__ mib; TYPE_1__ s; struct s_phy* y; } ;
struct s_plc {int ebuf_cont; scalar_t__ p_state; int p_bits; int p_start; int /*<<< orphan*/  parity_err; int /*<<< orphan*/  np_err; int /*<<< orphan*/  b_hls; int /*<<< orphan*/  b_ils; int /*<<< orphan*/  b_qls; int /*<<< orphan*/  b_tne; int /*<<< orphan*/  b_tpc; int /*<<< orphan*/  b_pcs; int /*<<< orphan*/  tpc_exp; int /*<<< orphan*/  mini_ctr; int /*<<< orphan*/  vsym_ctr; int /*<<< orphan*/  phyinv; int /*<<< orphan*/  ebuf_err; int /*<<< orphan*/  soft_err; } ;
struct TYPE_7__ {int lem_errors; scalar_t__ lem_on; } ;
struct s_phy {int* r_val; int phy_name; scalar_t__ tr_flag; TYPE_5__* mib; int /*<<< orphan*/  curr_ls; TYPE_2__ lem; struct s_plc plc; } ;
struct TYPE_10__ {char* fddiPORTPCMState; int fddiPORTLem_Ct; int /*<<< orphan*/  fddiPORTEBError_Ct; } ;

/* Variables and functions */
 int /*<<< orphan*/  DB_PCMN (int,char*,int,...) ; 
 int /*<<< orphan*/  EC_DISCONNECT ; 
 int /*<<< orphan*/  EC_PATH_TEST ; 
 int /*<<< orphan*/  EC_TRACE_PROP ; 
 int /*<<< orphan*/  ENTITY_BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ENTITY_PHY (int) ; 
 scalar_t__ EVENT_ECM ; 
 scalar_t__ EVENT_PCM ; 
 scalar_t__ FALSE ; 
 char* PC2_TRACE ; 
 char* PC8_ACTIVE ; 
 int /*<<< orphan*/  PC_HLS ; 
 int /*<<< orphan*/  PC_ILS ; 
 int /*<<< orphan*/  PC_JOIN ; 
 int /*<<< orphan*/  PC_MLS ; 
 int /*<<< orphan*/  PC_QLS ; 
 int /*<<< orphan*/  PC_SIGNAL ; 
 int /*<<< orphan*/  PC_START ; 
 int /*<<< orphan*/  PLC (int,int /*<<< orphan*/ ) ; 
 int PLC_REV_MASK ; 
 int PLC_REV_SN3 ; 
 int PL_BREAK_REASON ; 
#define  PL_B_HLS 137 
#define  PL_B_ILS 136 
#define  PL_B_PCS 135 
#define  PL_B_QLS 134 
#define  PL_B_TNE 133 
#define  PL_B_TPC 132 
 int /*<<< orphan*/  PL_CNTRL_B ; 
 unsigned int PL_EBUF_ERR ; 
 int /*<<< orphan*/  PL_INTR_MASK ; 
#define  PL_I_HALT 131 
#define  PL_I_IDLE 130 
#define  PL_I_MASTR 129 
#define  PL_I_QUIET 128 
 unsigned int PL_LE_CTR ; 
 int /*<<< orphan*/  PL_LE_THRESHOLD ; 
 int /*<<< orphan*/  PL_LINK_ERR_CTR ; 
 unsigned int PL_LSDO ; 
 unsigned int PL_LS_MATCH ; 
 int PL_MATCH_LS ; 
 unsigned int PL_MINI_CTR ; 
 unsigned int PL_NP_ERR ; 
 unsigned int PL_PARITY_ERR ; 
 unsigned int PL_PCM_BREAK ; 
 unsigned int PL_PCM_CODE ; 
 unsigned int PL_PCM_ENABLED ; 
 unsigned int PL_PHYINV ; 
 int /*<<< orphan*/  PL_RCV_VECTOR ; 
 unsigned int PL_SELF_TEST ; 
 int /*<<< orphan*/  PL_STATUS_A ; 
 int /*<<< orphan*/  PL_STATUS_B ; 
 unsigned int PL_TNE_EXPIRED ; 
 unsigned int PL_TPC_EXPIRED ; 
 unsigned int PL_TRACE_PROP ; 
 unsigned int PL_VSYM_CTR ; 
 scalar_t__ PS_LCT ; 
 scalar_t__ PT_PASSED ; 
 scalar_t__ PT_PENDING ; 
 int /*<<< orphan*/  SMT_E0136 ; 
 int /*<<< orphan*/  SMT_E0136_MSG ; 
 int /*<<< orphan*/  SMT_ERR_LOG (struct s_smc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  drv_reset_indication (struct s_smc*) ; 
 int get_pcmstate (struct s_smc*,int) ; 
 int inpw (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outpw (int /*<<< orphan*/ ,int) ; 
 unsigned int plc_imsk_na ; 
 int /*<<< orphan*/  queue_event (struct s_smc*,scalar_t__,int /*<<< orphan*/ ) ; 

void plc_irq(struct s_smc *smc, int np, unsigned int cmd)
/* int np;	PHY index */
{
	struct s_phy *phy = &smc->y[np] ;
	struct s_plc *plc = &phy->plc ;
	int		n ;
#ifdef	SUPERNET_3
	int		corr_mask ;
#endif	/* SUPERNET_3 */
	int		i ;

	if (np >= smc->s.numphys) {
		plc->soft_err++ ;
		return ;
	}
	if (cmd & PL_EBUF_ERR) {	/* elastic buff. det. over-|underflow*/
		/*
		 * Check whether the SRF Condition occurred.
		 */
		if (!plc->ebuf_cont && phy->mib->fddiPORTPCMState == PC8_ACTIVE){
			/*
			 * This is the real Elasticity Error.
			 * More than one in a row are treated as a
			 * single one.
			 * Only count this in the active state.
			 */
			phy->mib->fddiPORTEBError_Ct ++ ;

		}

		plc->ebuf_err++ ;
		if (plc->ebuf_cont <= 1000) {
			/*
			 * Prevent counter from being wrapped after
			 * hanging years in that interrupt.
			 */
			plc->ebuf_cont++ ;	/* Ebuf continous error */
		}

#ifdef	SUPERNET_3
		if (plc->ebuf_cont == 1000 &&
			((inpw(PLC(np,PL_STATUS_A)) & PLC_REV_MASK) ==
			PLC_REV_SN3)) {
			/*
			 * This interrupt remeained high for at least
			 * 1000 consecutive interrupt calls.
			 *
			 * This is caused by a hardware error of the
			 * ORION part of the Supernet III chipset.
			 *
			 * Disable this bit from the mask.
			 */
			corr_mask = (plc_imsk_na & ~PL_EBUF_ERR) ;
			outpw(PLC(np,PL_INTR_MASK),corr_mask);

			/*
			 * Disconnect from the ring.
			 * Call the driver with the reset indication.
			 */
			queue_event(smc,EVENT_ECM,EC_DISCONNECT) ;

			/*
			 * Make an error log entry.
			 */
			SMT_ERR_LOG(smc,SMT_E0136, SMT_E0136_MSG) ;

			/*
			 * Indicate the Reset.
			 */
			drv_reset_indication(smc) ;
		}
#endif	/* SUPERNET_3 */
	} else {
		/* Reset the continous error variable */
		plc->ebuf_cont = 0 ;	/* reset Ebuf continous error */
	}
	if (cmd & PL_PHYINV) {		/* physical layer invalid signal */
		plc->phyinv++ ;
	}
	if (cmd & PL_VSYM_CTR) {	/* violation symbol counter has incr.*/
		plc->vsym_ctr++ ;
	}
	if (cmd & PL_MINI_CTR) {	/* dep. on PLC_CNTRL_A's MINI_CTR_INT*/
		plc->mini_ctr++ ;
	}
	if (cmd & PL_LE_CTR) {		/* link error event counter */
		int	j ;

		/*
		 * note: PL_LINK_ERR_CTR MUST be read to clear it
		 */
		j = inpw(PLC(np,PL_LE_THRESHOLD)) ;
		i = inpw(PLC(np,PL_LINK_ERR_CTR)) ;

		if (i < j) {
			/* wrapped around */
			i += 256 ;
		}

		if (phy->lem.lem_on) {
			/* Note: Lem errors shall only be counted when
			 * link is ACTIVE or LCT is active.
			 */
			phy->lem.lem_errors += i ;
			phy->mib->fddiPORTLem_Ct += i ;
		}
	}
	if (cmd & PL_TPC_EXPIRED) {	/* TPC timer reached zero */
		if (plc->p_state == PS_LCT) {
			/*
			 * end of LCT
			 */
			;
		}
		plc->tpc_exp++ ;
	}
	if (cmd & PL_LS_MATCH) {	/* LS == LS in PLC_CNTRL_B's MATCH_LS*/
		switch (inpw(PLC(np,PL_CNTRL_B)) & PL_MATCH_LS) {
		case PL_I_IDLE :	phy->curr_ls = PC_ILS ;		break ;
		case PL_I_HALT :	phy->curr_ls = PC_HLS ;		break ;
		case PL_I_MASTR :	phy->curr_ls = PC_MLS ;		break ;
		case PL_I_QUIET :	phy->curr_ls = PC_QLS ;		break ;
		}
	}
	if (cmd & PL_PCM_BREAK) {	/* PCM has entered the BREAK state */
		int	reason;

		reason = inpw(PLC(np,PL_STATUS_B)) & PL_BREAK_REASON ;

		switch (reason) {
		case PL_B_PCS :		plc->b_pcs++ ;	break ;
		case PL_B_TPC :		plc->b_tpc++ ;	break ;
		case PL_B_TNE :		plc->b_tne++ ;	break ;
		case PL_B_QLS :		plc->b_qls++ ;	break ;
		case PL_B_ILS :		plc->b_ils++ ;	break ;
		case PL_B_HLS :		plc->b_hls++ ;	break ;
		}

		/*jd 05-Aug-1999 changed: Bug #10419 */
		DB_PCMN(1,"PLC %d: MDcF = %x\n", np, smc->e.DisconnectFlag);
		if (smc->e.DisconnectFlag == FALSE) {
			DB_PCMN(1,"PLC %d: restart (reason %x)\n", np, reason);
			queue_event(smc,EVENT_PCM+np,PC_START) ;
		}
		else {
			DB_PCMN(1,"PLC %d: NO!! restart (reason %x)\n", np, reason);
		}
		return ;
	}
	/*
	 * If both CODE & ENABLE are set ignore enable
	 */
	if (cmd & PL_PCM_CODE) { /* receive last sign.-bit | LCT complete */
		queue_event(smc,EVENT_PCM+np,PC_SIGNAL) ;
		n = inpw(PLC(np,PL_RCV_VECTOR)) ;
		for (i = 0 ; i < plc->p_bits ; i++) {
			phy->r_val[plc->p_start+i] = n & 1 ;
			n >>= 1 ;
		}
	}
	else if (cmd & PL_PCM_ENABLED) { /* asserted SC_JOIN, scrub.completed*/
		queue_event(smc,EVENT_PCM+np,PC_JOIN) ;
	}
	if (cmd & PL_TRACE_PROP) {	/* MLS while PC8_ACTIV || PC2_TRACE */
		/*PC22b*/
		if (!phy->tr_flag) {
			DB_PCMN(1,"PCM : irq TRACE_PROP %d %d\n",
				np,smc->mib.fddiSMTECMState) ;
			phy->tr_flag = TRUE ;
			smc->e.trace_prop |= ENTITY_BIT(ENTITY_PHY(np)) ;
			queue_event(smc,EVENT_ECM,EC_TRACE_PROP) ;
		}
	}
	/*
	 * filter PLC glitch ???
	 * QLS || HLS only while in PC2_TRACE state
	 */
	if ((cmd & PL_SELF_TEST) && (phy->mib->fddiPORTPCMState == PC2_TRACE)) {
		/*PC22a*/
		if (smc->e.path_test == PT_PASSED) {
			DB_PCMN(1,"PCM : state = %s %d\n", get_pcmstate(smc,np),
				phy->mib->fddiPORTPCMState) ;

			smc->e.path_test = PT_PENDING ;
			queue_event(smc,EVENT_ECM,EC_PATH_TEST) ;
		}
	}
	if (cmd & PL_TNE_EXPIRED) {	/* TNE: length of noise events */
		/* break_required (TNE > NS_Max) */
		if (phy->mib->fddiPORTPCMState == PC8_ACTIVE) {
			if (!phy->tr_flag) {
			   DB_PCMN(1,"PCM %c : PC81 %s\n",phy->phy_name,"NSE");
			   queue_event(smc,EVENT_PCM+np,PC_START) ;
			   return ;
			}
		}
	}
#if	0
	if (cmd & PL_NP_ERR) {		/* NP has requested to r/w an inv reg*/
		/*
		 * It's a bug by AMD
		 */
		plc->np_err++ ;
	}
	/* pin inactiv (GND) */
	if (cmd & PL_PARITY_ERR) {	/* p. error dedected on TX9-0 inp */
		plc->parity_err++ ;
	}
	if (cmd & PL_LSDO) {		/* carrier detected */
		;
	}
#endif
}