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
struct wl1251 {scalar_t__ use_eeprom; TYPE_2__* hw; } ;
struct tx_double_buffer_desc {int dummy; } ;
struct TYPE_4__ {int channel_change_time; int flags; int queues; TYPE_1__* wiphy; scalar_t__ extra_tx_headroom; } ;
struct TYPE_3__ {int interface_modes; int max_scan_ssids; int /*<<< orphan*/ ** bands; } ;

/* Variables and functions */
 int BIT (int /*<<< orphan*/ ) ; 
 size_t IEEE80211_BAND_2GHZ ; 
 int IEEE80211_HW_SIGNAL_DBM ; 
 int IEEE80211_HW_SUPPORTS_PS ; 
 int IEEE80211_HW_SUPPORTS_UAPSD ; 
 int /*<<< orphan*/  NL80211_IFTYPE_ADHOC ; 
 int /*<<< orphan*/  NL80211_IFTYPE_STATION ; 
 scalar_t__ WL1251_TKIP_IV_SPACE ; 
 int /*<<< orphan*/  wl1251_band_2ghz ; 
 int /*<<< orphan*/  wl1251_debugfs_init (struct wl1251*) ; 
 int /*<<< orphan*/  wl1251_notice (char*) ; 
 int /*<<< orphan*/  wl1251_read_eeprom_mac (struct wl1251*) ; 
 int wl1251_register_hw (struct wl1251*) ; 

int wl1251_init_ieee80211(struct wl1251 *wl)
{
	int ret;

	/* The tx descriptor buffer and the TKIP space */
	wl->hw->extra_tx_headroom = sizeof(struct tx_double_buffer_desc)
		+ WL1251_TKIP_IV_SPACE;

	/* unit us */
	/* FIXME: find a proper value */
	wl->hw->channel_change_time = 10000;

	wl->hw->flags = IEEE80211_HW_SIGNAL_DBM |
		IEEE80211_HW_SUPPORTS_PS |
		IEEE80211_HW_SUPPORTS_UAPSD;

	wl->hw->wiphy->interface_modes = BIT(NL80211_IFTYPE_STATION) |
					 BIT(NL80211_IFTYPE_ADHOC);
	wl->hw->wiphy->max_scan_ssids = 1;
	wl->hw->wiphy->bands[IEEE80211_BAND_2GHZ] = &wl1251_band_2ghz;

	wl->hw->queues = 4;

	if (wl->use_eeprom)
		wl1251_read_eeprom_mac(wl);

	ret = wl1251_register_hw(wl);
	if (ret)
		goto out;

	wl1251_debugfs_init(wl);
	wl1251_notice("initialized");

	ret = 0;

out:
	return ret;
}