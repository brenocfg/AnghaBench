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
typedef  void* u_long ;
struct smt_config {int build_ring_map; int /*<<< orphan*/  lct_extended; int /*<<< orphan*/  lct_long; int /*<<< orphan*/  lct_medium; int /*<<< orphan*/  lct_short; int /*<<< orphan*/  mac_d_max; void* rmt_dup_mac_behavior; int /*<<< orphan*/  rmt_t_poll; int /*<<< orphan*/  rmt_t_announce; int /*<<< orphan*/  rmt_t_jam; int /*<<< orphan*/  rmt_t_direct; int /*<<< orphan*/  rmt_t_stuck; int /*<<< orphan*/  rmt_t_non_op; int /*<<< orphan*/  ecm_check_poll; int /*<<< orphan*/  ecm_test_done; int /*<<< orphan*/  ecm_td_min; int /*<<< orphan*/  ecm_in_max; int /*<<< orphan*/  ecm_i_max; int /*<<< orphan*/  pcm_ns_max; int /*<<< orphan*/  pcm_t_next_9; int /*<<< orphan*/  pcm_lc_extended; int /*<<< orphan*/  pcm_lc_long; int /*<<< orphan*/  pcm_lc_medium; int /*<<< orphan*/  pcm_lc_short; int /*<<< orphan*/  pcm_tl_min; int /*<<< orphan*/  pcm_t_out; int /*<<< orphan*/  pcm_c_min; int /*<<< orphan*/  pcm_tb_max; int /*<<< orphan*/  pcm_tb_min; int /*<<< orphan*/  numphys; int /*<<< orphan*/  sas; scalar_t__ attach_s; } ;
struct TYPE_10__ {scalar_t__ pci_fix_value; } ;
struct TYPE_9__ {int timer_count; int /*<<< orphan*/ * sba_reply_pend; void* local_sba_active; void* raf_act_timer_poll; void* sync_bw_available; } ;
struct TYPE_8__ {int fddiESSMinSegmentSize; void* fddiESSSynchTxMode; int /*<<< orphan*/  fddiESSCategory; void* fddiESSMaxTNeg; scalar_t__ fddiESSOverhead; scalar_t__ fddiESSPayload; } ;
struct TYPE_7__ {void** last_tok_time; } ;
struct TYPE_6__ {int /*<<< orphan*/  smc_version; } ;
struct s_smc {TYPE_5__ hw; TYPE_4__ ess; TYPE_3__ mib; struct smt_config s; TYPE_2__ sm; TYPE_1__ os; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEFAULT_CHECK_POLL ; 
 int /*<<< orphan*/  DEFAULT_C_MIN ; 
 int /*<<< orphan*/  DEFAULT_D_MAX ; 
 int /*<<< orphan*/  DEFAULT_IN_MAX ; 
 int /*<<< orphan*/  DEFAULT_I_MAX ; 
 int /*<<< orphan*/  DEFAULT_LCT_EXTEND ; 
 int /*<<< orphan*/  DEFAULT_LCT_LONG ; 
 int /*<<< orphan*/  DEFAULT_LCT_MEDIUM ; 
 int /*<<< orphan*/  DEFAULT_LCT_SHORT ; 
 int /*<<< orphan*/  DEFAULT_LC_EXTENDED ; 
 int /*<<< orphan*/  DEFAULT_LC_LONG ; 
 int /*<<< orphan*/  DEFAULT_LC_MEDIUM ; 
 int /*<<< orphan*/  DEFAULT_LC_SHORT ; 
 int /*<<< orphan*/  DEFAULT_NS_MAX ; 
 int /*<<< orphan*/  DEFAULT_POLL ; 
 int /*<<< orphan*/  DEFAULT_TB_MAX ; 
 int /*<<< orphan*/  DEFAULT_TB_MIN ; 
 int /*<<< orphan*/  DEFAULT_TD_MIN ; 
 int /*<<< orphan*/  DEFAULT_TEST_DONE ; 
 int /*<<< orphan*/  DEFAULT_TL_MIN ; 
 int /*<<< orphan*/  DEFAULT_T_ANNOUNCE ; 
 int /*<<< orphan*/  DEFAULT_T_DIRECT ; 
 int /*<<< orphan*/  DEFAULT_T_JAM ; 
 int /*<<< orphan*/  DEFAULT_T_NEXT_9 ; 
 int /*<<< orphan*/  DEFAULT_T_NON_OP ; 
 int /*<<< orphan*/  DEFAULT_T_OUT ; 
 int /*<<< orphan*/  DEFAULT_T_STUCK ; 
 void* FALSE ; 
 scalar_t__ MS2BCLK (int) ; 
 int NUMMACS ; 
 int /*<<< orphan*/  NUMPHYS ; 
 int /*<<< orphan*/  SB_STATIC ; 
 int /*<<< orphan*/  SMC_VERSION ; 
 int /*<<< orphan*/  SMT_DAS ; 
 void* smt_get_time () ; 
 int /*<<< orphan*/  smt_init_mib (struct s_smc*,int) ; 
 int /*<<< orphan*/  smt_init_sba (struct s_smc*,int) ; 

void smt_reset_defaults(struct s_smc *smc, int level)
{
	struct smt_config	*smt ;
	int			i ;
	u_long			smt_boot_time;


	smt_init_mib(smc,level) ;

	smc->os.smc_version = SMC_VERSION ;
	smt_boot_time = smt_get_time();
	for( i = 0; i < NUMMACS; i++ )
		smc->sm.last_tok_time[i] = smt_boot_time ;
	smt = &smc->s ;
	smt->attach_s = 0 ;
	smt->build_ring_map = 1 ;
	smt->sas = SMT_DAS ;
	smt->numphys = NUMPHYS ;
	smt->pcm_tb_min = DEFAULT_TB_MIN ;
	smt->pcm_tb_max = DEFAULT_TB_MAX ;
	smt->pcm_c_min = DEFAULT_C_MIN ;
	smt->pcm_t_out = DEFAULT_T_OUT ;
	smt->pcm_tl_min = DEFAULT_TL_MIN ;
	smt->pcm_lc_short = DEFAULT_LC_SHORT ;
	smt->pcm_lc_medium = DEFAULT_LC_MEDIUM ;
	smt->pcm_lc_long = DEFAULT_LC_LONG ;
	smt->pcm_lc_extended = DEFAULT_LC_EXTENDED ;
	smt->pcm_t_next_9 = DEFAULT_T_NEXT_9 ;
	smt->pcm_ns_max = DEFAULT_NS_MAX ;
	smt->ecm_i_max = DEFAULT_I_MAX ;
	smt->ecm_in_max = DEFAULT_IN_MAX ;
	smt->ecm_td_min = DEFAULT_TD_MIN ;
	smt->ecm_test_done = DEFAULT_TEST_DONE ;
	smt->ecm_check_poll = DEFAULT_CHECK_POLL ;
	smt->rmt_t_non_op = DEFAULT_T_NON_OP ;
	smt->rmt_t_stuck = DEFAULT_T_STUCK ;
	smt->rmt_t_direct = DEFAULT_T_DIRECT ;
	smt->rmt_t_jam = DEFAULT_T_JAM ;
	smt->rmt_t_announce = DEFAULT_T_ANNOUNCE ;
	smt->rmt_t_poll = DEFAULT_POLL ;
        smt->rmt_dup_mac_behavior = FALSE ;  /* See Struct smt_config */
	smt->mac_d_max = DEFAULT_D_MAX ;

	smt->lct_short = DEFAULT_LCT_SHORT ;
	smt->lct_medium = DEFAULT_LCT_MEDIUM ;
	smt->lct_long = DEFAULT_LCT_LONG ;
	smt->lct_extended = DEFAULT_LCT_EXTEND ;

#ifndef	SLIM_SMT
#ifdef	ESS
	if (level == 0) {
		smc->ess.sync_bw_available = FALSE ;
		smc->mib.fddiESSPayload = 0 ;
		smc->mib.fddiESSOverhead = 0 ;
		smc->mib.fddiESSMaxTNeg = (u_long)(- MS2BCLK(25)) ;
		smc->mib.fddiESSMinSegmentSize = 1 ;
		smc->mib.fddiESSCategory = SB_STATIC ;
		smc->mib.fddiESSSynchTxMode = FALSE ;
		smc->ess.raf_act_timer_poll = FALSE ;
		smc->ess.timer_count = 7 ; 	/* first RAF alc req after 3s */
	}
	smc->ess.local_sba_active = FALSE ;
	smc->ess.sba_reply_pend = NULL ;
#endif
#ifdef	SBA
	smt_init_sba(smc,level) ;
#endif
#endif	/* no SLIM_SMT */
#ifdef	TAG_MODE
	if (level == 0) {
		smc->hw.pci_fix_value = 0 ;
	}
#endif
}