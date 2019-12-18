#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_9__ {int /*<<< orphan*/ * txq; } ;
struct TYPE_8__ {int /*<<< orphan*/  samp_lock; } ;
struct ath_softc {TYPE_4__ tx; struct ath_hw* sc_ah; int /*<<< orphan*/  rx_poll_timer; int /*<<< orphan*/  hw_pll_work; int /*<<< orphan*/  paprd_work; int /*<<< orphan*/  hw_check_work; int /*<<< orphan*/  hw_reset_work; int /*<<< orphan*/  bcon_tasklet; int /*<<< orphan*/  intr_tq; TYPE_3__ debug; int /*<<< orphan*/  mutex; int /*<<< orphan*/  sc_pm_lock; int /*<<< orphan*/  sc_serial_rw; int /*<<< orphan*/  hw; int /*<<< orphan*/  dfs_detector; TYPE_5__* dev; } ;
struct TYPE_7__ {int /*<<< orphan*/  rmw; int /*<<< orphan*/  write; int /*<<< orphan*/  read; } ;
struct TYPE_6__ {int /*<<< orphan*/  devid; } ;
struct ath_hw {int led_pin; TYPE_2__ reg_ops; int /*<<< orphan*/  external_reset; int /*<<< orphan*/  get_mac_revision; int /*<<< orphan*/  is_clk_25mhz; int /*<<< orphan*/  gpio_val; int /*<<< orphan*/  gpio_mask; int /*<<< orphan*/  ah_flags; int /*<<< orphan*/  intr_ref_cnt; TYPE_1__ hw_version; int /*<<< orphan*/  hw; TYPE_5__* dev; } ;
struct ath_common {int btcoex_enabled; int disable_ani; int antenna_diversity; int cachelsz; struct ath_bus_ops const* bus_ops; int /*<<< orphan*/  macaddr; int /*<<< orphan*/  cc_lock; int /*<<< orphan*/  debug_mask; struct ath_softc* priv; int /*<<< orphan*/  hw; struct ath_hw* ah; TYPE_2__* ops; } ;
struct ath_bus_ops {int /*<<< orphan*/  (* aspm_init ) (struct ath_common*) ;} ;
struct ath9k_platform_data {int led_pin; scalar_t__ macaddr; scalar_t__ eeprom_name; int /*<<< orphan*/  external_reset; int /*<<< orphan*/  get_mac_revision; int /*<<< orphan*/  is_clk_25mhz; int /*<<< orphan*/  gpio_val; int /*<<< orphan*/  gpio_mask; } ;
struct TYPE_10__ {struct ath9k_platform_data* platform_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  AH_USE_EEPROM ; 
 int ATH9K_NUM_TX_QUEUES ; 
 scalar_t__ ATH_TXQ_SETUP (struct ath_softc*,int) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  ETH_ALEN ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NL80211_DFS_UNSET ; 
 int /*<<< orphan*/  ath9k_beacon_tasklet ; 
 int ath9k_btcoex_enable ; 
 int /*<<< orphan*/  ath9k_cmn_init_crypto (struct ath_hw*) ; 
 int /*<<< orphan*/  ath9k_debug ; 
 int /*<<< orphan*/  ath9k_eeprom_release (struct ath_softc*) ; 
 int ath9k_eeprom_request (struct ath_softc*,scalar_t__) ; 
 scalar_t__ ath9k_enable_diversity ; 
 struct ath_common* ath9k_hw_common (struct ath_hw*) ; 
 int /*<<< orphan*/  ath9k_hw_deinit (struct ath_hw*) ; 
 int ath9k_hw_init (struct ath_hw*) ; 
 int ath9k_init_btcoex (struct ath_softc*) ; 
 int ath9k_init_channels_rates (struct ath_softc*) ; 
 int /*<<< orphan*/  ath9k_init_misc (struct ath_softc*) ; 
 int ath9k_init_queues (struct ath_softc*) ; 
 int /*<<< orphan*/  ath9k_ioread32 ; 
 int /*<<< orphan*/  ath9k_iowrite32 ; 
 int /*<<< orphan*/  ath9k_reg_rmw ; 
 int /*<<< orphan*/  ath9k_tasklet ; 
 int /*<<< orphan*/  ath_fill_led_pin (struct ath_softc*) ; 
 int /*<<< orphan*/  ath_hw_check ; 
 int /*<<< orphan*/  ath_hw_pll_work ; 
 int /*<<< orphan*/  ath_paprd_calibrate ; 
 int /*<<< orphan*/  ath_read_cachesize (struct ath_common*,int*) ; 
 int /*<<< orphan*/  ath_reset_work ; 
 int /*<<< orphan*/  ath_rx_poll ; 
 int /*<<< orphan*/  ath_tx_cleanupq (struct ath_softc*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 struct ath_hw* devm_kzalloc (TYPE_5__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dfs_pattern_detector_init (struct ath_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  setup_timer (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct ath_common*) ; 
 int /*<<< orphan*/  tasklet_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned long) ; 

__attribute__((used)) static int ath9k_init_softc(u16 devid, struct ath_softc *sc,
			    const struct ath_bus_ops *bus_ops)
{
	struct ath9k_platform_data *pdata = sc->dev->platform_data;
	struct ath_hw *ah = NULL;
	struct ath_common *common;
	int ret = 0, i;
	int csz = 0;

	ah = devm_kzalloc(sc->dev, sizeof(struct ath_hw), GFP_KERNEL);
	if (!ah)
		return -ENOMEM;

	ah->dev = sc->dev;
	ah->hw = sc->hw;
	ah->hw_version.devid = devid;
	ah->reg_ops.read = ath9k_ioread32;
	ah->reg_ops.write = ath9k_iowrite32;
	ah->reg_ops.rmw = ath9k_reg_rmw;
	atomic_set(&ah->intr_ref_cnt, -1);
	sc->sc_ah = ah;

	sc->dfs_detector = dfs_pattern_detector_init(ah, NL80211_DFS_UNSET);

	if (!pdata) {
		ah->ah_flags |= AH_USE_EEPROM;
		sc->sc_ah->led_pin = -1;
	} else {
		sc->sc_ah->gpio_mask = pdata->gpio_mask;
		sc->sc_ah->gpio_val = pdata->gpio_val;
		sc->sc_ah->led_pin = pdata->led_pin;
		ah->is_clk_25mhz = pdata->is_clk_25mhz;
		ah->get_mac_revision = pdata->get_mac_revision;
		ah->external_reset = pdata->external_reset;
	}

	common = ath9k_hw_common(ah);
	common->ops = &ah->reg_ops;
	common->bus_ops = bus_ops;
	common->ah = ah;
	common->hw = sc->hw;
	common->priv = sc;
	common->debug_mask = ath9k_debug;
	common->btcoex_enabled = ath9k_btcoex_enable == 1;
	common->disable_ani = false;

	/*
	 * Enable Antenna diversity only when BTCOEX is disabled
	 * and the user manually requests the feature.
	 */
	if (!common->btcoex_enabled && ath9k_enable_diversity)
		common->antenna_diversity = 1;

	spin_lock_init(&common->cc_lock);

	spin_lock_init(&sc->sc_serial_rw);
	spin_lock_init(&sc->sc_pm_lock);
	mutex_init(&sc->mutex);
#ifdef CONFIG_ATH9K_MAC_DEBUG
	spin_lock_init(&sc->debug.samp_lock);
#endif
	tasklet_init(&sc->intr_tq, ath9k_tasklet, (unsigned long)sc);
	tasklet_init(&sc->bcon_tasklet, ath9k_beacon_tasklet,
		     (unsigned long)sc);

	INIT_WORK(&sc->hw_reset_work, ath_reset_work);
	INIT_WORK(&sc->hw_check_work, ath_hw_check);
	INIT_WORK(&sc->paprd_work, ath_paprd_calibrate);
	INIT_DELAYED_WORK(&sc->hw_pll_work, ath_hw_pll_work);
	setup_timer(&sc->rx_poll_timer, ath_rx_poll, (unsigned long)sc);

	/*
	 * Cache line size is used to size and align various
	 * structures used to communicate with the hardware.
	 */
	ath_read_cachesize(common, &csz);
	common->cachelsz = csz << 2; /* convert to bytes */

	if (pdata && pdata->eeprom_name) {
		ret = ath9k_eeprom_request(sc, pdata->eeprom_name);
		if (ret)
			return ret;
	}

	/* Initializes the hardware for all supported chipsets */
	ret = ath9k_hw_init(ah);
	if (ret)
		goto err_hw;

	if (pdata && pdata->macaddr)
		memcpy(common->macaddr, pdata->macaddr, ETH_ALEN);

	ret = ath9k_init_queues(sc);
	if (ret)
		goto err_queues;

	ret =  ath9k_init_btcoex(sc);
	if (ret)
		goto err_btcoex;

	ret = ath9k_init_channels_rates(sc);
	if (ret)
		goto err_btcoex;

	ath9k_cmn_init_crypto(sc->sc_ah);
	ath9k_init_misc(sc);
	ath_fill_led_pin(sc);

	if (common->bus_ops->aspm_init)
		common->bus_ops->aspm_init(common);

	return 0;

err_btcoex:
	for (i = 0; i < ATH9K_NUM_TX_QUEUES; i++)
		if (ATH_TXQ_SETUP(sc, i))
			ath_tx_cleanupq(sc, &sc->tx.txq[i]);
err_queues:
	ath9k_hw_deinit(ah);
err_hw:
	ath9k_eeprom_release(sc);
	return ret;
}