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
struct il_vif_priv {int /*<<< orphan*/  ibss_bssid_sta_id; } ;
struct il_priv {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  bssid; } ;
struct ieee80211_vif {TYPE_1__ bss_conf; scalar_t__ drv_priv; } ;

/* Variables and functions */
 int il4965_add_bssid_station (struct il_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int il_remove_station (struct il_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
il4965_manage_ibss_station(struct il_priv *il, struct ieee80211_vif *vif,
			   bool add)
{
	struct il_vif_priv *vif_priv = (void *)vif->drv_priv;

	if (add)
		return il4965_add_bssid_station(il, vif->bss_conf.bssid,
						&vif_priv->ibss_bssid_sta_id);
	return il_remove_station(il, vif_priv->ibss_bssid_sta_id,
				 vif->bss_conf.bssid);
}