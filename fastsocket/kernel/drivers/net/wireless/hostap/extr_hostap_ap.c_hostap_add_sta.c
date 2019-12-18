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
typedef  int /*<<< orphan*/  u8 ;
struct sta_info {int flags; int ap; int* supported_rates; int tx_supp_rates; int tx_rate; int tx_max_rate; int tx_rate_idx; } ;
struct ap_data {int /*<<< orphan*/  sta_table_lock; } ;

/* Variables and functions */
 int WLAN_RATE_11M ; 
 int WLAN_RATE_1M ; 
 int WLAN_RATE_2M ; 
 int WLAN_RATE_5M5 ; 
 int WLAN_STA_ASSOC ; 
 int WLAN_STA_AUTH ; 
 struct sta_info* ap_add_sta (struct ap_data*,int /*<<< orphan*/ *) ; 
 struct sta_info* ap_get_sta (struct ap_data*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

int hostap_add_sta(struct ap_data *ap, u8 *sta_addr)
{
	struct sta_info *sta;
	int ret = 1;

	if (!ap)
		return -1;

	spin_lock(&ap->sta_table_lock);
	sta = ap_get_sta(ap, sta_addr);
	if (sta)
		ret = 0;
	spin_unlock(&ap->sta_table_lock);

	if (ret == 1) {
		sta = ap_add_sta(ap, sta_addr);
		if (!sta)
			return -1;
		sta->flags = WLAN_STA_AUTH | WLAN_STA_ASSOC;
		sta->ap = 1;
		memset(sta->supported_rates, 0, sizeof(sta->supported_rates));
		/* No way of knowing which rates are supported since we did not
		 * get supported rates element from beacon/assoc req. Assume
		 * that remote end supports all 802.11b rates. */
		sta->supported_rates[0] = 0x82;
		sta->supported_rates[1] = 0x84;
		sta->supported_rates[2] = 0x0b;
		sta->supported_rates[3] = 0x16;
		sta->tx_supp_rates = WLAN_RATE_1M | WLAN_RATE_2M |
			WLAN_RATE_5M5 | WLAN_RATE_11M;
		sta->tx_rate = 110;
		sta->tx_max_rate = sta->tx_rate_idx = 3;
	}

	return ret;
}