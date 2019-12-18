#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct ath_hw_private_ops {int /*<<< orphan*/  fast_chan_change; int /*<<< orphan*/  set_radar_params; int /*<<< orphan*/  ani_cache_ini_regs; int /*<<< orphan*/  do_getnf; int /*<<< orphan*/  ani_control; int /*<<< orphan*/  rfbus_done; int /*<<< orphan*/  rfbus_req; int /*<<< orphan*/  set_delta_slope; int /*<<< orphan*/  mark_phy_inactive; int /*<<< orphan*/  set_rfmode; int /*<<< orphan*/  process_ini; int /*<<< orphan*/  init_bb; int /*<<< orphan*/  set_channel_regs; int /*<<< orphan*/  compute_pll_control; int /*<<< orphan*/  spur_mitigate_freq; int /*<<< orphan*/  rf_set_freq; } ;
struct ath_hw_ops {int /*<<< orphan*/  spectral_scan_wait; int /*<<< orphan*/  spectral_scan_trigger; int /*<<< orphan*/  spectral_scan_config; int /*<<< orphan*/  antctrl_shared_chain_lnadiv; int /*<<< orphan*/  antdiv_comb_conf_set; int /*<<< orphan*/  antdiv_comb_conf_get; } ;
struct ath_hw {int /*<<< orphan*/  nf_regs; } ;

/* Variables and functions */
#define  AR_PHY_CCA_0 133 
#define  AR_PHY_CCA_1 132 
#define  AR_PHY_CCA_2 131 
#define  AR_PHY_EXT_CCA 130 
#define  AR_PHY_EXT_CCA_1 129 
#define  AR_PHY_EXT_CCA_2 128 
 int /*<<< orphan*/  ar9003_hw_ani_cache_ini_regs ; 
 int /*<<< orphan*/  ar9003_hw_ani_control ; 
 int /*<<< orphan*/  ar9003_hw_antctrl_shared_chain_lnadiv ; 
 int /*<<< orphan*/  ar9003_hw_antdiv_comb_conf_get ; 
 int /*<<< orphan*/  ar9003_hw_antdiv_comb_conf_set ; 
 int /*<<< orphan*/  ar9003_hw_compute_pll_control ; 
 int /*<<< orphan*/  ar9003_hw_do_getnf ; 
 int /*<<< orphan*/  ar9003_hw_fast_chan_change ; 
 int /*<<< orphan*/  ar9003_hw_init_bb ; 
 int /*<<< orphan*/  ar9003_hw_mark_phy_inactive ; 
 int /*<<< orphan*/  ar9003_hw_process_ini ; 
 int /*<<< orphan*/  ar9003_hw_rfbus_done ; 
 int /*<<< orphan*/  ar9003_hw_rfbus_req ; 
 int /*<<< orphan*/  ar9003_hw_set_channel ; 
 int /*<<< orphan*/  ar9003_hw_set_channel_regs ; 
 int /*<<< orphan*/  ar9003_hw_set_delta_slope ; 
 int /*<<< orphan*/  ar9003_hw_set_nf_limits (struct ath_hw*) ; 
 int /*<<< orphan*/  ar9003_hw_set_radar_conf (struct ath_hw*) ; 
 int /*<<< orphan*/  ar9003_hw_set_radar_params ; 
 int /*<<< orphan*/  ar9003_hw_set_rfmode ; 
 int /*<<< orphan*/  ar9003_hw_spectral_scan_config ; 
 int /*<<< orphan*/  ar9003_hw_spectral_scan_trigger ; 
 int /*<<< orphan*/  ar9003_hw_spectral_scan_wait ; 
 int /*<<< orphan*/  ar9003_hw_spur_mitigate ; 
 struct ath_hw_ops* ath9k_hw_ops (struct ath_hw*) ; 
 struct ath_hw_private_ops* ath9k_hw_private_ops (struct ath_hw*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int) ; 

void ar9003_hw_attach_phy_ops(struct ath_hw *ah)
{
	struct ath_hw_private_ops *priv_ops = ath9k_hw_private_ops(ah);
	struct ath_hw_ops *ops = ath9k_hw_ops(ah);
	static const u32 ar9300_cca_regs[6] = {
		AR_PHY_CCA_0,
		AR_PHY_CCA_1,
		AR_PHY_CCA_2,
		AR_PHY_EXT_CCA,
		AR_PHY_EXT_CCA_1,
		AR_PHY_EXT_CCA_2,
	};

	priv_ops->rf_set_freq = ar9003_hw_set_channel;
	priv_ops->spur_mitigate_freq = ar9003_hw_spur_mitigate;
	priv_ops->compute_pll_control = ar9003_hw_compute_pll_control;
	priv_ops->set_channel_regs = ar9003_hw_set_channel_regs;
	priv_ops->init_bb = ar9003_hw_init_bb;
	priv_ops->process_ini = ar9003_hw_process_ini;
	priv_ops->set_rfmode = ar9003_hw_set_rfmode;
	priv_ops->mark_phy_inactive = ar9003_hw_mark_phy_inactive;
	priv_ops->set_delta_slope = ar9003_hw_set_delta_slope;
	priv_ops->rfbus_req = ar9003_hw_rfbus_req;
	priv_ops->rfbus_done = ar9003_hw_rfbus_done;
	priv_ops->ani_control = ar9003_hw_ani_control;
	priv_ops->do_getnf = ar9003_hw_do_getnf;
	priv_ops->ani_cache_ini_regs = ar9003_hw_ani_cache_ini_regs;
	priv_ops->set_radar_params = ar9003_hw_set_radar_params;
	priv_ops->fast_chan_change = ar9003_hw_fast_chan_change;

	ops->antdiv_comb_conf_get = ar9003_hw_antdiv_comb_conf_get;
	ops->antdiv_comb_conf_set = ar9003_hw_antdiv_comb_conf_set;
	ops->antctrl_shared_chain_lnadiv = ar9003_hw_antctrl_shared_chain_lnadiv;
	ops->spectral_scan_config = ar9003_hw_spectral_scan_config;
	ops->spectral_scan_trigger = ar9003_hw_spectral_scan_trigger;
	ops->spectral_scan_wait = ar9003_hw_spectral_scan_wait;

	ar9003_hw_set_nf_limits(ah);
	ar9003_hw_set_radar_conf(ah);
	memcpy(ah->nf_regs, ar9300_cca_regs, sizeof(ah->nf_regs));
}