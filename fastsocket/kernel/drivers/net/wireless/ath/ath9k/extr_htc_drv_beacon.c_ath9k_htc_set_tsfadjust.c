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
typedef  int u64 ;
struct ieee80211_vif {scalar_t__ drv_priv; } ;
struct htc_beacon_config {int beacon_interval; } ;
struct ath_common {int dummy; } ;
struct ath9k_htc_vif {int bslot; int /*<<< orphan*/  tsfadjust; } ;
struct ath9k_htc_priv {struct htc_beacon_config cur_beacon_conf; int /*<<< orphan*/  ah; } ;

/* Variables and functions */
 int ATH9K_HTC_MAX_BCN_VIF ; 
 int /*<<< orphan*/  CONFIG ; 
 int /*<<< orphan*/  TU_TO_USEC (int) ; 
 struct ath_common* ath9k_hw_common (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ath_dbg (struct ath_common*,int /*<<< orphan*/ ,char*,unsigned long long,int) ; 
 int /*<<< orphan*/  cpu_to_le64 (int /*<<< orphan*/ ) ; 

void ath9k_htc_set_tsfadjust(struct ath9k_htc_priv *priv,
			     struct ieee80211_vif *vif)
{
	struct ath_common *common = ath9k_hw_common(priv->ah);
	struct ath9k_htc_vif *avp = (struct ath9k_htc_vif *)vif->drv_priv;
	struct htc_beacon_config *cur_conf = &priv->cur_beacon_conf;
	u64 tsfadjust;

	if (avp->bslot == 0)
		return;

	/*
	 * The beacon interval cannot be different for multi-AP mode,
	 * and we reach here only for VIF slots greater than zero,
	 * so beacon_interval is guaranteed to be set in cur_conf.
	 */
	tsfadjust = cur_conf->beacon_interval * avp->bslot / ATH9K_HTC_MAX_BCN_VIF;
	avp->tsfadjust = cpu_to_le64(TU_TO_USEC(tsfadjust));

	ath_dbg(common, CONFIG, "tsfadjust is: %llu for bslot: %d\n",
		(unsigned long long)tsfadjust, avp->bslot);
}