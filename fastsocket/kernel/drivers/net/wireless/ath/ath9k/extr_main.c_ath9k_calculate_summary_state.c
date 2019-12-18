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
struct ieee80211_vif {int dummy; } ;
struct ieee80211_hw {struct ath_softc* priv; } ;
struct ath_softc {int /*<<< orphan*/  hw; int /*<<< orphan*/  sc_flags; struct ath_hw* sc_ah; } ;
struct ath_hw {int opmode; int /*<<< orphan*/  imask; } ;
struct ath_common {int /*<<< orphan*/  bssidmask; } ;
struct ath9k_vif_iter_data {scalar_t__ naps; scalar_t__ nmeshes; scalar_t__ nadhocs; scalar_t__ nstations; scalar_t__ nwds; int /*<<< orphan*/  mask; } ;
typedef  enum nl80211_iftype { ____Placeholder_nl80211_iftype } nl80211_iftype ;

/* Variables and functions */
 int /*<<< orphan*/  ATH9K_INT_TSFOOR ; 
 int /*<<< orphan*/  ETH_ALEN ; 
 int /*<<< orphan*/  IEEE80211_IFACE_ITER_RESUME_ALL ; 
 int NL80211_IFTYPE_ADHOC ; 
 int NL80211_IFTYPE_AP ; 
 int NL80211_IFTYPE_MESH_POINT ; 
 scalar_t__ NL80211_IFTYPE_STATION ; 
 int /*<<< orphan*/  SC_OP_PRIM_STA_VIF ; 
 int /*<<< orphan*/  ath9k_calculate_iter_data (struct ieee80211_hw*,struct ieee80211_vif*,struct ath9k_vif_iter_data*) ; 
 struct ath_common* ath9k_hw_common (struct ath_hw*) ; 
 int /*<<< orphan*/  ath9k_hw_set_interrupts (struct ath_hw*) ; 
 int /*<<< orphan*/  ath9k_hw_set_tsfadjust (struct ath_hw*,int) ; 
 int /*<<< orphan*/  ath9k_hw_setopmode (struct ath_hw*) ; 
 int /*<<< orphan*/  ath9k_sta_vif_iter ; 
 int /*<<< orphan*/  ath_hw_setbssidmask (struct ath_common*) ; 
 int /*<<< orphan*/  ieee80211_iterate_active_interfaces_atomic (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ath_softc*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ath9k_calculate_summary_state(struct ieee80211_hw *hw,
					  struct ieee80211_vif *vif)
{
	struct ath_softc *sc = hw->priv;
	struct ath_hw *ah = sc->sc_ah;
	struct ath_common *common = ath9k_hw_common(ah);
	struct ath9k_vif_iter_data iter_data;
	enum nl80211_iftype old_opmode = ah->opmode;

	ath9k_calculate_iter_data(hw, vif, &iter_data);

	memcpy(common->bssidmask, iter_data.mask, ETH_ALEN);
	ath_hw_setbssidmask(common);

	if (iter_data.naps > 0) {
		ath9k_hw_set_tsfadjust(ah, true);
		ah->opmode = NL80211_IFTYPE_AP;
	} else {
		ath9k_hw_set_tsfadjust(ah, false);

		if (iter_data.nmeshes)
			ah->opmode = NL80211_IFTYPE_MESH_POINT;
		else if (iter_data.nwds)
			ah->opmode = NL80211_IFTYPE_AP;
		else if (iter_data.nadhocs)
			ah->opmode = NL80211_IFTYPE_ADHOC;
		else
			ah->opmode = NL80211_IFTYPE_STATION;
	}

	ath9k_hw_setopmode(ah);

	if ((iter_data.nstations + iter_data.nadhocs + iter_data.nmeshes) > 0)
		ah->imask |= ATH9K_INT_TSFOOR;
	else
		ah->imask &= ~ATH9K_INT_TSFOOR;

	ath9k_hw_set_interrupts(ah);

	/*
	 * If we are changing the opmode to STATION,
	 * a beacon sync needs to be done.
	 */
	if (ah->opmode == NL80211_IFTYPE_STATION &&
	    old_opmode == NL80211_IFTYPE_AP &&
	    test_bit(SC_OP_PRIM_STA_VIF, &sc->sc_flags)) {
		ieee80211_iterate_active_interfaces_atomic(
			sc->hw, IEEE80211_IFACE_ITER_RESUME_ALL,
			ath9k_sta_vif_iter, sc);
	}
}