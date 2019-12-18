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
struct ath_softc {int /*<<< orphan*/  rx_poll_timer; scalar_t__ hw_busy_count; int /*<<< orphan*/  hw; struct ath_hw* sc_ah; } ;
struct ath_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ath9k_debug_samp_bb_mac (struct ath_softc*) ; 
 int /*<<< orphan*/  ath9k_hw_disable_interrupts (struct ath_hw*) ; 
 int /*<<< orphan*/  ath_drain_all_txq (struct ath_softc*) ; 
 int /*<<< orphan*/  ath_stop_ani (struct ath_softc*) ; 
 int /*<<< orphan*/  ath_stoprecv (struct ath_softc*) ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ieee80211_stop_queues (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool ath_prepare_reset(struct ath_softc *sc)
{
	struct ath_hw *ah = sc->sc_ah;
	bool ret = true;

	ieee80211_stop_queues(sc->hw);

	sc->hw_busy_count = 0;
	ath_stop_ani(sc);
	del_timer_sync(&sc->rx_poll_timer);

	ath9k_debug_samp_bb_mac(sc);
	ath9k_hw_disable_interrupts(ah);

	if (!ath_drain_all_txq(sc))
		ret = false;

	if (!ath_stoprecv(sc))
		ret = false;

	return ret;
}