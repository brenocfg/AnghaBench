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
typedef  size_t u8 ;
struct wl1271 {size_t hw_tx_rate_tbl_size; size_t** band_rate_to_idx; } ;
typedef  enum ieee80211_band { ____Placeholder_ieee80211_band } ieee80211_band ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 size_t CONF_HW_RXTX_RATE_UNSUPPORTED ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  wl1271_error (char*,size_t) ; 

u8 wlcore_rate_to_idx(struct wl1271 *wl, u8 rate, enum ieee80211_band band)
{
	u8 idx;

	BUG_ON(band >= 2);

	if (unlikely(rate >= wl->hw_tx_rate_tbl_size)) {
		wl1271_error("Illegal RX rate from HW: %d", rate);
		return 0;
	}

	idx = wl->band_rate_to_idx[band][rate];
	if (unlikely(idx == CONF_HW_RXTX_RATE_UNSUPPORTED)) {
		wl1271_error("Unsupported RX rate from HW: %d", rate);
		return 0;
	}

	return idx;
}