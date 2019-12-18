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
struct ieee80211_rx_status {int flag; int vendor_radiotap_align; scalar_t__ vendor_radiotap_len; } ;
struct ieee80211_radiotap_header {int dummy; } ;
struct TYPE_2__ {int flags; } ;
struct ieee80211_local {TYPE_1__ hw; } ;

/* Variables and functions */
 int ALIGN (int,int) ; 
 int IEEE80211_HW_SIGNAL_DBM ; 
 int RX_FLAG_AMPDU_DETAILS ; 
 int RX_FLAG_HT ; 
 int RX_FLAG_VHT ; 
 scalar_t__ WARN_ON_ONCE (int) ; 
 scalar_t__ ieee80211_have_rx_timestamp (struct ieee80211_rx_status*) ; 

__attribute__((used)) static int
ieee80211_rx_radiotap_space(struct ieee80211_local *local,
			    struct ieee80211_rx_status *status)
{
	int len;

	/* always present fields */
	len = sizeof(struct ieee80211_radiotap_header) + 9;

	/* allocate extra bitmap */
	if (status->vendor_radiotap_len)
		len += 4;

	if (ieee80211_have_rx_timestamp(status)) {
		len = ALIGN(len, 8);
		len += 8;
	}
	if (local->hw.flags & IEEE80211_HW_SIGNAL_DBM)
		len += 1;

	/* padding for RX_FLAGS if necessary */
	len = ALIGN(len, 2);

	if (status->flag & RX_FLAG_HT) /* HT info */
		len += 3;

	if (status->flag & RX_FLAG_AMPDU_DETAILS) {
		len = ALIGN(len, 4);
		len += 8;
	}

	if (status->flag & RX_FLAG_VHT) {
		len = ALIGN(len, 2);
		len += 12;
	}

	if (status->vendor_radiotap_len) {
		if (WARN_ON_ONCE(status->vendor_radiotap_align == 0))
			status->vendor_radiotap_align = 1;
		/* align standard part of vendor namespace */
		len = ALIGN(len, 2);
		/* allocate standard part of vendor namespace */
		len += 6;
		/* align vendor-defined part */
		len = ALIGN(len, status->vendor_radiotap_align);
		/* vendor-defined part is already in skb */
	}

	return len;
}