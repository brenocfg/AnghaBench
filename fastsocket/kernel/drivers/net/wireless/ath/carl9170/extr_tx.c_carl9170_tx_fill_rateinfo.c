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
struct ar9170 {int dummy; } ;
struct TYPE_3__ {int idx; unsigned int count; } ;

/* Variables and functions */
 unsigned int IEEE80211_TX_MAX_RATES ; 

__attribute__((used)) static void carl9170_tx_fill_rateinfo(struct ar9170 *ar, unsigned int rix,
	unsigned int tries, struct ieee80211_tx_info *txinfo)
{
	unsigned int i;

	for (i = 0; i < IEEE80211_TX_MAX_RATES; i++) {
		if (txinfo->status.rates[i].idx < 0)
			break;

		if (i == rix) {
			txinfo->status.rates[i].count = tries;
			i++;
			break;
		}
	}

	for (; i < IEEE80211_TX_MAX_RATES; i++) {
		txinfo->status.rates[i].idx = -1;
		txinfo->status.rates[i].count = 0;
	}
}