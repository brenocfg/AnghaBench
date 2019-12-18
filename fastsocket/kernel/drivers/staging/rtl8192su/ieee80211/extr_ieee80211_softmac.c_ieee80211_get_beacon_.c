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
typedef  int u8 ;
struct sk_buff {scalar_t__ data; } ;
struct TYPE_2__ {int /*<<< orphan*/  frame_ctl; } ;
struct ieee80211_probe_response {TYPE_1__ header; } ;
struct ieee80211_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IEEE80211_STYPE_BEACON ; 
 int /*<<< orphan*/  cpu_to_le16 (int /*<<< orphan*/ ) ; 
 struct sk_buff* ieee80211_probe_resp (struct ieee80211_device*,int*) ; 

struct sk_buff *ieee80211_get_beacon_(struct ieee80211_device *ieee)
{
	u8 broadcast_addr[] = {0xff,0xff,0xff,0xff,0xff,0xff};

	struct sk_buff *skb;
	struct ieee80211_probe_response *b;

	skb = ieee80211_probe_resp(ieee, broadcast_addr);

	if (!skb)
		return NULL;

	b = (struct ieee80211_probe_response *) skb->data;
	b->header.frame_ctl = cpu_to_le16(IEEE80211_STYPE_BEACON);

	return skb;

}