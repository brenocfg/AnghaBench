#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {int /*<<< orphan*/  debugfs_phy; } ;
struct TYPE_10__ {int /*<<< orphan*/ * txq_max_pending; } ;
struct ath_softc {TYPE_7__ debug; TYPE_5__* sc_ah; int /*<<< orphan*/  rfs_chan_spec_scan; TYPE_3__ tx; TYPE_2__* hw; } ;
struct TYPE_13__ {int /*<<< orphan*/  cwm_ignore_extcca; } ;
struct ath_hw {TYPE_6__ config; } ;
struct ath_common {scalar_t__ priv; } ;
struct TYPE_11__ {int /*<<< orphan*/  enable_paprd; } ;
struct TYPE_12__ {int /*<<< orphan*/  gpio_val; int /*<<< orphan*/  gpio_mask; TYPE_4__ config; } ;
struct TYPE_9__ {TYPE_1__* wiphy; } ;
struct TYPE_8__ {int /*<<< orphan*/  debugfsdir; } ;

/* Variables and functions */
 int ENOMEM ; 
 size_t IEEE80211_AC_BE ; 
 size_t IEEE80211_AC_BK ; 
 size_t IEEE80211_AC_VI ; 
 size_t IEEE80211_AC_VO ; 
 int S_IRUSR ; 
 int S_IWUSR ; 
 int /*<<< orphan*/  ath9k_dfs_init_debug (struct ath_softc*) ; 
 struct ath_common* ath9k_hw_common (struct ath_hw*) ; 
 int /*<<< orphan*/  debugfs_create_bool (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  debugfs_create_dir (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debugfs_create_file (char*,int,int /*<<< orphan*/ ,struct ath_softc*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  debugfs_create_u32 (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fops_ant_diversity ; 
 int /*<<< orphan*/  fops_base_eeprom ; 
 int /*<<< orphan*/  fops_btcoex ; 
 int /*<<< orphan*/  fops_debug ; 
 int /*<<< orphan*/  fops_disable_ani ; 
 int /*<<< orphan*/  fops_dma ; 
 int /*<<< orphan*/  fops_dump_nfcal ; 
 int /*<<< orphan*/  fops_interrupt ; 
 int /*<<< orphan*/  fops_misc ; 
 int /*<<< orphan*/  fops_modal_eeprom ; 
 int /*<<< orphan*/  fops_queues ; 
 int /*<<< orphan*/  fops_recv ; 
 int /*<<< orphan*/  fops_regdump ; 
 int /*<<< orphan*/  fops_regidx ; 
 int /*<<< orphan*/  fops_regval ; 
 int /*<<< orphan*/  fops_reset ; 
 int /*<<< orphan*/  fops_rx_chainmask ; 
 int /*<<< orphan*/  fops_samps ; 
 int /*<<< orphan*/  fops_spec_scan_ctl ; 
 int /*<<< orphan*/  fops_spectral_count ; 
 int /*<<< orphan*/  fops_spectral_fft_period ; 
 int /*<<< orphan*/  fops_spectral_period ; 
 int /*<<< orphan*/  fops_spectral_short_repeat ; 
 int /*<<< orphan*/  fops_tx_chainmask ; 
 int /*<<< orphan*/  fops_xmit ; 
 int /*<<< orphan*/  relay_open (char*,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rfs_spec_scan_cb ; 

int ath9k_init_debug(struct ath_hw *ah)
{
	struct ath_common *common = ath9k_hw_common(ah);
	struct ath_softc *sc = (struct ath_softc *) common->priv;

	sc->debug.debugfs_phy = debugfs_create_dir("ath9k",
						   sc->hw->wiphy->debugfsdir);
	if (!sc->debug.debugfs_phy)
		return -ENOMEM;

#ifdef CONFIG_ATH_DEBUG
	debugfs_create_file("debug", S_IRUSR | S_IWUSR, sc->debug.debugfs_phy,
			    sc, &fops_debug);
#endif

	ath9k_dfs_init_debug(sc);

	debugfs_create_file("dma", S_IRUSR, sc->debug.debugfs_phy, sc,
			    &fops_dma);
	debugfs_create_file("interrupt", S_IRUSR, sc->debug.debugfs_phy, sc,
			    &fops_interrupt);
	debugfs_create_file("xmit", S_IRUSR, sc->debug.debugfs_phy, sc,
			    &fops_xmit);
	debugfs_create_file("queues", S_IRUSR, sc->debug.debugfs_phy, sc,
			    &fops_queues);
	debugfs_create_u32("qlen_bk", S_IRUSR | S_IWUSR, sc->debug.debugfs_phy,
			   &sc->tx.txq_max_pending[IEEE80211_AC_BK]);
	debugfs_create_u32("qlen_be", S_IRUSR | S_IWUSR, sc->debug.debugfs_phy,
			   &sc->tx.txq_max_pending[IEEE80211_AC_BE]);
	debugfs_create_u32("qlen_vi", S_IRUSR | S_IWUSR, sc->debug.debugfs_phy,
			   &sc->tx.txq_max_pending[IEEE80211_AC_VI]);
	debugfs_create_u32("qlen_vo", S_IRUSR | S_IWUSR, sc->debug.debugfs_phy,
			   &sc->tx.txq_max_pending[IEEE80211_AC_VO]);
	debugfs_create_file("misc", S_IRUSR, sc->debug.debugfs_phy, sc,
			    &fops_misc);
	debugfs_create_file("reset", S_IRUSR, sc->debug.debugfs_phy, sc,
			    &fops_reset);
	debugfs_create_file("recv", S_IRUSR, sc->debug.debugfs_phy, sc,
			    &fops_recv);
	debugfs_create_file("rx_chainmask", S_IRUSR | S_IWUSR,
			    sc->debug.debugfs_phy, sc, &fops_rx_chainmask);
	debugfs_create_file("tx_chainmask", S_IRUSR | S_IWUSR,
			    sc->debug.debugfs_phy, sc, &fops_tx_chainmask);
	debugfs_create_file("disable_ani", S_IRUSR | S_IWUSR,
			    sc->debug.debugfs_phy, sc, &fops_disable_ani);
	debugfs_create_bool("paprd", S_IRUSR | S_IWUSR, sc->debug.debugfs_phy,
			    &sc->sc_ah->config.enable_paprd);
	debugfs_create_file("regidx", S_IRUSR | S_IWUSR, sc->debug.debugfs_phy,
			    sc, &fops_regidx);
	debugfs_create_file("regval", S_IRUSR | S_IWUSR, sc->debug.debugfs_phy,
			    sc, &fops_regval);
	debugfs_create_bool("ignore_extcca", S_IRUSR | S_IWUSR,
			    sc->debug.debugfs_phy,
			    &ah->config.cwm_ignore_extcca);
	debugfs_create_file("regdump", S_IRUSR, sc->debug.debugfs_phy, sc,
			    &fops_regdump);
	debugfs_create_file("dump_nfcal", S_IRUSR, sc->debug.debugfs_phy, sc,
			    &fops_dump_nfcal);
	debugfs_create_file("base_eeprom", S_IRUSR, sc->debug.debugfs_phy, sc,
			    &fops_base_eeprom);
	debugfs_create_file("modal_eeprom", S_IRUSR, sc->debug.debugfs_phy, sc,
			    &fops_modal_eeprom);
	sc->rfs_chan_spec_scan = relay_open("spectral_scan",
					    sc->debug.debugfs_phy,
					    1024, 256, &rfs_spec_scan_cb,
					    NULL);
	debugfs_create_file("spectral_scan_ctl", S_IRUSR | S_IWUSR,
			    sc->debug.debugfs_phy, sc,
			    &fops_spec_scan_ctl);
	debugfs_create_file("spectral_short_repeat", S_IRUSR | S_IWUSR,
			    sc->debug.debugfs_phy, sc,
			    &fops_spectral_short_repeat);
	debugfs_create_file("spectral_count", S_IRUSR | S_IWUSR,
			    sc->debug.debugfs_phy, sc, &fops_spectral_count);
	debugfs_create_file("spectral_period", S_IRUSR | S_IWUSR,
			    sc->debug.debugfs_phy, sc, &fops_spectral_period);
	debugfs_create_file("spectral_fft_period", S_IRUSR | S_IWUSR,
			    sc->debug.debugfs_phy, sc,
			    &fops_spectral_fft_period);

#ifdef CONFIG_ATH9K_MAC_DEBUG
	debugfs_create_file("samples", S_IRUSR, sc->debug.debugfs_phy, sc,
			    &fops_samps);
#endif
	debugfs_create_u32("gpio_mask", S_IRUSR | S_IWUSR,
			   sc->debug.debugfs_phy, &sc->sc_ah->gpio_mask);
	debugfs_create_u32("gpio_val", S_IRUSR | S_IWUSR,
			   sc->debug.debugfs_phy, &sc->sc_ah->gpio_val);
	debugfs_create_file("diversity", S_IRUSR | S_IWUSR,
			    sc->debug.debugfs_phy, sc, &fops_ant_diversity);
#ifdef CONFIG_ATH9K_BTCOEX_SUPPORT
	debugfs_create_file("btcoex", S_IRUSR, sc->debug.debugfs_phy, sc,
			    &fops_btcoex);
#endif
	return 0;
}