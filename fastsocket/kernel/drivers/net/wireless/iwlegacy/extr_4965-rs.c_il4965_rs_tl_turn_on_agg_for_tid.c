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
typedef  scalar_t__ u8 ;
typedef  scalar_t__ u32 ;
struct il_priv {int dummy; } ;
struct il_lq_sta {int dummy; } ;
struct ieee80211_sta {scalar_t__ addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  D_HT (char*,scalar_t__,scalar_t__) ; 
 int EAGAIN ; 
 scalar_t__ IL_AGG_LOAD_THRESHOLD ; 
 int /*<<< orphan*/  IL_ERR (char*,scalar_t__) ; 
 int ieee80211_start_tx_ba_session (struct ieee80211_sta*,scalar_t__,int) ; 
 int /*<<< orphan*/  ieee80211_stop_tx_ba_session (struct ieee80211_sta*,scalar_t__) ; 
 scalar_t__ il4965_rs_tl_get_load (struct il_lq_sta*,scalar_t__) ; 

__attribute__((used)) static int
il4965_rs_tl_turn_on_agg_for_tid(struct il_priv *il, struct il_lq_sta *lq_data,
				 u8 tid, struct ieee80211_sta *sta)
{
	int ret = -EAGAIN;
	u32 load;

	load = il4965_rs_tl_get_load(lq_data, tid);

	if (load > IL_AGG_LOAD_THRESHOLD) {
		D_HT("Starting Tx agg: STA: %pM tid: %d\n", sta->addr, tid);
		ret = ieee80211_start_tx_ba_session(sta, tid, 5000);
		if (ret == -EAGAIN) {
			/*
			 * driver and mac80211 is out of sync
			 * this might be cause by reloading firmware
			 * stop the tx ba session here
			 */
			IL_ERR("Fail start Tx agg on tid: %d\n", tid);
			ieee80211_stop_tx_ba_session(sta, tid);
		}
	} else
		D_HT("Aggregation not enabled for tid %d because load = %u\n",
		     tid, load);

	return ret;
}