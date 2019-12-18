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
struct sk_buff {int dummy; } ;
struct ieee80211_hdr_3addr {int /*<<< orphan*/  frame_ctl; int /*<<< orphan*/  addr3; int /*<<< orphan*/  addr2; int /*<<< orphan*/  addr1; } ;
struct TYPE_4__ {int /*<<< orphan*/  bssid; } ;
struct ieee80211_device {TYPE_2__ current_network; TYPE_1__* dev; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_ALEN ; 
 int IEEE80211_FCTL_PM ; 
 int IEEE80211_FCTL_TODS ; 
 int IEEE80211_FTYPE_DATA ; 
 int IEEE80211_STYPE_NULLFUNC ; 
 int /*<<< orphan*/  cpu_to_le16 (int) ; 
 struct sk_buff* dev_alloc_skb (int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ skb_put (struct sk_buff*,int) ; 

struct sk_buff* ieee80211_null_func(struct ieee80211_device *ieee,short pwr)
{
	struct sk_buff *skb;
	struct ieee80211_hdr_3addr* hdr;

	skb = dev_alloc_skb(sizeof(struct ieee80211_hdr_3addr));

	if (!skb)
		return NULL;

	hdr = (struct ieee80211_hdr_3addr*)skb_put(skb,sizeof(struct ieee80211_hdr_3addr));

	memcpy(hdr->addr1, ieee->current_network.bssid, ETH_ALEN);
	memcpy(hdr->addr2, ieee->dev->dev_addr, ETH_ALEN);
	memcpy(hdr->addr3, ieee->current_network.bssid, ETH_ALEN);

	hdr->frame_ctl = cpu_to_le16(IEEE80211_FTYPE_DATA |
		IEEE80211_STYPE_NULLFUNC | IEEE80211_FCTL_TODS |
		(pwr ? IEEE80211_FCTL_PM:0));

	return skb;


}