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
 int* max2820_chan ; 
 int /*<<< orphan*/  max2820_write_phy_antenna (struct ieee80211_hw*,int) ; 
 int /*<<< orphan*/  rtl8180_write_phy (struct ieee80211_hw*,int,int) ; 
 int /*<<< orphan*/  write_max2820 (struct ieee80211_hw*,int,int) ; 

__attribute__((used)) static void max2820_rf_set_channel(struct ieee80211_hw *dev,
				   struct ieee80211_conf *conf)
{
	struct rtl8180_priv *priv = dev->priv;
	int channel = conf ?
		ieee80211_frequency_to_channel(conf->chandef.chan->center_freq) : 1;
	unsigned int chan_idx = channel - 1;
	u32 txpw = priv->channels[chan_idx].hw_value & 0xFF;
	u32 chan = max2820_chan[chan_idx];

	/* While philips SA2400 drive the PA bias from
	 * sa2400, for MAXIM we do this directly from BB */
	rtl8180_write_phy(dev, 3, txpw);

	max2820_write_phy_antenna(dev, channel);
	write_max2820(dev, 3, chan);
}