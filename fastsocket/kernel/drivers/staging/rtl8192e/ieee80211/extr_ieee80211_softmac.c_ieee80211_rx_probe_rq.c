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
typedef  int /*<<< orphan*/  u8 ;
struct sk_buff {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  tx_probe_rs; int /*<<< orphan*/  rx_probe_rq; } ;
struct ieee80211_device {TYPE_1__ softmac_stats; } ;

/* Variables and functions */
 int ETH_ALEN ; 
 int /*<<< orphan*/  ieee80211_resp_to_probe (struct ieee80211_device*,int /*<<< orphan*/ *) ; 
 scalar_t__ probe_rq_parse (struct ieee80211_device*,struct sk_buff*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void
ieee80211_rx_probe_rq(struct ieee80211_device *ieee, struct sk_buff *skb)
{
	u8 dest[ETH_ALEN];

	//IEEE80211DMESG("Rx probe");
	ieee->softmac_stats.rx_probe_rq++;
	//DMESG("Dest is "MACSTR, MAC2STR(dest));
	if (probe_rq_parse(ieee, skb, dest)){
		//IEEE80211DMESG("Was for me!");
		ieee->softmac_stats.tx_probe_rs++;
		ieee80211_resp_to_probe(ieee, dest);
	}
}