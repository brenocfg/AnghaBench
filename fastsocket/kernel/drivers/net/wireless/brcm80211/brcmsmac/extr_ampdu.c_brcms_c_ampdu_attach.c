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
struct brcms_c_info {TYPE_1__* pub; TYPE_2__* band; } ;
struct ampdu_info {int* ini_enable; int mfbr; int /*<<< orphan*/  tx_max_funl; int /*<<< orphan*/  dur; int /*<<< orphan*/  rr_retry_limit; int /*<<< orphan*/ * rr_retry_limit_tid; int /*<<< orphan*/  retry_limit; int /*<<< orphan*/ * retry_limit_tid; int /*<<< orphan*/  rx_factor; int /*<<< orphan*/  ffpld_rsvd; int /*<<< orphan*/  max_pdu; int /*<<< orphan*/  mpdu_density; int /*<<< orphan*/  ba_rx_wsize; int /*<<< orphan*/  ba_tx_wsize; struct brcms_c_info* wlc; } ;
struct TYPE_4__ {int /*<<< orphan*/  phyrev; } ;
struct TYPE_3__ {int /*<<< orphan*/  _ampdu; } ;

/* Variables and functions */
 int /*<<< orphan*/  AMPDU_DEF_FFPLD_RSVD ; 
 int /*<<< orphan*/  AMPDU_DEF_MPDU_DENSITY ; 
 int /*<<< orphan*/  AMPDU_DEF_RETRY_LIMIT ; 
 int /*<<< orphan*/  AMPDU_DEF_RR_RETRY_LIMIT ; 
 int /*<<< orphan*/  AMPDU_MAX_DUR ; 
 int AMPDU_MAX_SCB_TID ; 
 int /*<<< orphan*/  AMPDU_RX_BA_DEF_WSIZE ; 
 int /*<<< orphan*/  AMPDU_TX_BA_DEF_WSIZE ; 
 int /*<<< orphan*/  AUTO ; 
 scalar_t__ BRCMS_ISNPHY (TYPE_2__*) ; 
 int /*<<< orphan*/  FFPLD_TX_MAX_UNFL ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  IEEE80211_HT_MAX_AMPDU_32K ; 
 int /*<<< orphan*/  IEEE80211_HT_MAX_AMPDU_64K ; 
 scalar_t__ NREV_LT (int /*<<< orphan*/ ,int) ; 
 size_t PRIO_8021D_BK ; 
 size_t PRIO_8021D_NC ; 
 size_t PRIO_8021D_NONE ; 
 size_t PRIO_8021D_VO ; 
 int /*<<< orphan*/  brcms_c_ampdu_set (struct ampdu_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  brcms_c_ffpld_init (struct ampdu_info*) ; 
 int /*<<< orphan*/  brcms_c_scb_ampdu_update_max_txlen (struct ampdu_info*,int /*<<< orphan*/ ) ; 
 struct ampdu_info* kzalloc (int,int /*<<< orphan*/ ) ; 

struct ampdu_info *brcms_c_ampdu_attach(struct brcms_c_info *wlc)
{
	struct ampdu_info *ampdu;
	int i;

	ampdu = kzalloc(sizeof(struct ampdu_info), GFP_ATOMIC);
	if (!ampdu)
		return NULL;

	ampdu->wlc = wlc;

	for (i = 0; i < AMPDU_MAX_SCB_TID; i++)
		ampdu->ini_enable[i] = true;
	/* Disable ampdu for VO by default */
	ampdu->ini_enable[PRIO_8021D_VO] = false;
	ampdu->ini_enable[PRIO_8021D_NC] = false;

	/* Disable ampdu for BK by default since not enough fifo space */
	ampdu->ini_enable[PRIO_8021D_NONE] = false;
	ampdu->ini_enable[PRIO_8021D_BK] = false;

	ampdu->ba_tx_wsize = AMPDU_TX_BA_DEF_WSIZE;
	ampdu->ba_rx_wsize = AMPDU_RX_BA_DEF_WSIZE;
	ampdu->mpdu_density = AMPDU_DEF_MPDU_DENSITY;
	ampdu->max_pdu = AUTO;
	ampdu->dur = AMPDU_MAX_DUR;

	ampdu->ffpld_rsvd = AMPDU_DEF_FFPLD_RSVD;
	/*
	 * bump max ampdu rcv size to 64k for all 11n
	 * devices except 4321A0 and 4321A1
	 */
	if (BRCMS_ISNPHY(wlc->band) && NREV_LT(wlc->band->phyrev, 2))
		ampdu->rx_factor = IEEE80211_HT_MAX_AMPDU_32K;
	else
		ampdu->rx_factor = IEEE80211_HT_MAX_AMPDU_64K;
	ampdu->retry_limit = AMPDU_DEF_RETRY_LIMIT;
	ampdu->rr_retry_limit = AMPDU_DEF_RR_RETRY_LIMIT;

	for (i = 0; i < AMPDU_MAX_SCB_TID; i++) {
		ampdu->retry_limit_tid[i] = ampdu->retry_limit;
		ampdu->rr_retry_limit_tid[i] = ampdu->rr_retry_limit;
	}

	brcms_c_scb_ampdu_update_max_txlen(ampdu, ampdu->dur);
	ampdu->mfbr = false;
	/* try to set ampdu to the default value */
	brcms_c_ampdu_set(ampdu, wlc->pub->_ampdu);

	ampdu->tx_max_funl = FFPLD_TX_MAX_UNFL;
	brcms_c_ffpld_init(ampdu);

	return ampdu;
}