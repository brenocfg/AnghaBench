#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  txpowlimit; } ;
struct ath_softc {int ps_flags; int ant_rx; TYPE_4__* hw; int /*<<< orphan*/  sc_pm_lock; int /*<<< orphan*/  sc_flags; int /*<<< orphan*/  curtxpow; TYPE_1__ config; struct ath_hw* sc_ah; } ;
struct TYPE_7__ {int hw_caps; } ;
struct ath_hw {scalar_t__ opmode; TYPE_3__ caps; } ;
struct ath_common {int dummy; } ;
struct TYPE_6__ {int flags; } ;
struct TYPE_8__ {TYPE_2__ conf; } ;

/* Variables and functions */
 int ATH9K_HW_CAP_ANT_DIV_COMB ; 
 int IEEE80211_CONF_OFFCHANNEL ; 
 scalar_t__ NL80211_IFTYPE_STATION ; 
 int PS_BEACON_SYNC ; 
 int PS_WAIT_FOR_BEACON ; 
 int /*<<< orphan*/  SC_OP_BEACONS ; 
 int /*<<< orphan*/  SC_OP_HW_RESET ; 
 int /*<<< orphan*/  SC_OP_PRIM_STA_VIF ; 
 int /*<<< orphan*/  ath9k_cmn_update_txpow (struct ath_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct ath_common* ath9k_hw_common (struct ath_hw*) ; 
 int /*<<< orphan*/  ath9k_hw_enable_interrupts (struct ath_hw*) ; 
 int /*<<< orphan*/  ath9k_hw_set_interrupts (struct ath_hw*) ; 
 int /*<<< orphan*/  ath9k_set_beacon (struct ath_softc*) ; 
 int /*<<< orphan*/  ath_ant_comb_update (struct ath_softc*) ; 
 int /*<<< orphan*/  ath_err (struct ath_common*,char*) ; 
 int /*<<< orphan*/  ath_restart_work (struct ath_softc*) ; 
 scalar_t__ ath_startrecv (struct ath_softc*) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ieee80211_wake_queues (TYPE_4__*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool ath_complete_reset(struct ath_softc *sc, bool start)
{
	struct ath_hw *ah = sc->sc_ah;
	struct ath_common *common = ath9k_hw_common(ah);
	unsigned long flags;

	if (ath_startrecv(sc) != 0) {
		ath_err(common, "Unable to restart recv logic\n");
		return false;
	}

	ath9k_cmn_update_txpow(ah, sc->curtxpow,
			       sc->config.txpowlimit, &sc->curtxpow);

	clear_bit(SC_OP_HW_RESET, &sc->sc_flags);
	ath9k_hw_set_interrupts(ah);
	ath9k_hw_enable_interrupts(ah);

	if (!(sc->hw->conf.flags & IEEE80211_CONF_OFFCHANNEL) && start) {
		if (!test_bit(SC_OP_BEACONS, &sc->sc_flags))
			goto work;

		if (ah->opmode == NL80211_IFTYPE_STATION &&
		    test_bit(SC_OP_PRIM_STA_VIF, &sc->sc_flags)) {
			spin_lock_irqsave(&sc->sc_pm_lock, flags);
			sc->ps_flags |= PS_BEACON_SYNC | PS_WAIT_FOR_BEACON;
			spin_unlock_irqrestore(&sc->sc_pm_lock, flags);
		} else {
			ath9k_set_beacon(sc);
		}
	work:
		ath_restart_work(sc);
	}

	if ((ah->caps.hw_caps & ATH9K_HW_CAP_ANT_DIV_COMB) && sc->ant_rx != 3)
		ath_ant_comb_update(sc);

	ieee80211_wake_queues(sc->hw);

	return true;
}