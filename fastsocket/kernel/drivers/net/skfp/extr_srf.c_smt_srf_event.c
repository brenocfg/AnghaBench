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
typedef  int u_long ;
struct s_srf_evc {int* evc_cond_state; int evc_rep_required; void** evc_multiple; } ;
struct TYPE_4__ {void* TSR; int sr_state; int SRThreshold; void* any_report; } ;
struct TYPE_3__ {int /*<<< orphan*/  fddiSMTStatRptPolicy; int /*<<< orphan*/  fddiSMTTransitionTimeStamp; } ;
struct s_smc {TYPE_2__ srf; TYPE_1__ mib; } ;

/* Variables and functions */
 int /*<<< orphan*/  DB_SMT (char*,char*,int) ; 
 void* FALSE ; 
 int /*<<< orphan*/  RS_DUPADDR ; 
 int /*<<< orphan*/  RS_SET (struct s_smc*,int /*<<< orphan*/ ) ; 
 int SMT_COND_MAC_DUP_ADDR ; 
 scalar_t__ SMT_IS_CONDITION (int) ; 
#define  SR0_WAIT 130 
#define  SR1_HOLDOFF 129 
#define  SR2_DISABLED 128 
 void* THRESHOLD_2 ; 
 int THRESHOLD_32 ; 
 int TICKS_PER_SECOND ; 
 void* TRUE ; 
 int /*<<< orphan*/  clear_all_rep (struct s_smc*) ; 
 struct s_srf_evc* smt_get_evc (struct s_smc*,int,int) ; 
 void* smt_get_time () ; 
 int /*<<< orphan*/  smt_send_srf (struct s_smc*) ; 
 int /*<<< orphan*/  smt_set_timestamp (struct s_smc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snmp_srf_event (struct s_smc*,struct s_srf_evc*) ; 
 char** srf_names ; 

void smt_srf_event(struct s_smc *smc, int code, int index, int cond)
{
	struct s_srf_evc	*evc ;
	int			cond_asserted = 0 ;
	int			cond_deasserted = 0 ;
	int			event_occurred = 0 ;
	int			tsr ;
	int			T_Limit = 2*TICKS_PER_SECOND ;

	if (code == SMT_COND_MAC_DUP_ADDR && cond) {
		RS_SET(smc,RS_DUPADDR) ;
	}

	if (code) {
		DB_SMT("SRF: %s index %d\n",srf_names[code],index) ;

		if (!(evc = smt_get_evc(smc,code,index))) {
			DB_SMT("SRF : smt_get_evc() failed\n",0,0) ;
			return ;
		}
		/*
		 * ignore condition if no change
		 */
		if (SMT_IS_CONDITION(code)) {
			if (*evc->evc_cond_state == cond)
				return ;
		}

		/*
		 * set transition time stamp
		 */
		smt_set_timestamp(smc,smc->mib.fddiSMTTransitionTimeStamp) ;
		if (SMT_IS_CONDITION(code)) {
			DB_SMT("SRF: condition is %s\n",cond ? "ON":"OFF",0) ;
			if (cond) {
				*evc->evc_cond_state = TRUE ;
				evc->evc_rep_required = TRUE ;
				smc->srf.any_report = TRUE ;
				cond_asserted = TRUE ;
			}
			else {
				*evc->evc_cond_state = FALSE ;
				cond_deasserted = TRUE ;
			}
		}
		else {
			if (evc->evc_rep_required) {
				*evc->evc_multiple  = TRUE ;
			}
			else {
				evc->evc_rep_required = TRUE ;
				*evc->evc_multiple  = FALSE ;
			}
			smc->srf.any_report = TRUE ;
			event_occurred = TRUE ;
		}
#ifdef	FDDI_MIB
		snmp_srf_event(smc,evc) ;
#endif	/* FDDI_MIB */
	}
	tsr = smt_get_time() - smc->srf.TSR ;

	switch (smc->srf.sr_state) {
	case SR0_WAIT :
		/* SR01a */
		if (cond_asserted && tsr < T_Limit) {
			smc->srf.SRThreshold = THRESHOLD_2 ;
			smc->srf.sr_state = SR1_HOLDOFF ;
			break ;
		}
		/* SR01b */
		if (cond_deasserted && tsr < T_Limit) {
			smc->srf.sr_state = SR1_HOLDOFF ;
			break ;
		}
		/* SR01c */
		if (event_occurred && tsr < T_Limit) {
			smc->srf.sr_state = SR1_HOLDOFF ;
			break ;
		}
		/* SR00b */
		if (cond_asserted && tsr >= T_Limit) {
			smc->srf.SRThreshold = THRESHOLD_2 ;
			smc->srf.TSR = smt_get_time() ;
			smt_send_srf(smc) ;
			break ;
		}
		/* SR00c */
		if (cond_deasserted && tsr >= T_Limit) {
			smc->srf.TSR = smt_get_time() ;
			smt_send_srf(smc) ;
			break ;
		}
		/* SR00d */
		if (event_occurred && tsr >= T_Limit) {
			smc->srf.TSR = smt_get_time() ;
			smt_send_srf(smc) ;
			break ;
		}
		/* SR00e */
		if (smc->srf.any_report && (u_long) tsr >=
			smc->srf.SRThreshold) {
			smc->srf.SRThreshold *= 2 ;
			if (smc->srf.SRThreshold > THRESHOLD_32)
				smc->srf.SRThreshold = THRESHOLD_32 ;
			smc->srf.TSR = smt_get_time() ;
			smt_send_srf(smc) ;
			break ;
		}
		/* SR02 */
		if (!smc->mib.fddiSMTStatRptPolicy) {
			smc->srf.sr_state = SR2_DISABLED ;
			break ;
		}
		break ;
	case SR1_HOLDOFF :
		/* SR10b */
		if (tsr >= T_Limit) {
			smc->srf.sr_state = SR0_WAIT ;
			smc->srf.TSR = smt_get_time() ;
			smt_send_srf(smc) ;
			break ;
		}
		/* SR11a */
		if (cond_asserted) {
			smc->srf.SRThreshold = THRESHOLD_2 ;
		}
		/* SR11b */
		/* SR11c */
		/* handled above */
		/* SR12 */
		if (!smc->mib.fddiSMTStatRptPolicy) {
			smc->srf.sr_state = SR2_DISABLED ;
			break ;
		}
		break ;
	case SR2_DISABLED :
		if (smc->mib.fddiSMTStatRptPolicy) {
			smc->srf.sr_state = SR0_WAIT ;
			smc->srf.TSR = smt_get_time() ;
			smc->srf.SRThreshold = THRESHOLD_2 ;
			clear_all_rep(smc) ;
			break ;
		}
		break ;
	}
}