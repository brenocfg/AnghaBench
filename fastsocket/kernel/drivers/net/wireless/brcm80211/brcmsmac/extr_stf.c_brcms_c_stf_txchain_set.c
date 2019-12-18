#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint ;
typedef  size_t u8 ;
struct brcms_c_info {TYPE_2__* stf; TYPE_1__* band; int /*<<< orphan*/ * bandstate; } ;
typedef  scalar_t__ s32 ;
struct TYPE_4__ {size_t txchain; size_t hw_txchain; size_t txstreams; int /*<<< orphan*/  rxchain; int /*<<< orphan*/  txant; } ;
struct TYPE_3__ {int /*<<< orphan*/  pi; int /*<<< orphan*/  band_stf_stbc_tx; } ;

/* Variables and functions */
 int /*<<< orphan*/  ANT_TX_DEF ; 
 int /*<<< orphan*/  ANT_TX_FORCE_0 ; 
 size_t BAND_2G_INDEX ; 
 size_t BAND_5G_INDEX ; 
 int EINVAL ; 
 size_t MAX_STREAMS_SUPPORTED ; 
 int /*<<< orphan*/  _brcms_c_stf_phy_txant_upd (struct brcms_c_info*) ; 
 int /*<<< orphan*/  brcms_c_stf_ss_update (struct brcms_c_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  brcms_c_stf_stbc_tx_set (struct brcms_c_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  brcms_c_stf_txcore_set (struct brcms_c_info*,size_t,int /*<<< orphan*/ ) ; 
 scalar_t__ hweight8 (size_t) ; 
 int /*<<< orphan*/ * txcore_default ; 
 int /*<<< orphan*/  wlc_phy_stf_chain_set (int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ) ; 

int brcms_c_stf_txchain_set(struct brcms_c_info *wlc, s32 int_val, bool force)
{
	u8 txchain = (u8) int_val;
	u8 txstreams;
	uint i;

	if (wlc->stf->txchain == txchain)
		return 0;

	if ((txchain & ~wlc->stf->hw_txchain)
	    || !(txchain & wlc->stf->hw_txchain))
		return -EINVAL;

	/*
	 * if nrate override is configured to be non-SISO STF mode, reject
	 * reducing txchain to 1
	 */
	txstreams = (u8) hweight8(txchain);
	if (txstreams > MAX_STREAMS_SUPPORTED)
		return -EINVAL;

	wlc->stf->txchain = txchain;
	wlc->stf->txstreams = txstreams;
	brcms_c_stf_stbc_tx_set(wlc, wlc->band->band_stf_stbc_tx);
	brcms_c_stf_ss_update(wlc, wlc->bandstate[BAND_2G_INDEX]);
	brcms_c_stf_ss_update(wlc, wlc->bandstate[BAND_5G_INDEX]);
	wlc->stf->txant =
	    (wlc->stf->txstreams == 1) ? ANT_TX_FORCE_0 : ANT_TX_DEF;
	_brcms_c_stf_phy_txant_upd(wlc);

	wlc_phy_stf_chain_set(wlc->band->pi, wlc->stf->txchain,
			      wlc->stf->rxchain);

	for (i = 1; i <= MAX_STREAMS_SUPPORTED; i++)
		brcms_c_stf_txcore_set(wlc, (u8) i, txcore_default[i]);

	return 0;
}