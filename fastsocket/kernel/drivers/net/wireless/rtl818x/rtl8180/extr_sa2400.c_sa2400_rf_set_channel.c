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
typedef  int u32 ;
struct rtl8180_priv {TYPE_3__* channels; } ;
struct ieee80211_hw {struct rtl8180_priv* priv; } ;
struct TYPE_5__ {TYPE_1__* chan; } ;
struct ieee80211_conf {TYPE_2__ chandef; } ;
struct TYPE_6__ {int hw_value; } ;
struct TYPE_4__ {int /*<<< orphan*/  center_freq; } ;

/* Variables and functions */
 int ieee80211_frequency_to_channel (int /*<<< orphan*/ ) ; 
 int* sa2400_chan ; 
 int /*<<< orphan*/  sa2400_write_phy_antenna (struct ieee80211_hw*,int) ; 
 int /*<<< orphan*/  write_sa2400 (struct ieee80211_hw*,int,int) ; 

__attribute__((used)) static void sa2400_rf_set_channel(struct ieee80211_hw *dev,
				  struct ieee80211_conf *conf)
{
	struct rtl8180_priv *priv = dev->priv;
	int channel =
		ieee80211_frequency_to_channel(conf->chandef.chan->center_freq);
	u32 txpw = priv->channels[channel - 1].hw_value & 0xFF;
	u32 chan = sa2400_chan[channel - 1];

	write_sa2400(dev, 7, txpw);

	sa2400_write_phy_antenna(dev, channel);

	write_sa2400(dev, 0, chan);
	write_sa2400(dev, 1, 0xbb50);
	write_sa2400(dev, 2, 0x80);
	write_sa2400(dev, 3, 0);
}