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
struct ath_hw_private_ops {int /*<<< orphan*/  do_getnf; int /*<<< orphan*/  compute_pll_control; int /*<<< orphan*/  olc_init; int /*<<< orphan*/  spur_mitigate_freq; int /*<<< orphan*/  rf_set_freq; int /*<<< orphan*/ * set_rf_regs; } ;
struct ath_hw_ops {int /*<<< orphan*/  spectral_scan_wait; int /*<<< orphan*/  spectral_scan_trigger; int /*<<< orphan*/  spectral_scan_config; int /*<<< orphan*/  antdiv_comb_conf_set; int /*<<< orphan*/  antdiv_comb_conf_get; } ;
struct ath_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ar9002_hw_antdiv_comb_conf_get ; 
 int /*<<< orphan*/  ar9002_hw_antdiv_comb_conf_set ; 
 int /*<<< orphan*/  ar9002_hw_compute_pll_control ; 
 int /*<<< orphan*/  ar9002_hw_do_getnf ; 
 int /*<<< orphan*/  ar9002_hw_set_channel ; 
 int /*<<< orphan*/  ar9002_hw_set_nf_limits (struct ath_hw*) ; 
 int /*<<< orphan*/  ar9002_hw_spectral_scan_config ; 
 int /*<<< orphan*/  ar9002_hw_spectral_scan_trigger ; 
 int /*<<< orphan*/  ar9002_hw_spectral_scan_wait ; 
 int /*<<< orphan*/  ar9002_hw_spur_mitigate ; 
 int /*<<< orphan*/  ar9002_olc_init ; 
 struct ath_hw_ops* ath9k_hw_ops (struct ath_hw*) ; 
 struct ath_hw_private_ops* ath9k_hw_private_ops (struct ath_hw*) ; 

void ar9002_hw_attach_phy_ops(struct ath_hw *ah)
{
	struct ath_hw_private_ops *priv_ops = ath9k_hw_private_ops(ah);
	struct ath_hw_ops *ops = ath9k_hw_ops(ah);

	priv_ops->set_rf_regs = NULL;
	priv_ops->rf_set_freq = ar9002_hw_set_channel;
	priv_ops->spur_mitigate_freq = ar9002_hw_spur_mitigate;
	priv_ops->olc_init = ar9002_olc_init;
	priv_ops->compute_pll_control = ar9002_hw_compute_pll_control;
	priv_ops->do_getnf = ar9002_hw_do_getnf;

	ops->antdiv_comb_conf_get = ar9002_hw_antdiv_comb_conf_get;
	ops->antdiv_comb_conf_set = ar9002_hw_antdiv_comb_conf_set;
	ops->spectral_scan_config = ar9002_hw_spectral_scan_config;
	ops->spectral_scan_trigger = ar9002_hw_spectral_scan_trigger;
	ops->spectral_scan_wait = ar9002_hw_spectral_scan_wait;

	ar9002_hw_set_nf_limits(ah);
}