#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u16 ;
struct TYPE_2__ {int /*<<< orphan*/  phy_rev; } ;
struct brcms_phy {scalar_t__ nphy_txrx_chain; int /*<<< orphan*/  nphy_perical; TYPE_1__ pubpi; } ;

/* Variables and functions */
 scalar_t__ BRCMS_N_TXRX_CHAIN0 ; 
 scalar_t__ BRCMS_N_TXRX_CHAIN1 ; 
 int NPHY_RfseqCoreActv_TxRxChain0 ; 
 int NPHY_RfseqCoreActv_TxRxChain1 ; 
 int NPHY_RfseqMode_CoreActv_override ; 
 scalar_t__ NREV_LE (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  PHY_PERICAL_DISABLE ; 
 int /*<<< orphan*/  PHY_PERICAL_MPHASE ; 
 int /*<<< orphan*/  and_phy_reg (struct brcms_phy*,int,int) ; 
 int /*<<< orphan*/  mod_phy_reg (struct brcms_phy*,int,int,int) ; 
 int /*<<< orphan*/  or_phy_reg (struct brcms_phy*,int,int) ; 

void wlc_phy_stf_chain_upd_nphy(struct brcms_phy *pi)
{

	u16 txrx_chain =
		(NPHY_RfseqCoreActv_TxRxChain0 | NPHY_RfseqCoreActv_TxRxChain1);
	bool CoreActv_override = false;

	if (pi->nphy_txrx_chain == BRCMS_N_TXRX_CHAIN0) {
		txrx_chain = NPHY_RfseqCoreActv_TxRxChain0;
		CoreActv_override = true;

		if (NREV_LE(pi->pubpi.phy_rev, 2))
			and_phy_reg(pi, 0xa0, ~0x20);
	} else if (pi->nphy_txrx_chain == BRCMS_N_TXRX_CHAIN1) {
		txrx_chain = NPHY_RfseqCoreActv_TxRxChain1;
		CoreActv_override = true;

		if (NREV_LE(pi->pubpi.phy_rev, 2))
			or_phy_reg(pi, 0xa0, 0x20);
	}

	mod_phy_reg(pi, 0xa2, ((0xf << 0) | (0xf << 4)), txrx_chain);

	if (CoreActv_override) {
		pi->nphy_perical = PHY_PERICAL_DISABLE;
		or_phy_reg(pi, 0xa1, NPHY_RfseqMode_CoreActv_override);
	} else {
		pi->nphy_perical = PHY_PERICAL_MPHASE;
		and_phy_reg(pi, 0xa1, ~NPHY_RfseqMode_CoreActv_override);
	}
}