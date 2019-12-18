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
struct ieee80211_hw {struct ath_softc* priv; } ;
struct ath_softc {scalar_t__ scanning; } ;

/* Variables and functions */

__attribute__((used)) static void ath9k_sw_scan_complete(struct ieee80211_hw *hw)
{
	struct ath_softc *sc = hw->priv;

	sc->scanning = 0;
}