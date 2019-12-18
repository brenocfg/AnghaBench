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
struct ieee80211_hw {struct ath_softc* priv; } ;
struct ieee80211_hdr {int dummy; } ;
struct ath_softc {int last_rssi; } ;
struct ath_rx_status {int rs_rssi; int /*<<< orphan*/  rs_moreaggr; int /*<<< orphan*/  is_mybeacon; } ;
struct TYPE_2__ {int avgbrssi; } ;
struct ath_hw {scalar_t__ opmode; TYPE_1__ stats; } ;
struct ath_common {struct ath_hw* ah; } ;

/* Variables and functions */
 int ATH9K_RSSI_BAD ; 
 int ATH_EP_RND (int,int /*<<< orphan*/ ) ; 
 int ATH_RSSI_DUMMY_MARKER ; 
 int /*<<< orphan*/  ATH_RSSI_EP_MULTIPLIER ; 
 int /*<<< orphan*/  ATH_RSSI_LPF (int,int) ; 
 scalar_t__ NL80211_IFTYPE_ADHOC ; 
 scalar_t__ NL80211_IFTYPE_STATION ; 
 scalar_t__ likely (int) ; 

__attribute__((used)) static void ath9k_process_rssi(struct ath_common *common,
			       struct ieee80211_hw *hw,
			       struct ieee80211_hdr *hdr,
			       struct ath_rx_status *rx_stats)
{
	struct ath_softc *sc = hw->priv;
	struct ath_hw *ah = common->ah;
	int last_rssi;
	int rssi = rx_stats->rs_rssi;

	if (!rx_stats->is_mybeacon ||
	    ((ah->opmode != NL80211_IFTYPE_STATION) &&
	     (ah->opmode != NL80211_IFTYPE_ADHOC)))
		return;

	if (rx_stats->rs_rssi != ATH9K_RSSI_BAD && !rx_stats->rs_moreaggr)
		ATH_RSSI_LPF(sc->last_rssi, rx_stats->rs_rssi);

	last_rssi = sc->last_rssi;
	if (likely(last_rssi != ATH_RSSI_DUMMY_MARKER))
		rssi = ATH_EP_RND(last_rssi, ATH_RSSI_EP_MULTIPLIER);
	if (rssi < 0)
		rssi = 0;

	/* Update Beacon RSSI, this is used by ANI. */
	ah->stats.avgbrssi = rssi;
}