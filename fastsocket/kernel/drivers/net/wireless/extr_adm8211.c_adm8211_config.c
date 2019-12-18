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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_4__ {TYPE_1__* chan; } ;
struct ieee80211_conf {TYPE_2__ chandef; } ;
struct ieee80211_hw {struct ieee80211_conf conf; struct adm8211_priv* priv; } ;
struct adm8211_priv {int channel; } ;
struct TYPE_3__ {int /*<<< orphan*/  center_freq; } ;

/* Variables and functions */
 int /*<<< orphan*/  adm8211_rf_set_channel (struct ieee80211_hw*,int) ; 
 int ieee80211_frequency_to_channel (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int adm8211_config(struct ieee80211_hw *dev, u32 changed)
{
	struct adm8211_priv *priv = dev->priv;
	struct ieee80211_conf *conf = &dev->conf;
	int channel =
		ieee80211_frequency_to_channel(conf->chandef.chan->center_freq);

	if (channel != priv->channel) {
		priv->channel = channel;
		adm8211_rf_set_channel(dev, priv->channel);
	}

	return 0;
}