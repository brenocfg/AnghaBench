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
struct ieee80211_bss_conf {scalar_t__ enable_beacon; int /*<<< orphan*/  ibss_creator; } ;
struct ieee80211_vif {struct ieee80211_bss_conf bss_conf; } ;
struct ath_beacon_config {int enable_beacon; scalar_t__ beacon_interval; } ;
struct ath_softc {int nbcnvifs; int ps_flags; int /*<<< orphan*/  sc_flags; int /*<<< orphan*/  sc_pm_lock; TYPE_1__* sc_ah; struct ath_beacon_config cur_beacon_conf; } ;
struct TYPE_2__ {scalar_t__ opmode; } ;

/* Variables and functions */
 int BSS_CHANGED_BEACON_ENABLED ; 
 int BSS_CHANGED_IBSS ; 
 scalar_t__ NL80211_IFTYPE_STATION ; 
 int PS_BEACON_SYNC ; 
 int PS_WAIT_FOR_BEACON ; 
 int /*<<< orphan*/  SC_OP_BEACONS ; 
 int /*<<< orphan*/  ath9k_cache_beacon_config (struct ath_softc*,struct ieee80211_bss_conf*) ; 
 int /*<<< orphan*/  ath9k_set_beacon (struct ath_softc*) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void ath9k_beacon_config(struct ath_softc *sc, struct ieee80211_vif *vif,
			 u32 changed)
{
	struct ieee80211_bss_conf *bss_conf = &vif->bss_conf;
	struct ath_beacon_config *cur_conf = &sc->cur_beacon_conf;
	unsigned long flags;
	bool skip_beacon = false;

	if (sc->sc_ah->opmode == NL80211_IFTYPE_STATION) {
		ath9k_cache_beacon_config(sc, bss_conf);
		ath9k_set_beacon(sc);
		set_bit(SC_OP_BEACONS, &sc->sc_flags);
		return;

	}

	/*
	 * Take care of multiple interfaces when
	 * enabling/disabling SWBA.
	 */
	if (changed & BSS_CHANGED_BEACON_ENABLED) {
		if (!bss_conf->enable_beacon &&
		    (sc->nbcnvifs <= 1)) {
			cur_conf->enable_beacon = false;
		} else if (bss_conf->enable_beacon) {
			cur_conf->enable_beacon = true;
			ath9k_cache_beacon_config(sc, bss_conf);
		}
	}

	/*
	 * Configure the HW beacon registers only when we have a valid
	 * beacon interval.
	 */
	if (cur_conf->beacon_interval) {
		/*
		 * If we are joining an existing IBSS network, start beaconing
		 * only after a TSF-sync has taken place. Ensure that this
		 * happens by setting the appropriate flags.
		 */
		if ((changed & BSS_CHANGED_IBSS) && !bss_conf->ibss_creator &&
		    bss_conf->enable_beacon) {
			spin_lock_irqsave(&sc->sc_pm_lock, flags);
			sc->ps_flags |= PS_BEACON_SYNC | PS_WAIT_FOR_BEACON;
			spin_unlock_irqrestore(&sc->sc_pm_lock, flags);
			skip_beacon = true;
		} else {
			ath9k_set_beacon(sc);
		}

		/*
		 * Do not set the SC_OP_BEACONS flag for IBSS joiner mode
		 * here, it is done in ath9k_beacon_config_adhoc().
		 */
		if (cur_conf->enable_beacon && !skip_beacon)
			set_bit(SC_OP_BEACONS, &sc->sc_flags);
		else
			clear_bit(SC_OP_BEACONS, &sc->sc_flags);
	}
}