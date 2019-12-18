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
struct sk_buff {int dummy; } ;
struct TYPE_2__ {int rx_bytes; int /*<<< orphan*/  rx_packets; } ;
struct net_device {TYPE_1__ stats; } ;
struct hostap_80211_rx_status {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PRISM2_RX_MONITOR ; 
 int prism2_rx_80211 (struct net_device*,struct sk_buff*,struct hostap_80211_rx_status*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void monitor_rx(struct net_device *dev, struct sk_buff *skb,
		       struct hostap_80211_rx_status *rx_stats)
{
	int len;

	len = prism2_rx_80211(dev, skb, rx_stats, PRISM2_RX_MONITOR);
	dev->stats.rx_packets++;
	dev->stats.rx_bytes += len;
}