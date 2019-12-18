#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct sk_buff {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  addr3; int /*<<< orphan*/ * addr2; int /*<<< orphan*/  addr1; scalar_t__ duration_id; int /*<<< orphan*/  frame_ctl; } ;
struct ieee80211_probe_request {TYPE_2__ header; } ;
struct TYPE_6__ {unsigned int ssid_len; int /*<<< orphan*/  ssid; } ;
struct ieee80211_device {TYPE_3__ current_network; TYPE_1__* dev; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev_addr; } ;

/* Variables and functions */
 unsigned int ETH_ALEN ; 
 int /*<<< orphan*/  IEEE80211_STYPE_PROBE_REQ ; 
 int /*<<< orphan*/  MFIE_TYPE_SSID ; 
 int /*<<< orphan*/  cpu_to_le16 (int /*<<< orphan*/ ) ; 
 struct sk_buff* dev_alloc_skb (int) ; 
 int /*<<< orphan*/  ieee80211_MFIE_Brate (struct ieee80211_device*,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  ieee80211_MFIE_Grate (struct ieee80211_device*,int /*<<< orphan*/ **) ; 
 unsigned int ieee80211_MFIE_rate_len (struct ieee80211_device*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int,unsigned int) ; 
 scalar_t__ skb_put (struct sk_buff*,unsigned int) ; 

inline struct sk_buff *ieee80211_probe_req(struct ieee80211_device *ieee)
{
	unsigned int len,rate_len;
	u8 *tag;
	struct sk_buff *skb;
	struct ieee80211_probe_request *req;

	len = ieee->current_network.ssid_len;

	rate_len = ieee80211_MFIE_rate_len(ieee);

	skb = dev_alloc_skb(sizeof(struct ieee80211_probe_request) +
			    2 + len + rate_len);
	if (!skb)
		return NULL;

	req = (struct ieee80211_probe_request *) skb_put(skb,sizeof(struct ieee80211_probe_request));
	req->header.frame_ctl = cpu_to_le16(IEEE80211_STYPE_PROBE_REQ);
	req->header.duration_id = 0; //FIXME: is this OK ?

	memset(req->header.addr1, 0xff, ETH_ALEN);
	memcpy(req->header.addr2, ieee->dev->dev_addr, ETH_ALEN);
	memset(req->header.addr3, 0xff, ETH_ALEN);

	tag = (u8 *) skb_put(skb,len+2+rate_len);

	*tag++ = MFIE_TYPE_SSID;
	*tag++ = len;
	memcpy(tag, ieee->current_network.ssid, len);
	tag += len;
	ieee80211_MFIE_Brate(ieee,&tag);
	ieee80211_MFIE_Grate(ieee,&tag);

	return skb;
}