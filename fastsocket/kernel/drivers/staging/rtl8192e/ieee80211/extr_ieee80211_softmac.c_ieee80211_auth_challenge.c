#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct sk_buff {int dummy; } ;
struct ieee80211_network {int dummy; } ;
struct ieee80211_hdr_3addr {int dummy; } ;
struct TYPE_5__ {scalar_t__ expires; } ;
struct TYPE_4__ {int /*<<< orphan*/  tx_auth_rq; } ;
struct ieee80211_device {TYPE_2__ associate_timer; TYPE_1__ softmac_stats; int /*<<< orphan*/  associate_seq; struct ieee80211_network current_network; } ;

/* Variables and functions */
 int HZ ; 
 int /*<<< orphan*/  IEEE80211_DEBUG_MGMT (char*) ; 
 int /*<<< orphan*/  MFIE_TYPE_CHALLENGE ; 
 int /*<<< orphan*/  add_timer (TYPE_2__*) ; 
 int /*<<< orphan*/  ieee80211_associate_abort (struct ieee80211_device*) ; 
 struct sk_buff* ieee80211_authentication_req (struct ieee80211_network*,struct ieee80211_device*,int) ; 
 int /*<<< orphan*/  ieee80211_encrypt_fragment (struct ieee80211_device*,struct sk_buff*,int) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mod_timer (TYPE_2__*,scalar_t__) ; 
 int /*<<< orphan*/ * skb_put (struct sk_buff*,int) ; 
 int /*<<< orphan*/  softmac_mgmt_xmit (struct sk_buff*,struct ieee80211_device*) ; 

void ieee80211_auth_challenge(struct ieee80211_device *ieee, u8 *challenge, int chlen)
{
	u8 *c;
	struct sk_buff *skb;
	struct ieee80211_network *beacon = &ieee->current_network;
//	int hlen = sizeof(struct ieee80211_authentication);

	ieee->associate_seq++;
	ieee->softmac_stats.tx_auth_rq++;

	skb = ieee80211_authentication_req(beacon, ieee, chlen+2);
	if (!skb)
		ieee80211_associate_abort(ieee);
	else{
		c = skb_put(skb, chlen+2);
		*(c++) = MFIE_TYPE_CHALLENGE;
		*(c++) = chlen;
		memcpy(c, challenge, chlen);

		IEEE80211_DEBUG_MGMT("Sending authentication challenge response\n");

		ieee80211_encrypt_fragment(ieee, skb, sizeof(struct ieee80211_hdr_3addr  ));

		softmac_mgmt_xmit(skb, ieee);
		mod_timer(&ieee->associate_timer, jiffies + (HZ/2));
#if 0
		ieee->associate_timer.expires = jiffies + (HZ / 2);
		add_timer(&ieee->associate_timer);
#endif
		//dev_kfree_skb_any(skb);//edit by thomas
	}
	kfree(challenge);
}