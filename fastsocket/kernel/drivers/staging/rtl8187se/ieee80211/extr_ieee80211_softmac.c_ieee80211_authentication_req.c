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
struct ieee80211_network {int /*<<< orphan*/  bssid; } ;
struct ieee80211_device {int /*<<< orphan*/  associate_seq; scalar_t__ open_wep; TYPE_1__* dev; } ;
struct TYPE_4__ {int duration_id; int /*<<< orphan*/  addr3; int /*<<< orphan*/  addr2; int /*<<< orphan*/  addr1; int /*<<< orphan*/  frame_ctl; } ;
struct ieee80211_authentication {void* status; void* transaction; int /*<<< orphan*/  algorithm; TYPE_2__ header; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_ALEN ; 
 int /*<<< orphan*/  IEEE80211_FCTL_WEP ; 
 int /*<<< orphan*/  IEEE80211_STYPE_AUTH ; 
 int /*<<< orphan*/  WLAN_AUTH_OPEN ; 
 int /*<<< orphan*/  WLAN_AUTH_SHARED_KEY ; 
 int /*<<< orphan*/  WLAN_STATUS_SUCCESS ; 
 void* cpu_to_le16 (int /*<<< orphan*/ ) ; 
 struct sk_buff* dev_alloc_skb (int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ skb_put (struct sk_buff*,int) ; 

inline struct sk_buff *ieee80211_authentication_req(struct ieee80211_network *beacon,
	struct ieee80211_device *ieee, int challengelen)
{
	struct sk_buff *skb;
	struct ieee80211_authentication *auth;

	skb = dev_alloc_skb(sizeof(struct ieee80211_authentication) + challengelen);

	if (!skb) return NULL;

	auth = (struct ieee80211_authentication *)
		skb_put(skb, sizeof(struct ieee80211_authentication));

	auth->header.frame_ctl = IEEE80211_STYPE_AUTH;
	if (challengelen) auth->header.frame_ctl |= IEEE80211_FCTL_WEP;

	auth->header.duration_id = 0x013a; //FIXME

	memcpy(auth->header.addr1, beacon->bssid, ETH_ALEN);
	memcpy(auth->header.addr2, ieee->dev->dev_addr, ETH_ALEN);
	memcpy(auth->header.addr3, beacon->bssid, ETH_ALEN);

	auth->algorithm = ieee->open_wep ? WLAN_AUTH_OPEN : WLAN_AUTH_SHARED_KEY;

	auth->transaction = cpu_to_le16(ieee->associate_seq);
	ieee->associate_seq++;

	auth->status = cpu_to_le16(WLAN_STATUS_SUCCESS);

	return skb;

}