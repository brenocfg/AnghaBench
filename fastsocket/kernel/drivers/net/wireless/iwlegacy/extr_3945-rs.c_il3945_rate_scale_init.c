#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {size_t last_rx_rssi; } ;
struct TYPE_10__ {int flags; } ;
struct il_priv {int band; TYPE_5__ _3945; TYPE_4__ active; TYPE_3__* stations; int /*<<< orphan*/  vif; } ;
struct il3945_rs_sta {int tgg; size_t start_rate; int /*<<< orphan*/  lock; int /*<<< orphan*/  expected_tpt; } ;
struct il3945_sta_priv {struct il3945_rs_sta rs_sta; } ;
struct ieee80211_sta {scalar_t__ drv_priv; } ;
struct ieee80211_hw {struct il_priv* priv; } ;
typedef  size_t s32 ;
struct TYPE_12__ {int /*<<< orphan*/  plcp; } ;
struct TYPE_7__ {int /*<<< orphan*/  addr; } ;
struct TYPE_8__ {TYPE_1__ sta; } ;
struct TYPE_9__ {TYPE_2__ sta; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 int /*<<< orphan*/  D_RATE (char*,...) ; 
#define  IEEE80211_BAND_2GHZ 129 
#define  IEEE80211_BAND_5GHZ 128 
 size_t IL_MIN_RSSI_VAL ; 
 int RXON_FLG_TGG_PROTECT_MSK ; 
 struct ieee80211_sta* ieee80211_find_sta (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  il3945_expected_tpt_a ; 
 int /*<<< orphan*/  il3945_expected_tpt_g ; 
 int /*<<< orphan*/  il3945_expected_tpt_g_prot ; 
 size_t il3945_get_rate_idx_by_rssi (size_t,int) ; 
 TYPE_6__* il3945_rates ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void
il3945_rate_scale_init(struct ieee80211_hw *hw, s32 sta_id)
{
	struct il_priv *il = hw->priv;
	s32 rssi = 0;
	unsigned long flags;
	struct il3945_rs_sta *rs_sta;
	struct ieee80211_sta *sta;
	struct il3945_sta_priv *psta;

	D_RATE("enter\n");

	rcu_read_lock();

	sta = ieee80211_find_sta(il->vif, il->stations[sta_id].sta.sta.addr);
	if (!sta) {
		D_RATE("Unable to find station to initialize rate scaling.\n");
		rcu_read_unlock();
		return;
	}

	psta = (void *)sta->drv_priv;
	rs_sta = &psta->rs_sta;

	spin_lock_irqsave(&rs_sta->lock, flags);

	rs_sta->tgg = 0;
	switch (il->band) {
	case IEEE80211_BAND_2GHZ:
		/* TODO: this always does G, not a regression */
		if (il->active.flags & RXON_FLG_TGG_PROTECT_MSK) {
			rs_sta->tgg = 1;
			rs_sta->expected_tpt = il3945_expected_tpt_g_prot;
		} else
			rs_sta->expected_tpt = il3945_expected_tpt_g;
		break;
	case IEEE80211_BAND_5GHZ:
		rs_sta->expected_tpt = il3945_expected_tpt_a;
		break;
	default:
		BUG();
		break;
	}

	spin_unlock_irqrestore(&rs_sta->lock, flags);

	rssi = il->_3945.last_rx_rssi;
	if (rssi == 0)
		rssi = IL_MIN_RSSI_VAL;

	D_RATE("Network RSSI: %d\n", rssi);

	rs_sta->start_rate = il3945_get_rate_idx_by_rssi(rssi, il->band);

	D_RATE("leave: rssi %d assign rate idx: " "%d (plcp 0x%x)\n", rssi,
	       rs_sta->start_rate, il3945_rates[rs_sta->start_rate].plcp);
	rcu_read_unlock();
}