#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u16 ;
struct ieee80211_hw {int /*<<< orphan*/  wiphy; } ;
struct TYPE_2__ {int /*<<< orphan*/  default_trigger; } ;
struct ath_softc {struct ieee80211_hw* hw; TYPE_1__ led_cdev; struct ath_hw* sc_ah; } ;
struct ath_regulatory {int /*<<< orphan*/  alpha2; } ;
struct ath_hw {int dummy; } ;
struct ath_common {struct ath_regulatory regulatory; } ;
struct ath_bus_ops {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ATH_RXBUF ; 
 int /*<<< orphan*/  ATH_TXBUF ; 
 int /*<<< orphan*/  IEEE80211_TPT_LEDTRIG_FL_RADIO ; 
 int /*<<< orphan*/  ath9k_deinit_debug (struct ath_softc*) ; 
 int /*<<< orphan*/  ath9k_deinit_softc (struct ath_softc*) ; 
 struct ath_common* ath9k_hw_common (struct ath_hw*) ; 
 int ath9k_init_debug (struct ath_hw*) ; 
 int ath9k_init_softc (int /*<<< orphan*/ ,struct ath_softc*,struct ath_bus_ops const*) ; 
 int /*<<< orphan*/  ath9k_init_txpower_limits (struct ath_softc*) ; 
 int /*<<< orphan*/  ath9k_reg_notifier ; 
 int /*<<< orphan*/  ath9k_set_hw_capab (struct ath_softc*,struct ieee80211_hw*) ; 
 int /*<<< orphan*/  ath9k_tpt_blink ; 
 int /*<<< orphan*/  ath_err (struct ath_common*,char*) ; 
 int /*<<< orphan*/  ath_init_leds (struct ath_softc*) ; 
 int /*<<< orphan*/  ath_is_world_regd (struct ath_regulatory*) ; 
 int ath_regd_init (struct ath_regulatory*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ath_rx_cleanup (struct ath_softc*) ; 
 int ath_rx_init (struct ath_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ath_start_rfkill_poll (struct ath_softc*) ; 
 int ath_tx_init (struct ath_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_create_tpt_led_trigger (struct ieee80211_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ieee80211_register_hw (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  ieee80211_unregister_hw (struct ieee80211_hw*) ; 
 int regulatory_hint (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int ath9k_init_device(u16 devid, struct ath_softc *sc,
		    const struct ath_bus_ops *bus_ops)
{
	struct ieee80211_hw *hw = sc->hw;
	struct ath_common *common;
	struct ath_hw *ah;
	int error = 0;
	struct ath_regulatory *reg;

	/* Bring up device */
	error = ath9k_init_softc(devid, sc, bus_ops);
	if (error)
		return error;

	ah = sc->sc_ah;
	common = ath9k_hw_common(ah);
	ath9k_set_hw_capab(sc, hw);

	/* Initialize regulatory */
	error = ath_regd_init(&common->regulatory, sc->hw->wiphy,
			      ath9k_reg_notifier);
	if (error)
		goto deinit;

	reg = &common->regulatory;

	/* Setup TX DMA */
	error = ath_tx_init(sc, ATH_TXBUF);
	if (error != 0)
		goto deinit;

	/* Setup RX DMA */
	error = ath_rx_init(sc, ATH_RXBUF);
	if (error != 0)
		goto deinit;

	ath9k_init_txpower_limits(sc);

#ifdef CONFIG_MAC80211_LEDS
	/* must be initialized before ieee80211_register_hw */
	sc->led_cdev.default_trigger = ieee80211_create_tpt_led_trigger(sc->hw,
		IEEE80211_TPT_LEDTRIG_FL_RADIO, ath9k_tpt_blink,
		ARRAY_SIZE(ath9k_tpt_blink));
#endif

	/* Register with mac80211 */
	error = ieee80211_register_hw(hw);
	if (error)
		goto rx_cleanup;

	error = ath9k_init_debug(ah);
	if (error) {
		ath_err(common, "Unable to create debugfs files\n");
		goto unregister;
	}

	/* Handle world regulatory */
	if (!ath_is_world_regd(reg)) {
		error = regulatory_hint(hw->wiphy, reg->alpha2);
		if (error)
			goto debug_cleanup;
	}

	ath_init_leds(sc);
	ath_start_rfkill_poll(sc);

	return 0;

debug_cleanup:
	ath9k_deinit_debug(sc);
unregister:
	ieee80211_unregister_hw(hw);
rx_cleanup:
	ath_rx_cleanup(sc);
deinit:
	ath9k_deinit_softc(sc);
	return error;
}