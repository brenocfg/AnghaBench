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
struct efx_nic {scalar_t__ rx_hash_key; } ;
typedef  int /*<<< orphan*/  efx_oword_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUILD_BUG_ON (int) ; 
 int /*<<< orphan*/  EFX_POPULATE_OWORD_1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  EFX_POPULATE_OWORD_2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 
 int EFX_RX_USR_BUF_SIZE ; 
 int /*<<< orphan*/  EFX_SET_OWORD_FIELD (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  FRF_AZ_TX_NO_EOP_DISC_EN ; 
 int /*<<< orphan*/  FRF_BZ_FLS_EVQ_ID ; 
 int /*<<< orphan*/  FRF_BZ_RX_DESC_PUSH_EN ; 
 int /*<<< orphan*/  FRF_BZ_RX_HASH_ALG ; 
 int /*<<< orphan*/  FRF_BZ_RX_HASH_INSRT_HDR ; 
 int /*<<< orphan*/  FRF_BZ_RX_INGR_EN ; 
 int /*<<< orphan*/  FRF_BZ_RX_IP_HASH ; 
 int /*<<< orphan*/  FRF_BZ_RX_USR_BUF_SIZE ; 
 int /*<<< orphan*/  FRF_BZ_TX_FLUSH_MIN_LEN_EN ; 
 int /*<<< orphan*/  FRF_CZ_RX_RSS_IPV6_IP_THASH_ENABLE ; 
 int /*<<< orphan*/  FRF_CZ_RX_RSS_IPV6_THASH_ENABLE ; 
 scalar_t__ FRF_CZ_RX_RSS_IPV6_TKEY_HI_LBN ; 
 int FRF_CZ_RX_RSS_IPV6_TKEY_HI_WIDTH ; 
 int /*<<< orphan*/  FRF_CZ_TX_FILTER_EN_BIT ; 
 int /*<<< orphan*/  FRF_CZ_USREV_DIS ; 
 int /*<<< orphan*/  FR_AZ_RX_CFG ; 
 int /*<<< orphan*/  FR_AZ_TX_CFG ; 
 int /*<<< orphan*/  FR_AZ_TX_RESERVED ; 
 int /*<<< orphan*/  FR_BZ_DP_CTRL ; 
 int /*<<< orphan*/  FR_BZ_RX_RSS_TKEY ; 
 int /*<<< orphan*/  FR_CZ_RX_RSS_IPV6_REG1 ; 
 int /*<<< orphan*/  FR_CZ_RX_RSS_IPV6_REG2 ; 
 int /*<<< orphan*/  FR_CZ_RX_RSS_IPV6_REG3 ; 
 int /*<<< orphan*/  FR_CZ_USR_EV_CFG ; 
 int efx_mcdi_handle_assertion (struct efx_nic*) ; 
 int efx_mcdi_log_ctrl (struct efx_nic*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  efx_nic_init_common (struct efx_nic*) ; 
 int /*<<< orphan*/  efx_reado (struct efx_nic*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  efx_writeo (struct efx_nic*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,scalar_t__,int) ; 

__attribute__((used)) static int siena_init_nic(struct efx_nic *efx)
{
	efx_oword_t temp;
	int rc;

	/* Recover from a failed assertion post-reset */
	rc = efx_mcdi_handle_assertion(efx);
	if (rc)
		return rc;

	/* Squash TX of packets of 16 bytes or less */
	efx_reado(efx, &temp, FR_AZ_TX_RESERVED);
	EFX_SET_OWORD_FIELD(temp, FRF_BZ_TX_FLUSH_MIN_LEN_EN, 1);
	efx_writeo(efx, &temp, FR_AZ_TX_RESERVED);

	/* Do not enable TX_NO_EOP_DISC_EN, since it limits packets to 16
	 * descriptors (which is bad).
	 */
	efx_reado(efx, &temp, FR_AZ_TX_CFG);
	EFX_SET_OWORD_FIELD(temp, FRF_AZ_TX_NO_EOP_DISC_EN, 0);
	EFX_SET_OWORD_FIELD(temp, FRF_CZ_TX_FILTER_EN_BIT, 1);
	efx_writeo(efx, &temp, FR_AZ_TX_CFG);

	efx_reado(efx, &temp, FR_AZ_RX_CFG);
	EFX_SET_OWORD_FIELD(temp, FRF_BZ_RX_DESC_PUSH_EN, 0);
	EFX_SET_OWORD_FIELD(temp, FRF_BZ_RX_INGR_EN, 1);
	/* Enable hash insertion. This is broken for the 'Falcon' hash
	 * if IPv6 hashing is also enabled, so also select Toeplitz
	 * TCP/IPv4 and IPv4 hashes. */
	EFX_SET_OWORD_FIELD(temp, FRF_BZ_RX_HASH_INSRT_HDR, 1);
	EFX_SET_OWORD_FIELD(temp, FRF_BZ_RX_HASH_ALG, 1);
	EFX_SET_OWORD_FIELD(temp, FRF_BZ_RX_IP_HASH, 1);
	EFX_SET_OWORD_FIELD(temp, FRF_BZ_RX_USR_BUF_SIZE,
			    EFX_RX_USR_BUF_SIZE >> 5);
	efx_writeo(efx, &temp, FR_AZ_RX_CFG);

	/* Set hash key for IPv4 */
	memcpy(&temp, efx->rx_hash_key, sizeof(temp));
	efx_writeo(efx, &temp, FR_BZ_RX_RSS_TKEY);

	/* Enable IPv6 RSS */
	BUILD_BUG_ON(sizeof(efx->rx_hash_key) <
		     2 * sizeof(temp) + FRF_CZ_RX_RSS_IPV6_TKEY_HI_WIDTH / 8 ||
		     FRF_CZ_RX_RSS_IPV6_TKEY_HI_LBN != 0);
	memcpy(&temp, efx->rx_hash_key, sizeof(temp));
	efx_writeo(efx, &temp, FR_CZ_RX_RSS_IPV6_REG1);
	memcpy(&temp, efx->rx_hash_key + sizeof(temp), sizeof(temp));
	efx_writeo(efx, &temp, FR_CZ_RX_RSS_IPV6_REG2);
	EFX_POPULATE_OWORD_2(temp, FRF_CZ_RX_RSS_IPV6_THASH_ENABLE, 1,
			     FRF_CZ_RX_RSS_IPV6_IP_THASH_ENABLE, 1);
	memcpy(&temp, efx->rx_hash_key + 2 * sizeof(temp),
	       FRF_CZ_RX_RSS_IPV6_TKEY_HI_WIDTH / 8);
	efx_writeo(efx, &temp, FR_CZ_RX_RSS_IPV6_REG3);

	/* Enable event logging */
	rc = efx_mcdi_log_ctrl(efx, true, false, 0);
	if (rc)
		return rc;

	/* Set destination of both TX and RX Flush events */
	EFX_POPULATE_OWORD_1(temp, FRF_BZ_FLS_EVQ_ID, 0);
	efx_writeo(efx, &temp, FR_BZ_DP_CTRL);

	EFX_POPULATE_OWORD_1(temp, FRF_CZ_USREV_DIS, 1);
	efx_writeo(efx, &temp, FR_CZ_USR_EV_CFG);

	efx_nic_init_common(efx);
	return 0;
}