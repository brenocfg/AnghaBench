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
struct r8192_priv {int CurrentChannelBW; int Record_CCK_20Mindex; int CCK_index; int Record_CCK_40Mindex; scalar_t__ bcck_in_ch14; TYPE_2__* ieee80211; } ;
struct net_device {int dummy; } ;
struct TYPE_3__ {int channel; } ;
struct TYPE_4__ {TYPE_1__ current_network; } ;

/* Variables and functions */
 int /*<<< orphan*/  COMP_POWER_TRACKING ; 
 scalar_t__ FALSE ; 
#define  HT_CHANNEL_WIDTH_20 129 
#define  HT_CHANNEL_WIDTH_20_40 128 
 int /*<<< orphan*/  RT_TRACE (int /*<<< orphan*/ ,char*,int) ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  dm_cck_txpower_adjust (struct net_device*,scalar_t__) ; 
 struct r8192_priv* ieee80211_priv (struct net_device*) ; 

__attribute__((used)) static void CCK_Tx_Power_Track_BW_Switch_ThermalMeter(struct net_device *dev)
{
	struct r8192_priv *priv = ieee80211_priv(dev);

	if(priv->ieee80211->current_network.channel == 14 && !priv->bcck_in_ch14)
		priv->bcck_in_ch14 = TRUE;
	else if(priv->ieee80211->current_network.channel != 14 && priv->bcck_in_ch14)
		priv->bcck_in_ch14 = FALSE;

	//write to default index and tx power track will be done in dm.
	switch(priv->CurrentChannelBW)
	{
		/* 20 MHz channel*/
		case HT_CHANNEL_WIDTH_20:
			if(priv->Record_CCK_20Mindex == 0)
				priv->Record_CCK_20Mindex = 6;	//set default value.
			priv->CCK_index = priv->Record_CCK_20Mindex;//6;
			RT_TRACE(COMP_POWER_TRACKING, "20MHz, CCK_Tx_Power_Track_BW_Switch_ThermalMeter(),CCK_index = %d\n", priv->CCK_index);
		break;

		/* 40 MHz channel*/
		case HT_CHANNEL_WIDTH_20_40:
			priv->CCK_index = priv->Record_CCK_40Mindex;//0;
			RT_TRACE(COMP_POWER_TRACKING, "40MHz, CCK_Tx_Power_Track_BW_Switch_ThermalMeter(), CCK_index = %d\n", priv->CCK_index);
		break;
	}
	dm_cck_txpower_adjust(dev, priv->bcck_in_ch14);
}