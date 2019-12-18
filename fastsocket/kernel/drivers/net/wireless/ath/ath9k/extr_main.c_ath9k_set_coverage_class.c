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
typedef  int /*<<< orphan*/  u8 ;
struct ieee80211_hw {struct ath_softc* priv; } ;
struct ath_softc {int /*<<< orphan*/  mutex; struct ath_hw* sc_ah; } ;
struct ath_hw {int /*<<< orphan*/  coverage_class; } ;

/* Variables and functions */
 int /*<<< orphan*/  ath9k_hw_init_global_settings (struct ath_hw*) ; 
 int /*<<< orphan*/  ath9k_ps_restore (struct ath_softc*) ; 
 int /*<<< orphan*/  ath9k_ps_wakeup (struct ath_softc*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ath9k_set_coverage_class(struct ieee80211_hw *hw, u8 coverage_class)
{
	struct ath_softc *sc = hw->priv;
	struct ath_hw *ah = sc->sc_ah;

	mutex_lock(&sc->mutex);
	ah->coverage_class = coverage_class;

	ath9k_ps_wakeup(sc);
	ath9k_hw_init_global_settings(ah);
	ath9k_ps_restore(sc);

	mutex_unlock(&sc->mutex);
}