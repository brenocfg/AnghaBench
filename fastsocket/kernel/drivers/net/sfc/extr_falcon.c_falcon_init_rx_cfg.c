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
struct efx_nic {int dummy; } ;
typedef  int /*<<< orphan*/  efx_oword_t ;

/* Variables and functions */
 scalar_t__ EFX_REV_FALCON_A1 ; 
 int EFX_RX_USR_BUF_SIZE ; 
 int /*<<< orphan*/  EFX_SET_OWORD_FIELD (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int const) ; 
 int /*<<< orphan*/  FRF_AA_RX_DESC_PUSH_EN ; 
 int /*<<< orphan*/  FRF_AA_RX_USR_BUF_SIZE ; 
 int /*<<< orphan*/  FRF_AA_RX_XOFF_MAC_TH ; 
 int /*<<< orphan*/  FRF_AA_RX_XOFF_TX_TH ; 
 int /*<<< orphan*/  FRF_AA_RX_XON_MAC_TH ; 
 int /*<<< orphan*/  FRF_AA_RX_XON_TX_TH ; 
 int /*<<< orphan*/  FRF_AZ_RX_XOFF_MAC_EN ; 
 int /*<<< orphan*/  FRF_BZ_RX_DESC_PUSH_EN ; 
 int /*<<< orphan*/  FRF_BZ_RX_HASH_ALG ; 
 int /*<<< orphan*/  FRF_BZ_RX_HASH_INSRT_HDR ; 
 int /*<<< orphan*/  FRF_BZ_RX_INGR_EN ; 
 int /*<<< orphan*/  FRF_BZ_RX_IP_HASH ; 
 int /*<<< orphan*/  FRF_BZ_RX_USR_BUF_SIZE ; 
 int /*<<< orphan*/  FRF_BZ_RX_XOFF_MAC_TH ; 
 int /*<<< orphan*/  FRF_BZ_RX_XOFF_TX_TH ; 
 int /*<<< orphan*/  FRF_BZ_RX_XON_MAC_TH ; 
 int /*<<< orphan*/  FRF_BZ_RX_XON_TX_TH ; 
 int /*<<< orphan*/  FR_AZ_RX_CFG ; 
 scalar_t__ efx_nic_rev (struct efx_nic*) ; 
 int /*<<< orphan*/  efx_reado (struct efx_nic*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  efx_writeo (struct efx_nic*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void falcon_init_rx_cfg(struct efx_nic *efx)
{
	/* RX control FIFO thresholds (32 entries) */
	const unsigned ctrl_xon_thr = 20;
	const unsigned ctrl_xoff_thr = 25;
	efx_oword_t reg;

	efx_reado(efx, &reg, FR_AZ_RX_CFG);
	if (efx_nic_rev(efx) <= EFX_REV_FALCON_A1) {
		/* Data FIFO size is 5.5K.  The RX DMA engine only
		 * supports scattering for user-mode queues, but will
		 * split DMA writes at intervals of RX_USR_BUF_SIZE
		 * (32-byte units) even for kernel-mode queues.  We
		 * set it to be so large that that never happens.
		 */
		EFX_SET_OWORD_FIELD(reg, FRF_AA_RX_DESC_PUSH_EN, 0);
		EFX_SET_OWORD_FIELD(reg, FRF_AA_RX_USR_BUF_SIZE,
				    (3 * 4096) >> 5);
		EFX_SET_OWORD_FIELD(reg, FRF_AA_RX_XON_MAC_TH, 512 >> 8);
		EFX_SET_OWORD_FIELD(reg, FRF_AA_RX_XOFF_MAC_TH, 2048 >> 8);
		EFX_SET_OWORD_FIELD(reg, FRF_AA_RX_XON_TX_TH, ctrl_xon_thr);
		EFX_SET_OWORD_FIELD(reg, FRF_AA_RX_XOFF_TX_TH, ctrl_xoff_thr);
	} else {
		/* Data FIFO size is 80K; register fields moved */
		EFX_SET_OWORD_FIELD(reg, FRF_BZ_RX_DESC_PUSH_EN, 0);
		EFX_SET_OWORD_FIELD(reg, FRF_BZ_RX_USR_BUF_SIZE,
				    EFX_RX_USR_BUF_SIZE >> 5);
		/* Send XON and XOFF at ~3 * max MTU away from empty/full */
		EFX_SET_OWORD_FIELD(reg, FRF_BZ_RX_XON_MAC_TH, 27648 >> 8);
		EFX_SET_OWORD_FIELD(reg, FRF_BZ_RX_XOFF_MAC_TH, 54272 >> 8);
		EFX_SET_OWORD_FIELD(reg, FRF_BZ_RX_XON_TX_TH, ctrl_xon_thr);
		EFX_SET_OWORD_FIELD(reg, FRF_BZ_RX_XOFF_TX_TH, ctrl_xoff_thr);
		EFX_SET_OWORD_FIELD(reg, FRF_BZ_RX_INGR_EN, 1);

		/* Enable hash insertion. This is broken for the
		 * 'Falcon' hash so also select Toeplitz TCP/IPv4 and
		 * IPv4 hashes. */
		EFX_SET_OWORD_FIELD(reg, FRF_BZ_RX_HASH_INSRT_HDR, 1);
		EFX_SET_OWORD_FIELD(reg, FRF_BZ_RX_HASH_ALG, 1);
		EFX_SET_OWORD_FIELD(reg, FRF_BZ_RX_IP_HASH, 1);
	}
	/* Always enable XOFF signal from RX FIFO.  We enable
	 * or disable transmission of pause frames at the MAC. */
	EFX_SET_OWORD_FIELD(reg, FRF_AZ_RX_XOFF_MAC_EN, 1);
	efx_writeo(efx, &reg, FR_AZ_RX_CFG);
}