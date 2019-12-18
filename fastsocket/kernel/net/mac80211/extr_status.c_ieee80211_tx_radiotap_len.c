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
struct TYPE_4__ {TYPE_1__* rates; } ;
struct ieee80211_tx_info {TYPE_2__ status; } ;
struct ieee80211_radiotap_header {int dummy; } ;
struct TYPE_3__ {scalar_t__ idx; int flags; } ;

/* Variables and functions */
 int IEEE80211_TX_RC_MCS ; 

__attribute__((used)) static int ieee80211_tx_radiotap_len(struct ieee80211_tx_info *info)
{
	int len = sizeof(struct ieee80211_radiotap_header);

	/* IEEE80211_RADIOTAP_RATE rate */
	if (info->status.rates[0].idx >= 0 &&
	    !(info->status.rates[0].flags & IEEE80211_TX_RC_MCS))
		len += 2;

	/* IEEE80211_RADIOTAP_TX_FLAGS */
	len += 2;

	/* IEEE80211_RADIOTAP_DATA_RETRIES */
	len += 1;

	/* IEEE80211_TX_RC_MCS */
	if (info->status.rates[0].idx >= 0 &&
	    info->status.rates[0].flags & IEEE80211_TX_RC_MCS)
		len += 3;

	return len;
}