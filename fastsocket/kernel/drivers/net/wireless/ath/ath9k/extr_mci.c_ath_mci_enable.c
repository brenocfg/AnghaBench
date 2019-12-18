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
struct ath_softc {TYPE_2__* sc_ah; } ;
struct ath_common {int /*<<< orphan*/  btcoex_enabled; } ;
struct TYPE_3__ {int hw_caps; } ;
struct TYPE_4__ {int /*<<< orphan*/  imask; TYPE_1__ caps; } ;

/* Variables and functions */
 int ATH9K_HW_CAP_MCI ; 
 int /*<<< orphan*/  ATH9K_INT_MCI ; 
 struct ath_common* ath9k_hw_common (TYPE_2__*) ; 

void ath_mci_enable(struct ath_softc *sc)
{
	struct ath_common *common = ath9k_hw_common(sc->sc_ah);

	if (!common->btcoex_enabled)
		return;

	if (sc->sc_ah->caps.hw_caps & ATH9K_HW_CAP_MCI)
		sc->sc_ah->imask |= ATH9K_INT_MCI;
}