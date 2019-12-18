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
struct ath_softc {int /*<<< orphan*/  hw_reset_work; int /*<<< orphan*/  hw; int /*<<< orphan*/  sc_flags; } ;
typedef  enum ath_reset_type { ____Placeholder_ath_reset_type } ath_reset_type ;

/* Variables and functions */
 int /*<<< orphan*/  RESET_STAT_INC (struct ath_softc*,int) ; 
 int /*<<< orphan*/  SC_OP_HW_RESET ; 
 int /*<<< orphan*/  ieee80211_queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void ath9k_queue_reset(struct ath_softc *sc, enum ath_reset_type type)
{
#ifdef CONFIG_ATH9K_DEBUGFS
	RESET_STAT_INC(sc, type);
#endif
	set_bit(SC_OP_HW_RESET, &sc->sc_flags);
	ieee80211_queue_work(sc->hw, &sc->hw_reset_work);
}