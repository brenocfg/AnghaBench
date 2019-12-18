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
struct falcon_nic_data {scalar_t__ stats_disable_count; } ;
struct efx_nic {int /*<<< orphan*/  net_dev; struct falcon_nic_data* nic_data; } ;
typedef  int /*<<< orphan*/  efx_oword_t ;

/* Variables and functions */
 scalar_t__ EFX_OWORD_FIELD (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EFX_POPULATE_OWORD_1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ EFX_REV_FALCON_B0 ; 
 int /*<<< orphan*/  EFX_SET_OWORD_FIELD (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  FRF_AB_RST_EM ; 
 int /*<<< orphan*/  FRF_AB_RST_XGRX ; 
 int /*<<< orphan*/  FRF_AB_RST_XGTX ; 
 int /*<<< orphan*/  FRF_AB_XM_CORE_RST ; 
 int /*<<< orphan*/  FRF_BB_TXFIFO_DRAIN_EN ; 
 int /*<<< orphan*/  FR_AB_GLB_CTL ; 
 int /*<<< orphan*/  FR_AB_MAC_CTRL ; 
 int /*<<< orphan*/  FR_AB_XM_GLB_CFG ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 scalar_t__ efx_nic_rev (struct efx_nic*) ; 
 int /*<<< orphan*/  efx_reado (struct efx_nic*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  efx_writeo (struct efx_nic*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  falcon_setup_xaui (struct efx_nic*) ; 
 int /*<<< orphan*/  hw ; 
 int /*<<< orphan*/  netif_dbg (struct efx_nic*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  netif_err (struct efx_nic*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void falcon_reset_macs(struct efx_nic *efx)
{
	struct falcon_nic_data *nic_data = efx->nic_data;
	efx_oword_t reg, mac_ctrl;
	int count;

	if (efx_nic_rev(efx) < EFX_REV_FALCON_B0) {
		/* It's not safe to use GLB_CTL_REG to reset the
		 * macs, so instead use the internal MAC resets
		 */
		EFX_POPULATE_OWORD_1(reg, FRF_AB_XM_CORE_RST, 1);
		efx_writeo(efx, &reg, FR_AB_XM_GLB_CFG);

		for (count = 0; count < 10000; count++) {
			efx_reado(efx, &reg, FR_AB_XM_GLB_CFG);
			if (EFX_OWORD_FIELD(reg, FRF_AB_XM_CORE_RST) ==
			    0)
				return;
			udelay(10);
		}

		netif_err(efx, hw, efx->net_dev,
			  "timed out waiting for XMAC core reset\n");
	}

	/* Mac stats will fail whist the TX fifo is draining */
	WARN_ON(nic_data->stats_disable_count == 0);

	efx_reado(efx, &mac_ctrl, FR_AB_MAC_CTRL);
	EFX_SET_OWORD_FIELD(mac_ctrl, FRF_BB_TXFIFO_DRAIN_EN, 1);
	efx_writeo(efx, &mac_ctrl, FR_AB_MAC_CTRL);

	efx_reado(efx, &reg, FR_AB_GLB_CTL);
	EFX_SET_OWORD_FIELD(reg, FRF_AB_RST_XGTX, 1);
	EFX_SET_OWORD_FIELD(reg, FRF_AB_RST_XGRX, 1);
	EFX_SET_OWORD_FIELD(reg, FRF_AB_RST_EM, 1);
	efx_writeo(efx, &reg, FR_AB_GLB_CTL);

	count = 0;
	while (1) {
		efx_reado(efx, &reg, FR_AB_GLB_CTL);
		if (!EFX_OWORD_FIELD(reg, FRF_AB_RST_XGTX) &&
		    !EFX_OWORD_FIELD(reg, FRF_AB_RST_XGRX) &&
		    !EFX_OWORD_FIELD(reg, FRF_AB_RST_EM)) {
			netif_dbg(efx, hw, efx->net_dev,
				  "Completed MAC reset after %d loops\n",
				  count);
			break;
		}
		if (count > 20) {
			netif_err(efx, hw, efx->net_dev, "MAC reset failed\n");
			break;
		}
		count++;
		udelay(10);
	}

	/* Ensure the correct MAC is selected before statistics
	 * are re-enabled by the caller */
	efx_writeo(efx, &mac_ctrl, FR_AB_MAC_CTRL);

	falcon_setup_xaui(efx);
}