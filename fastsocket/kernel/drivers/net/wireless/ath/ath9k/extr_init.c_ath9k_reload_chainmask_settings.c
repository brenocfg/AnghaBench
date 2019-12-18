#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct ath_softc {TYPE_2__* sbands; TYPE_1__* sc_ah; } ;
struct TYPE_6__ {int hw_caps; } ;
struct TYPE_5__ {int /*<<< orphan*/  ht_cap; } ;
struct TYPE_4__ {TYPE_3__ caps; } ;

/* Variables and functions */
 int ATH9K_HW_CAP_2GHZ ; 
 int ATH9K_HW_CAP_5GHZ ; 
 int ATH9K_HW_CAP_HT ; 
 size_t IEEE80211_BAND_2GHZ ; 
 size_t IEEE80211_BAND_5GHZ ; 
 int /*<<< orphan*/  setup_ht_cap (struct ath_softc*,int /*<<< orphan*/ *) ; 

void ath9k_reload_chainmask_settings(struct ath_softc *sc)
{
	if (!(sc->sc_ah->caps.hw_caps & ATH9K_HW_CAP_HT))
		return;

	if (sc->sc_ah->caps.hw_caps & ATH9K_HW_CAP_2GHZ)
		setup_ht_cap(sc, &sc->sbands[IEEE80211_BAND_2GHZ].ht_cap);
	if (sc->sc_ah->caps.hw_caps & ATH9K_HW_CAP_5GHZ)
		setup_ht_cap(sc, &sc->sbands[IEEE80211_BAND_5GHZ].ht_cap);
}