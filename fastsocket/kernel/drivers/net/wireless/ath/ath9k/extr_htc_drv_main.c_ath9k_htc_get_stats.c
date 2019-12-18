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
struct ieee80211_low_level_stats {int /*<<< orphan*/  dot11RTSSuccessCount; int /*<<< orphan*/  dot11FCSErrorCount; int /*<<< orphan*/  dot11RTSFailureCount; int /*<<< orphan*/  dot11ACKFailureCount; } ;
struct ieee80211_hw {struct ath9k_htc_priv* priv; } ;
struct ath9k_mib_stats {int /*<<< orphan*/  rts_good; int /*<<< orphan*/  fcs_bad; int /*<<< orphan*/  rts_bad; int /*<<< orphan*/  ackrcv_bad; } ;
struct ath_hw {struct ath9k_mib_stats ah_mibStats; } ;
struct ath9k_htc_priv {struct ath_hw* ah; } ;

/* Variables and functions */

__attribute__((used)) static int ath9k_htc_get_stats(struct ieee80211_hw *hw,
			       struct ieee80211_low_level_stats *stats)
{
	struct ath9k_htc_priv *priv = hw->priv;
	struct ath_hw *ah = priv->ah;
	struct ath9k_mib_stats *mib_stats = &ah->ah_mibStats;

	stats->dot11ACKFailureCount = mib_stats->ackrcv_bad;
	stats->dot11RTSFailureCount = mib_stats->rts_bad;
	stats->dot11FCSErrorCount = mib_stats->fcs_bad;
	stats->dot11RTSSuccessCount = mib_stats->rts_good;

	return 0;
}