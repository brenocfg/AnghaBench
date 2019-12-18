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
struct txc43128_data {int phy_mode; int /*<<< orphan*/  loopback_mode; } ;
struct efx_nic {int phy_mode; int /*<<< orphan*/  loopback_mode; struct txc43128_data* phy_data; } ;
typedef  enum efx_phy_mode { ____Placeholder_efx_phy_mode } efx_phy_mode ;

/* Variables and functions */
 int LOOPBACK_CHANGED (struct txc43128_data*,struct efx_nic*,int /*<<< orphan*/ ) ; 
 int PHY_MODE_LOW_POWER ; 
 int PHY_MODE_TX_DISABLED ; 
 int /*<<< orphan*/  TXC_LOOPBACKS ; 
 int /*<<< orphan*/  efx_mdio_phy_reconfigure (struct efx_nic*) ; 
 int /*<<< orphan*/  efx_mdio_transmit_disable (struct efx_nic*) ; 
 int /*<<< orphan*/  falcon_reset_xaui (struct efx_nic*) ; 
 int /*<<< orphan*/  txc_apply_defaults (struct efx_nic*) ; 
 int /*<<< orphan*/  txc_reset_logic (struct efx_nic*) ; 
 int /*<<< orphan*/  txc_reset_phy (struct efx_nic*) ; 
 int /*<<< orphan*/  txc_set_power (struct efx_nic*) ; 

__attribute__((used)) static int txc43128_phy_reconfigure(struct efx_nic *efx)
{
	struct txc43128_data *phy_data = efx->phy_data;
	enum efx_phy_mode mode_change = efx->phy_mode ^ phy_data->phy_mode;
	bool loop_change = LOOPBACK_CHANGED(phy_data, efx, TXC_LOOPBACKS);

	if (efx->phy_mode & mode_change & PHY_MODE_TX_DISABLED) {
		txc_reset_phy(efx);
		txc_apply_defaults(efx);
		falcon_reset_xaui(efx);
		mode_change &= ~PHY_MODE_TX_DISABLED;
	}

	efx_mdio_transmit_disable(efx);
	efx_mdio_phy_reconfigure(efx);
	if (mode_change & PHY_MODE_LOW_POWER)
		txc_set_power(efx);

	/* The data sheet claims this is required after every reconfiguration
	 * (note at end of 7.1), but we mustn't do it when nothing changes as
	 * it glitches the link, and reconfigure gets called on link change,
	 * so we get an IRQ storm on link up. */
	if (loop_change || mode_change)
		txc_reset_logic(efx);

	phy_data->phy_mode = efx->phy_mode;
	phy_data->loopback_mode = efx->loopback_mode;

	return 0;
}