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
struct ieee80211_hw {struct adm8211_priv* priv; } ;
struct ieee80211_bss_conf {int /*<<< orphan*/  bssid; } ;
struct adm8211_priv {int /*<<< orphan*/  bssid; } ;

/* Variables and functions */
 int BSS_CHANGED_BSSID ; 
 int /*<<< orphan*/  ETH_ALEN ; 
 int /*<<< orphan*/  adm8211_set_bssid (struct ieee80211_hw*,int /*<<< orphan*/ ) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void adm8211_bss_info_changed(struct ieee80211_hw *dev,
				     struct ieee80211_vif *vif,
				     struct ieee80211_bss_conf *conf,
				     u32 changes)
{
	struct adm8211_priv *priv = dev->priv;

	if (!(changes & BSS_CHANGED_BSSID))
		return;

	if (memcmp(conf->bssid, priv->bssid, ETH_ALEN)) {
		adm8211_set_bssid(dev, conf->bssid);
		memcpy(priv->bssid, conf->bssid, ETH_ALEN);
	}
}