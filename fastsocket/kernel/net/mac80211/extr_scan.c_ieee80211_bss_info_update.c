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
struct ieee802_11_elems {int supp_rates_len; int ext_supp_rates_len; scalar_t__ parse_error; scalar_t__ wmm_info; scalar_t__ wmm_param; int /*<<< orphan*/  ext_supp_rates; int /*<<< orphan*/  supp_rates; int /*<<< orphan*/ * erp_info; } ;
struct ieee80211_rx_status {int signal; int /*<<< orphan*/  device_timestamp; } ;
struct ieee80211_mgmt {int /*<<< orphan*/  frame_control; } ;
struct TYPE_2__ {int flags; int max_signal; int /*<<< orphan*/  wiphy; } ;
struct ieee80211_local {TYPE_1__ hw; } ;
struct ieee80211_channel {int dummy; } ;
struct ieee80211_bss {int valid_data; int has_erp_value; int supp_rates_len; int wmm_used; int /*<<< orphan*/  uapsd_supported; scalar_t__ supp_rates; int /*<<< orphan*/  erp_value; int /*<<< orphan*/  corrupt_data; int /*<<< orphan*/  device_ts_presp; int /*<<< orphan*/  device_ts_beacon; } ;
struct cfg80211_bss {scalar_t__ priv; } ;
typedef  int s32 ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  IEEE80211_BSS_CORRUPT_BEACON ; 
 int /*<<< orphan*/  IEEE80211_BSS_CORRUPT_PROBE_RESP ; 
 int IEEE80211_BSS_VALID_ERP ; 
 int IEEE80211_BSS_VALID_RATES ; 
 int IEEE80211_BSS_VALID_WMM ; 
 int IEEE80211_HW_SIGNAL_DBM ; 
 int IEEE80211_HW_SIGNAL_UNSPEC ; 
 int IEEE80211_MAX_SUPP_RATES ; 
 struct cfg80211_bss* cfg80211_inform_bss_frame (int /*<<< orphan*/ ,struct ieee80211_channel*,struct ieee80211_mgmt*,size_t,int,int /*<<< orphan*/ ) ; 
 int ieee80211_is_beacon (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_uapsd_supported (struct ieee802_11_elems*) ; 
 int /*<<< orphan*/  memcpy (scalar_t__,int /*<<< orphan*/ ,int) ; 

struct ieee80211_bss *
ieee80211_bss_info_update(struct ieee80211_local *local,
			  struct ieee80211_rx_status *rx_status,
			  struct ieee80211_mgmt *mgmt, size_t len,
			  struct ieee802_11_elems *elems,
			  struct ieee80211_channel *channel)
{
	bool beacon = ieee80211_is_beacon(mgmt->frame_control);
	struct cfg80211_bss *cbss;
	struct ieee80211_bss *bss;
	int clen, srlen;
	s32 signal = 0;

	if (local->hw.flags & IEEE80211_HW_SIGNAL_DBM)
		signal = rx_status->signal * 100;
	else if (local->hw.flags & IEEE80211_HW_SIGNAL_UNSPEC)
		signal = (rx_status->signal * 100) / local->hw.max_signal;

	cbss = cfg80211_inform_bss_frame(local->hw.wiphy, channel,
					 mgmt, len, signal, GFP_ATOMIC);
	if (!cbss)
		return NULL;

	bss = (void *)cbss->priv;

	if (beacon)
		bss->device_ts_beacon = rx_status->device_timestamp;
	else
		bss->device_ts_presp = rx_status->device_timestamp;

	if (elems->parse_error) {
		if (beacon)
			bss->corrupt_data |= IEEE80211_BSS_CORRUPT_BEACON;
		else
			bss->corrupt_data |= IEEE80211_BSS_CORRUPT_PROBE_RESP;
	} else {
		if (beacon)
			bss->corrupt_data &= ~IEEE80211_BSS_CORRUPT_BEACON;
		else
			bss->corrupt_data &= ~IEEE80211_BSS_CORRUPT_PROBE_RESP;
	}

	/* save the ERP value so that it is available at association time */
	if (elems->erp_info && (!elems->parse_error ||
				!(bss->valid_data & IEEE80211_BSS_VALID_ERP))) {
		bss->erp_value = elems->erp_info[0];
		bss->has_erp_value = true;
		if (!elems->parse_error)
			bss->valid_data |= IEEE80211_BSS_VALID_ERP;
	}

	/* replace old supported rates if we get new values */
	if (!elems->parse_error ||
	    !(bss->valid_data & IEEE80211_BSS_VALID_RATES)) {
		srlen = 0;
		if (elems->supp_rates) {
			clen = IEEE80211_MAX_SUPP_RATES;
			if (clen > elems->supp_rates_len)
				clen = elems->supp_rates_len;
			memcpy(bss->supp_rates, elems->supp_rates, clen);
			srlen += clen;
		}
		if (elems->ext_supp_rates) {
			clen = IEEE80211_MAX_SUPP_RATES - srlen;
			if (clen > elems->ext_supp_rates_len)
				clen = elems->ext_supp_rates_len;
			memcpy(bss->supp_rates + srlen, elems->ext_supp_rates,
			       clen);
			srlen += clen;
		}
		if (srlen) {
			bss->supp_rates_len = srlen;
			if (!elems->parse_error)
				bss->valid_data |= IEEE80211_BSS_VALID_RATES;
		}
	}

	if (!elems->parse_error ||
	    !(bss->valid_data & IEEE80211_BSS_VALID_WMM)) {
		bss->wmm_used = elems->wmm_param || elems->wmm_info;
		bss->uapsd_supported = is_uapsd_supported(elems);
		if (!elems->parse_error)
			bss->valid_data |= IEEE80211_BSS_VALID_WMM;
	}

	return bss;
}