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
typedef  scalar_t__ u8 ;
struct r8192_priv {scalar_t__ ChannelPlan; TYPE_1__* ieee80211; } ;
struct net_device {int dummy; } ;
struct TYPE_2__ {scalar_t__* channel_map; } ;

/* Variables and functions */
 int /*<<< orphan*/  COMP_INIT ; 
 scalar_t__ COUNTRY_CODE_GLOBAL_DOMAIN ; 
 int /*<<< orphan*/  DMESG (char*) ; 
 int /*<<< orphan*/  RT_TRACE (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int channels ; 
 struct r8192_priv* ieee80211_priv (struct net_device*) ; 
 int /*<<< orphan*/  printk (char*) ; 
 int /*<<< orphan*/  rtl819x_set_channel_map (scalar_t__,struct r8192_priv*) ; 

__attribute__((used)) static short rtl8192_get_channel_map(struct net_device * dev)
{
	struct r8192_priv *priv = ieee80211_priv(dev);
#ifdef ENABLE_DOT11D
	if(priv->ChannelPlan> COUNTRY_CODE_GLOBAL_DOMAIN){
		printk("rtl8180_init:Error channel plan! Set to default.\n");
		priv->ChannelPlan= 0;
	}
	RT_TRACE(COMP_INIT, "Channel plan is %d\n",priv->ChannelPlan);

	rtl819x_set_channel_map(priv->ChannelPlan, priv);
#else
	int ch,i;
	//Set Default Channel Plan
	if(!channels){
		DMESG("No channels, aborting");
		return -1;
	}
	ch=channels;
	priv->ChannelPlan= 0;//hikaru
	 // set channels 1..14 allowed in given locale
	for (i=1; i<=14; i++) {
		(priv->ieee80211->channel_map)[i] = (u8)(ch & 0x01);
		ch >>= 1;
	}
#endif
	return 0;
}