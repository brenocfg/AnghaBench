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
struct ieee80211_vif {int type; int p2p; } ;
struct ieee80211_hw {struct ath_softc* priv; } ;
struct ath_softc {int /*<<< orphan*/  mutex; int /*<<< orphan*/  sc_ah; } ;
struct ath_common {int dummy; } ;
typedef  enum nl80211_iftype { ____Placeholder_nl80211_iftype } nl80211_iftype ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG ; 
 int /*<<< orphan*/  ath9k_beacon_assign_slot (struct ath_softc*,struct ieee80211_vif*) ; 
 int /*<<< orphan*/  ath9k_beacon_remove_slot (struct ath_softc*,struct ieee80211_vif*) ; 
 int /*<<< orphan*/  ath9k_calculate_summary_state (struct ieee80211_hw*,struct ieee80211_vif*) ; 
 struct ath_common* ath9k_hw_common (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ath9k_ps_restore (struct ath_softc*) ; 
 int /*<<< orphan*/  ath9k_ps_wakeup (struct ath_softc*) ; 
 scalar_t__ ath9k_uses_beacons (int) ; 
 int /*<<< orphan*/  ath_dbg (struct ath_common*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ath9k_change_interface(struct ieee80211_hw *hw,
				  struct ieee80211_vif *vif,
				  enum nl80211_iftype new_type,
				  bool p2p)
{
	struct ath_softc *sc = hw->priv;
	struct ath_common *common = ath9k_hw_common(sc->sc_ah);

	ath_dbg(common, CONFIG, "Change Interface\n");
	mutex_lock(&sc->mutex);

	if (ath9k_uses_beacons(vif->type))
		ath9k_beacon_remove_slot(sc, vif);

	vif->type = new_type;
	vif->p2p = p2p;

	ath9k_ps_wakeup(sc);
	ath9k_calculate_summary_state(hw, vif);
	ath9k_ps_restore(sc);

	if (ath9k_uses_beacons(vif->type))
		ath9k_beacon_assign_slot(sc, vif);

	mutex_unlock(&sc->mutex);
	return 0;
}