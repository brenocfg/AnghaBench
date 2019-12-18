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
struct ieee80211_hw {struct ath_softc* priv; } ;
struct TYPE_3__ {int enabled; int endless; } ;
struct ath_softc {int spectral_mode; TYPE_1__ spec_config; struct ath_hw* sc_ah; } ;
struct ath_hw {int dummy; } ;
struct ath_common {int dummy; } ;
typedef  enum spectral_mode { ____Placeholder_spectral_mode } spectral_mode ;
struct TYPE_4__ {int /*<<< orphan*/  (* spectral_scan_config ) (struct ath_hw*,TYPE_1__*) ;int /*<<< orphan*/  spectral_scan_trigger; } ;

/* Variables and functions */
#define  SPECTRAL_BACKGROUND 131 
#define  SPECTRAL_CHANSCAN 130 
#define  SPECTRAL_DISABLED 129 
#define  SPECTRAL_MANUAL 128 
 struct ath_common* ath9k_hw_common (struct ath_hw*) ; 
 TYPE_2__* ath9k_hw_ops (struct ath_hw*) ; 
 int /*<<< orphan*/  ath9k_ps_restore (struct ath_softc*) ; 
 int /*<<< orphan*/  ath9k_ps_wakeup (struct ath_softc*) ; 
 int /*<<< orphan*/  ath_err (struct ath_common*,char*) ; 
 int /*<<< orphan*/  stub1 (struct ath_hw*,TYPE_1__*) ; 

int ath9k_spectral_scan_config(struct ieee80211_hw *hw,
			       enum spectral_mode spectral_mode)
{
	struct ath_softc *sc = hw->priv;
	struct ath_hw *ah = sc->sc_ah;
	struct ath_common *common = ath9k_hw_common(ah);

	if (!ath9k_hw_ops(ah)->spectral_scan_trigger) {
		ath_err(common, "spectrum analyzer not implemented on this hardware\n");
		return -1;
	}

	switch (spectral_mode) {
	case SPECTRAL_DISABLED:
		sc->spec_config.enabled = 0;
		break;
	case SPECTRAL_BACKGROUND:
		/* send endless samples.
		 * TODO: is this really useful for "background"?
		 */
		sc->spec_config.endless = 1;
		sc->spec_config.enabled = 1;
		break;
	case SPECTRAL_CHANSCAN:
	case SPECTRAL_MANUAL:
		sc->spec_config.endless = 0;
		sc->spec_config.enabled = 1;
		break;
	default:
		return -1;
	}

	ath9k_ps_wakeup(sc);
	ath9k_hw_ops(ah)->spectral_scan_config(ah, &sc->spec_config);
	ath9k_ps_restore(sc);

	sc->spectral_mode = spectral_mode;

	return 0;
}