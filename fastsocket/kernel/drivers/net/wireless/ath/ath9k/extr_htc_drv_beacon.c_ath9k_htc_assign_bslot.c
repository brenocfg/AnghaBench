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
struct ieee80211_vif {scalar_t__ drv_priv; } ;
struct ath_common {int dummy; } ;
struct ath9k_htc_vif {int bslot; } ;
struct TYPE_2__ {struct ieee80211_vif** bslot; } ;
struct ath9k_htc_priv {int /*<<< orphan*/  beacon_lock; TYPE_1__ cur_beacon_conf; int /*<<< orphan*/  ah; } ;

/* Variables and functions */
 int ATH9K_HTC_MAX_BCN_VIF ; 
 int /*<<< orphan*/  CONFIG ; 
 struct ath_common* ath9k_hw_common (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ath_dbg (struct ath_common*,int /*<<< orphan*/ ,char*,size_t) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

void ath9k_htc_assign_bslot(struct ath9k_htc_priv *priv,
			    struct ieee80211_vif *vif)
{
	struct ath_common *common = ath9k_hw_common(priv->ah);
	struct ath9k_htc_vif *avp = (struct ath9k_htc_vif *)vif->drv_priv;
	int i = 0;

	spin_lock_bh(&priv->beacon_lock);
	for (i = 0; i < ATH9K_HTC_MAX_BCN_VIF; i++) {
		if (priv->cur_beacon_conf.bslot[i] == NULL) {
			avp->bslot = i;
			break;
		}
	}

	priv->cur_beacon_conf.bslot[avp->bslot] = vif;
	spin_unlock_bh(&priv->beacon_lock);

	ath_dbg(common, CONFIG, "Added interface at beacon slot: %d\n",
		avp->bslot);
}