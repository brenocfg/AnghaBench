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
struct ath_softc {scalar_t__ ps_usecount; int ps_flags; int /*<<< orphan*/  sc_pm_lock; int /*<<< orphan*/  sc_ah; scalar_t__ ps_enabled; scalar_t__ ps_idle; } ;
struct ath_common {int /*<<< orphan*/  cc_lock; } ;
typedef  enum ath9k_power_mode { ____Placeholder_ath9k_power_mode } ath9k_power_mode ;

/* Variables and functions */
 int ATH9K_PM_FULL_SLEEP ; 
 int ATH9K_PM_NETWORK_SLEEP ; 
 int PS_WAIT_FOR_ANI ; 
 int PS_WAIT_FOR_BEACON ; 
 int PS_WAIT_FOR_CAB ; 
 int PS_WAIT_FOR_PSPOLL_DATA ; 
 int PS_WAIT_FOR_TX_ACK ; 
 int /*<<< orphan*/  ath9k_btcoex_stop_gen_timer (struct ath_softc*) ; 
 scalar_t__ ath9k_hw_btcoex_is_enabled (int /*<<< orphan*/ ) ; 
 struct ath_common* ath9k_hw_common (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ath9k_hw_setpower (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ath9k_hw_setrxabort (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ath9k_hw_stopdmarecv (int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  ath_hw_cycle_counters_update (struct ath_common*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void ath9k_ps_restore(struct ath_softc *sc)
{
	struct ath_common *common = ath9k_hw_common(sc->sc_ah);
	enum ath9k_power_mode mode;
	unsigned long flags;
	bool reset;

	spin_lock_irqsave(&sc->sc_pm_lock, flags);
	if (--sc->ps_usecount != 0)
		goto unlock;

	if (sc->ps_idle) {
		ath9k_hw_setrxabort(sc->sc_ah, 1);
		ath9k_hw_stopdmarecv(sc->sc_ah, &reset);
		mode = ATH9K_PM_FULL_SLEEP;
	} else if (sc->ps_enabled &&
		   !(sc->ps_flags & (PS_WAIT_FOR_BEACON |
				     PS_WAIT_FOR_CAB |
				     PS_WAIT_FOR_PSPOLL_DATA |
				     PS_WAIT_FOR_TX_ACK |
				     PS_WAIT_FOR_ANI))) {
		mode = ATH9K_PM_NETWORK_SLEEP;
		if (ath9k_hw_btcoex_is_enabled(sc->sc_ah))
			ath9k_btcoex_stop_gen_timer(sc);
	} else {
		goto unlock;
	}

	spin_lock(&common->cc_lock);
	ath_hw_cycle_counters_update(common);
	spin_unlock(&common->cc_lock);

	ath9k_hw_setpower(sc->sc_ah, mode);

 unlock:
	spin_unlock_irqrestore(&sc->sc_pm_lock, flags);
}