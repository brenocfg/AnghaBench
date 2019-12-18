#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct ath9k_hw_cal_data {int dummy; } ;
struct ath_softc {int /*<<< orphan*/  intr_tq; int /*<<< orphan*/  sc_pcu_lock; TYPE_2__* hw; struct ath_hw* sc_ah; struct ath9k_hw_cal_data caldata; } ;
struct ath_hw {struct ath9k_channel* curchan; } ;
struct ath_common {int dummy; } ;
struct ath9k_channel {int /*<<< orphan*/  channel; } ;
struct TYPE_3__ {int flags; } ;
struct TYPE_4__ {TYPE_1__ conf; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG ; 
 int EIO ; 
 int IEEE80211_CONF_OFFCHANNEL ; 
 int /*<<< orphan*/  IS_CHAN_HT40 (struct ath9k_channel*) ; 
 int /*<<< orphan*/  RESET_TYPE_BB_HANG ; 
 int /*<<< orphan*/  __ath_cancel_work (struct ath_softc*) ; 
 struct ath_common* ath9k_hw_common (struct ath_hw*) ; 
 int /*<<< orphan*/  ath9k_hw_enable_interrupts (struct ath_hw*) ; 
 scalar_t__ ath9k_hw_mci_is_enabled (struct ath_hw*) ; 
 int ath9k_hw_reset (struct ath_hw*,struct ath9k_channel*,struct ath9k_hw_cal_data*,int) ; 
 int /*<<< orphan*/  ath9k_mci_set_txpower (struct ath_softc*,int,int) ; 
 int /*<<< orphan*/  ath9k_queue_reset (struct ath_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ath_complete_reset (struct ath_softc*,int) ; 
 int /*<<< orphan*/  ath_dbg (struct ath_common*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ath_err (struct ath_common*,char*,int) ; 
 int /*<<< orphan*/  ath_prepare_reset (struct ath_softc*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tasklet_disable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tasklet_enable (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ath_reset_internal(struct ath_softc *sc, struct ath9k_channel *hchan)
{
	struct ath_hw *ah = sc->sc_ah;
	struct ath_common *common = ath9k_hw_common(ah);
	struct ath9k_hw_cal_data *caldata = NULL;
	bool fastcc = true;
	int r;

	__ath_cancel_work(sc);

	tasklet_disable(&sc->intr_tq);
	spin_lock_bh(&sc->sc_pcu_lock);

	if (!(sc->hw->conf.flags & IEEE80211_CONF_OFFCHANNEL)) {
		fastcc = false;
		caldata = &sc->caldata;
	}

	if (!hchan) {
		fastcc = false;
		hchan = ah->curchan;
	}

	if (!ath_prepare_reset(sc))
		fastcc = false;

	ath_dbg(common, CONFIG, "Reset to %u MHz, HT40: %d fastcc: %d\n",
		hchan->channel, IS_CHAN_HT40(hchan), fastcc);

	r = ath9k_hw_reset(ah, hchan, caldata, fastcc);
	if (r) {
		ath_err(common,
			"Unable to reset channel, reset status %d\n", r);

		ath9k_hw_enable_interrupts(ah);
		ath9k_queue_reset(sc, RESET_TYPE_BB_HANG);

		goto out;
	}

	if (ath9k_hw_mci_is_enabled(sc->sc_ah) &&
	    (sc->hw->conf.flags & IEEE80211_CONF_OFFCHANNEL))
		ath9k_mci_set_txpower(sc, true, false);

	if (!ath_complete_reset(sc, true))
		r = -EIO;

out:
	spin_unlock_bh(&sc->sc_pcu_lock);
	tasklet_enable(&sc->intr_tq);

	return r;
}