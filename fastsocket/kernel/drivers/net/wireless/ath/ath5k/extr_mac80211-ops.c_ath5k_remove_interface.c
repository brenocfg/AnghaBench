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
struct ieee80211_hw {struct ath5k_hw* priv; } ;
struct ath5k_vif {scalar_t__ opmode; TYPE_1__* bbuf; } ;
struct ath5k_hw {int /*<<< orphan*/  lock; int /*<<< orphan*/  num_mesh_vifs; int /*<<< orphan*/  num_adhoc_vifs; int /*<<< orphan*/  num_ap_vifs; struct ieee80211_vif** bslot; int /*<<< orphan*/  bcbuf; int /*<<< orphan*/  nvifs; } ;
struct TYPE_2__ {int /*<<< orphan*/  list; } ;

/* Variables and functions */
 unsigned int ATH_BCBUF ; 
 scalar_t__ NL80211_IFTYPE_ADHOC ; 
 scalar_t__ NL80211_IFTYPE_AP ; 
 scalar_t__ NL80211_IFTYPE_MESH_POINT ; 
 int /*<<< orphan*/  ath5k_txbuf_free_skb (struct ath5k_hw*,TYPE_1__*) ; 
 int /*<<< orphan*/  ath5k_update_bssid_mask_and_opmode (struct ath5k_hw*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
ath5k_remove_interface(struct ieee80211_hw *hw,
		       struct ieee80211_vif *vif)
{
	struct ath5k_hw *ah = hw->priv;
	struct ath5k_vif *avf = (void *)vif->drv_priv;
	unsigned int i;

	mutex_lock(&ah->lock);
	ah->nvifs--;

	if (avf->bbuf) {
		ath5k_txbuf_free_skb(ah, avf->bbuf);
		list_add_tail(&avf->bbuf->list, &ah->bcbuf);
		for (i = 0; i < ATH_BCBUF; i++) {
			if (ah->bslot[i] == vif) {
				ah->bslot[i] = NULL;
				break;
			}
		}
		avf->bbuf = NULL;
	}
	if (avf->opmode == NL80211_IFTYPE_AP)
		ah->num_ap_vifs--;
	else if (avf->opmode == NL80211_IFTYPE_ADHOC)
		ah->num_adhoc_vifs--;
	else if (avf->opmode == NL80211_IFTYPE_MESH_POINT)
		ah->num_mesh_vifs--;

	ath5k_update_bssid_mask_and_opmode(ah, NULL);
	mutex_unlock(&ah->lock);
}