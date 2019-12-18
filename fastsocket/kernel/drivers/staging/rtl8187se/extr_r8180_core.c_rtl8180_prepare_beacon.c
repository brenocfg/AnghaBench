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
typedef  int /*<<< orphan*/  u16 ;
struct sk_buff {int /*<<< orphan*/  len; int /*<<< orphan*/  data; } ;
struct r8180_priv {TYPE_2__* ieee80211; } ;
struct net_device {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  beacon_interval; } ;
struct TYPE_4__ {int /*<<< orphan*/  basic_rate; TYPE_1__ current_network; } ;

/* Variables and functions */
 int /*<<< orphan*/  BEACON_PRIORITY ; 
 int /*<<< orphan*/  BcnItv ; 
 int /*<<< orphan*/  BcnItv_BcnItv ; 
 int /*<<< orphan*/  cpu_to_le16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_kfree_skb_any (struct sk_buff*) ; 
 struct sk_buff* ieee80211_get_beacon (TYPE_2__*) ; 
 scalar_t__ ieee80211_priv (struct net_device*) ; 
 int /*<<< orphan*/  ieeerate2rtlrate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  read_nic_word (struct net_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtl8180_tx (struct net_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_nic_word (struct net_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void rtl8180_prepare_beacon(struct net_device *dev)
{
	struct r8180_priv *priv = (struct r8180_priv *)ieee80211_priv(dev);
	struct sk_buff *skb;

	u16 word  = read_nic_word(dev, BcnItv);
	word &= ~BcnItv_BcnItv; // clear Bcn_Itv
	word |= cpu_to_le16(priv->ieee80211->current_network.beacon_interval);//0x64;
	write_nic_word(dev, BcnItv, word);

	skb = ieee80211_get_beacon(priv->ieee80211);
	if(skb){
		rtl8180_tx(dev,skb->data,skb->len,BEACON_PRIORITY,
			0,0,ieeerate2rtlrate(priv->ieee80211->basic_rate));
		dev_kfree_skb_any(skb);
	}
}