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
typedef  int /*<<< orphan*/  temp ;
struct efx_nic {int /*<<< orphan*/  rx_hash_key; } ;
typedef  int /*<<< orphan*/  efx_oword_t ;

/* Variables and functions */
 int /*<<< orphan*/  EFX_POPULATE_OWORD_1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ EFX_REV_FALCON_B0 ; 
 int /*<<< orphan*/  EFX_SET_OWORD_FIELD (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ EFX_WORKAROUND_5129 (struct efx_nic*) ; 
 scalar_t__ EFX_WORKAROUND_5583 (struct efx_nic*) ; 
 scalar_t__ EFX_WORKAROUND_7244 (struct efx_nic*) ; 
 int /*<<< orphan*/  FRF_AA_RX_ISCSI_DIS ; 
 int /*<<< orphan*/  FRF_AA_RX_NODESC_WAIT_DIS ; 
 int /*<<< orphan*/  FRF_AA_RX_SELF_RST_EN ; 
 int /*<<< orphan*/  FRF_AB_MEM_PERR_EN_TX_DATA ; 
 int /*<<< orphan*/  FRF_AB_ONCHIP_SRAM ; 
 int /*<<< orphan*/  FRF_AZ_TX_NO_EOP_DISC_EN ; 
 int /*<<< orphan*/  FRF_BZ_FLS_EVQ_ID ; 
 int /*<<< orphan*/  FRF_BZ_TCP_FULL_SRCH_LIMIT ; 
 int /*<<< orphan*/  FRF_BZ_TCP_WILD_SRCH_LIMIT ; 
 int /*<<< orphan*/  FRF_BZ_UDP_FULL_SRCH_LIMIT ; 
 int /*<<< orphan*/  FRF_BZ_UDP_WILD_SRCH_LIMIT ; 
 int /*<<< orphan*/  FR_AA_RX_SELF_RST ; 
 int /*<<< orphan*/  FR_AB_NIC_STAT ; 
 int /*<<< orphan*/  FR_AZ_CSR_SPARE ; 
 int /*<<< orphan*/  FR_AZ_TX_CFG ; 
 int /*<<< orphan*/  FR_BZ_DP_CTRL ; 
 int /*<<< orphan*/  FR_BZ_RX_FILTER_CTL ; 
 int /*<<< orphan*/  FR_BZ_RX_RSS_TKEY ; 
 int /*<<< orphan*/  efx_nic_init_common (struct efx_nic*) ; 
 scalar_t__ efx_nic_rev (struct efx_nic*) ; 
 int /*<<< orphan*/  efx_reado (struct efx_nic*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  efx_writeo (struct efx_nic*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  falcon_init_rx_cfg (struct efx_nic*) ; 
 int falcon_reset_sram (struct efx_nic*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int falcon_init_nic(struct efx_nic *efx)
{
	efx_oword_t temp;
	int rc;

	/* Use on-chip SRAM */
	efx_reado(efx, &temp, FR_AB_NIC_STAT);
	EFX_SET_OWORD_FIELD(temp, FRF_AB_ONCHIP_SRAM, 1);
	efx_writeo(efx, &temp, FR_AB_NIC_STAT);

	rc = falcon_reset_sram(efx);
	if (rc)
		return rc;

	/* Clear the parity enables on the TX data fifos as
	 * they produce false parity errors because of timing issues
	 */
	if (EFX_WORKAROUND_5129(efx)) {
		efx_reado(efx, &temp, FR_AZ_CSR_SPARE);
		EFX_SET_OWORD_FIELD(temp, FRF_AB_MEM_PERR_EN_TX_DATA, 0);
		efx_writeo(efx, &temp, FR_AZ_CSR_SPARE);
	}

	if (EFX_WORKAROUND_7244(efx)) {
		efx_reado(efx, &temp, FR_BZ_RX_FILTER_CTL);
		EFX_SET_OWORD_FIELD(temp, FRF_BZ_UDP_FULL_SRCH_LIMIT, 8);
		EFX_SET_OWORD_FIELD(temp, FRF_BZ_UDP_WILD_SRCH_LIMIT, 8);
		EFX_SET_OWORD_FIELD(temp, FRF_BZ_TCP_FULL_SRCH_LIMIT, 8);
		EFX_SET_OWORD_FIELD(temp, FRF_BZ_TCP_WILD_SRCH_LIMIT, 8);
		efx_writeo(efx, &temp, FR_BZ_RX_FILTER_CTL);
	}

	/* XXX This is documented only for Falcon A0/A1 */
	/* Setup RX.  Wait for descriptor is broken and must
	 * be disabled.  RXDP recovery shouldn't be needed, but is.
	 */
	efx_reado(efx, &temp, FR_AA_RX_SELF_RST);
	EFX_SET_OWORD_FIELD(temp, FRF_AA_RX_NODESC_WAIT_DIS, 1);
	EFX_SET_OWORD_FIELD(temp, FRF_AA_RX_SELF_RST_EN, 1);
	if (EFX_WORKAROUND_5583(efx))
		EFX_SET_OWORD_FIELD(temp, FRF_AA_RX_ISCSI_DIS, 1);
	efx_writeo(efx, &temp, FR_AA_RX_SELF_RST);

	/* Do not enable TX_NO_EOP_DISC_EN, since it limits packets to 16
	 * descriptors (which is bad).
	 */
	efx_reado(efx, &temp, FR_AZ_TX_CFG);
	EFX_SET_OWORD_FIELD(temp, FRF_AZ_TX_NO_EOP_DISC_EN, 0);
	efx_writeo(efx, &temp, FR_AZ_TX_CFG);

	falcon_init_rx_cfg(efx);

	if (efx_nic_rev(efx) >= EFX_REV_FALCON_B0) {
		/* Set hash key for IPv4 */
		memcpy(&temp, efx->rx_hash_key, sizeof(temp));
		efx_writeo(efx, &temp, FR_BZ_RX_RSS_TKEY);

		/* Set destination of both TX and RX Flush events */
		EFX_POPULATE_OWORD_1(temp, FRF_BZ_FLS_EVQ_ID, 0);
		efx_writeo(efx, &temp, FR_BZ_DP_CTRL);
	}

	efx_nic_init_common(efx);

	return 0;
}