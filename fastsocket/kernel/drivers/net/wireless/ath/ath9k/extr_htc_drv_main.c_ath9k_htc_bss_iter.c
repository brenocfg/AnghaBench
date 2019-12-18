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
typedef  int /*<<< orphan*/  u8 ;
struct ieee80211_bss_conf {int /*<<< orphan*/  bssid; int /*<<< orphan*/  aid; scalar_t__ assoc; } ;
struct ieee80211_vif {scalar_t__ type; struct ieee80211_bss_conf bss_conf; } ;
struct ath_common {int /*<<< orphan*/  curbssid; int /*<<< orphan*/  curaid; } ;
struct ath9k_htc_priv {int /*<<< orphan*/  ah; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_ALEN ; 
 scalar_t__ NL80211_IFTYPE_STATION ; 
 struct ath_common* ath9k_hw_common (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ath9k_htc_bss_iter(void *data, u8 *mac, struct ieee80211_vif *vif)
{
	struct ath9k_htc_priv *priv = (struct ath9k_htc_priv *)data;
	struct ath_common *common = ath9k_hw_common(priv->ah);
	struct ieee80211_bss_conf *bss_conf = &vif->bss_conf;

	if ((vif->type == NL80211_IFTYPE_STATION) && bss_conf->assoc) {
		common->curaid = bss_conf->aid;
		memcpy(common->curbssid, bss_conf->bssid, ETH_ALEN);
	}
}