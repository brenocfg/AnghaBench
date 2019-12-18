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
typedef  int u32 ;
struct ieee80211_vif {scalar_t__ type; scalar_t__ drv_priv; } ;
struct ieee80211_hw {struct ath_softc* priv; } ;
struct ieee80211_bss_conf {scalar_t__ use_short_slot; scalar_t__ enable_beacon; scalar_t__ aid; int /*<<< orphan*/  bssid; int /*<<< orphan*/  assoc; } ;
struct ath_vif {int primary_sta_vif; } ;
struct TYPE_2__ {int slottime; int /*<<< orphan*/  updateslot; } ;
struct ath_softc {int /*<<< orphan*/  mutex; TYPE_1__ beacon; struct ath_hw* sc_ah; int /*<<< orphan*/  sc_flags; int /*<<< orphan*/  hw; } ;
struct ath_hw {scalar_t__ opmode; int slottime; } ;
struct ath_common {scalar_t__ curaid; int /*<<< orphan*/  curbssid; } ;

/* Variables and functions */
 int BSS_CHANGED_ASSOC ; 
 int BSS_CHANGED_BEACON_ENABLED ; 
 int BSS_CHANGED_BEACON_INT ; 
 int BSS_CHANGED_ERP_SLOT ; 
 int BSS_CHANGED_IBSS ; 
 int CHECK_ANI ; 
 int /*<<< orphan*/  CONFIG ; 
 int /*<<< orphan*/  ETH_ALEN ; 
 int /*<<< orphan*/  IEEE80211_IFACE_ITER_RESUME_ALL ; 
 scalar_t__ NL80211_IFTYPE_AP ; 
 scalar_t__ NL80211_IFTYPE_STATION ; 
 int /*<<< orphan*/  SC_OP_BEACONS ; 
 int /*<<< orphan*/  SC_OP_PRIM_STA_VIF ; 
 int /*<<< orphan*/  UPDATE ; 
 scalar_t__ ath9k_allow_beacon_config (struct ath_softc*,struct ieee80211_vif*) ; 
 int /*<<< orphan*/  ath9k_beacon_config (struct ath_softc*,struct ieee80211_vif*,int) ; 
 int /*<<< orphan*/  ath9k_bss_assoc_iter ; 
 struct ath_common* ath9k_hw_common (struct ath_hw*) ; 
 int /*<<< orphan*/  ath9k_hw_init_global_settings (struct ath_hw*) ; 
 scalar_t__ ath9k_hw_mci_is_enabled (struct ath_hw*) ; 
 int /*<<< orphan*/  ath9k_hw_write_associd (struct ath_hw*) ; 
 int /*<<< orphan*/  ath9k_mci_update_wlan_channels (struct ath_softc*,int) ; 
 int /*<<< orphan*/  ath9k_ps_restore (struct ath_softc*) ; 
 int /*<<< orphan*/  ath9k_ps_wakeup (struct ath_softc*) ; 
 int /*<<< orphan*/  ath9k_set_tsfadjust (struct ath_softc*,struct ieee80211_vif*) ; 
 int /*<<< orphan*/  ath_check_ani (struct ath_softc*) ; 
 int /*<<< orphan*/  ath_dbg (struct ath_common*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ieee80211_iterate_active_interfaces_atomic (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ath_softc*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ath9k_bss_info_changed(struct ieee80211_hw *hw,
				   struct ieee80211_vif *vif,
				   struct ieee80211_bss_conf *bss_conf,
				   u32 changed)
{
#define CHECK_ANI				\
	(BSS_CHANGED_ASSOC |			\
	 BSS_CHANGED_IBSS |			\
	 BSS_CHANGED_BEACON_ENABLED)

	struct ath_softc *sc = hw->priv;
	struct ath_hw *ah = sc->sc_ah;
	struct ath_common *common = ath9k_hw_common(ah);
	struct ath_vif *avp = (void *)vif->drv_priv;
	int slottime;

	ath9k_ps_wakeup(sc);
	mutex_lock(&sc->mutex);

	if (changed & BSS_CHANGED_ASSOC) {
		ath_dbg(common, CONFIG, "BSSID %pM Changed ASSOC %d\n",
			bss_conf->bssid, bss_conf->assoc);

		if (avp->primary_sta_vif && !bss_conf->assoc) {
			clear_bit(SC_OP_PRIM_STA_VIF, &sc->sc_flags);
			avp->primary_sta_vif = false;

			if (ah->opmode == NL80211_IFTYPE_STATION)
				clear_bit(SC_OP_BEACONS, &sc->sc_flags);
		}

		ieee80211_iterate_active_interfaces_atomic(
			sc->hw, IEEE80211_IFACE_ITER_RESUME_ALL,
			ath9k_bss_assoc_iter, sc);

		if (!test_bit(SC_OP_PRIM_STA_VIF, &sc->sc_flags) &&
		    ah->opmode == NL80211_IFTYPE_STATION) {
			memset(common->curbssid, 0, ETH_ALEN);
			common->curaid = 0;
			ath9k_hw_write_associd(sc->sc_ah);
			if (ath9k_hw_mci_is_enabled(sc->sc_ah))
				ath9k_mci_update_wlan_channels(sc, true);
		}
	}

	if (changed & BSS_CHANGED_IBSS) {
		memcpy(common->curbssid, bss_conf->bssid, ETH_ALEN);
		common->curaid = bss_conf->aid;
		ath9k_hw_write_associd(sc->sc_ah);
	}

	if ((changed & BSS_CHANGED_BEACON_ENABLED) ||
	    (changed & BSS_CHANGED_BEACON_INT)) {
		if (ah->opmode == NL80211_IFTYPE_AP &&
		    bss_conf->enable_beacon)
			ath9k_set_tsfadjust(sc, vif);
		if (ath9k_allow_beacon_config(sc, vif))
			ath9k_beacon_config(sc, vif, changed);
	}

	if (changed & BSS_CHANGED_ERP_SLOT) {
		if (bss_conf->use_short_slot)
			slottime = 9;
		else
			slottime = 20;
		if (vif->type == NL80211_IFTYPE_AP) {
			/*
			 * Defer update, so that connected stations can adjust
			 * their settings at the same time.
			 * See beacon.c for more details
			 */
			sc->beacon.slottime = slottime;
			sc->beacon.updateslot = UPDATE;
		} else {
			ah->slottime = slottime;
			ath9k_hw_init_global_settings(ah);
		}
	}

	if (changed & CHECK_ANI)
		ath_check_ani(sc);

	mutex_unlock(&sc->mutex);
	ath9k_ps_restore(sc);

#undef CHECK_ANI
}