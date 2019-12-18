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
typedef  int u32 ;
struct ieee80211_vif {int dummy; } ;
struct ieee80211_sta {int /*<<< orphan*/  addr; } ;
struct ieee80211_hw {struct ath9k_htc_priv* priv; } ;
struct ath_common {int dummy; } ;
struct ath9k_htc_target_rate {int /*<<< orphan*/  capflags; } ;
struct ath9k_htc_priv {int /*<<< orphan*/  mutex; int /*<<< orphan*/  ah; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG ; 
 int IEEE80211_RC_SUPP_RATES_CHANGED ; 
 int /*<<< orphan*/  ath9k_htc_ps_restore (struct ath9k_htc_priv*) ; 
 int /*<<< orphan*/  ath9k_htc_ps_wakeup (struct ath9k_htc_priv*) ; 
 int /*<<< orphan*/  ath9k_htc_send_rate_cmd (struct ath9k_htc_priv*,struct ath9k_htc_target_rate*) ; 
 int /*<<< orphan*/  ath9k_htc_setup_rate (struct ath9k_htc_priv*,struct ieee80211_sta*,struct ath9k_htc_target_rate*) ; 
 struct ath_common* ath9k_hw_common (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ath_dbg (struct ath_common*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  be32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct ath9k_htc_target_rate*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ath9k_htc_sta_rc_update(struct ieee80211_hw *hw,
				    struct ieee80211_vif *vif,
				    struct ieee80211_sta *sta, u32 changed)
{
	struct ath9k_htc_priv *priv = hw->priv;
	struct ath_common *common = ath9k_hw_common(priv->ah);
	struct ath9k_htc_target_rate trate;

	mutex_lock(&priv->mutex);
	ath9k_htc_ps_wakeup(priv);

	if (changed & IEEE80211_RC_SUPP_RATES_CHANGED) {
		memset(&trate, 0, sizeof(struct ath9k_htc_target_rate));
		ath9k_htc_setup_rate(priv, sta, &trate);
		if (!ath9k_htc_send_rate_cmd(priv, &trate))
			ath_dbg(common, CONFIG,
				"Supported rates for sta: %pM updated, rate caps: 0x%X\n",
				sta->addr, be32_to_cpu(trate.capflags));
		else
			ath_dbg(common, CONFIG,
				"Unable to update supported rates for sta: %pM\n",
				sta->addr);
	}

	ath9k_htc_ps_restore(priv);
	mutex_unlock(&priv->mutex);
}