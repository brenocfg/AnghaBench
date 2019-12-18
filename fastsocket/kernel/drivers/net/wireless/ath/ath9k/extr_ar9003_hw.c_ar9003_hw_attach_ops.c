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
struct ath_hw_private_ops {int /*<<< orphan*/  init_mode_gain_regs; } ;
struct ath_hw_ops {int /*<<< orphan*/  config_pci_powersave; } ;
struct ath_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ar9003_hw_attach_calib_ops (struct ath_hw*) ; 
 int /*<<< orphan*/  ar9003_hw_attach_mac_ops (struct ath_hw*) ; 
 int /*<<< orphan*/  ar9003_hw_attach_phy_ops (struct ath_hw*) ; 
 int /*<<< orphan*/  ar9003_hw_configpcipowersave ; 
 int /*<<< orphan*/  ar9003_hw_init_mode_gain_regs ; 
 int /*<<< orphan*/  ar9003_hw_init_mode_regs (struct ath_hw*) ; 
 struct ath_hw_ops* ath9k_hw_ops (struct ath_hw*) ; 
 struct ath_hw_private_ops* ath9k_hw_private_ops (struct ath_hw*) ; 

void ar9003_hw_attach_ops(struct ath_hw *ah)
{
	struct ath_hw_private_ops *priv_ops = ath9k_hw_private_ops(ah);
	struct ath_hw_ops *ops = ath9k_hw_ops(ah);

	ar9003_hw_init_mode_regs(ah);
	priv_ops->init_mode_gain_regs = ar9003_hw_init_mode_gain_regs;

	ops->config_pci_powersave = ar9003_hw_configpcipowersave;

	ar9003_hw_attach_phy_ops(ah);
	ar9003_hw_attach_calib_ops(ah);
	ar9003_hw_attach_mac_ops(ah);
}