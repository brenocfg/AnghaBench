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
struct r8192_priv {int bDynamicTxHighPower; int bDynamicTxLowPower; unsigned int undecorated_smoothed_pwdb; int bLastDTPFlag_High; int bLastDTPFlag_Low; TYPE_2__* ieee80211; } ;
struct net_device {int dummy; } ;
struct TYPE_3__ {unsigned int channel; scalar_t__ atheros_cap_exist; } ;
struct TYPE_4__ {int bdynamic_txpower_enable; scalar_t__ mode; scalar_t__ state; TYPE_1__ current_network; } ;

/* Variables and functions */
 int /*<<< orphan*/  COMP_TXAGC ; 
 scalar_t__ IEEE80211_LINKED ; 
 scalar_t__ IEEE_G ; 
 int /*<<< orphan*/  RT_TRACE (int /*<<< orphan*/ ,char*,unsigned int) ; 
 unsigned int TX_POWER_ATHEROAP_THRESH_HIGH ; 
 unsigned int TX_POWER_ATHEROAP_THRESH_LOW ; 
 unsigned int TX_POWER_NEAR_FIELD_THRESH_HIGH ; 
 unsigned int TX_POWER_NEAR_FIELD_THRESH_LOW ; 
 struct r8192_priv* ieee80211_priv (struct net_device*) ; 
 int /*<<< orphan*/  rtl8192_phy_setTxPower (struct net_device*,unsigned int) ; 

__attribute__((used)) static void dm_dynamic_txpower(struct net_device *dev)
{
	struct r8192_priv *priv = ieee80211_priv(dev);
	unsigned int txhipower_threshhold=0;
        unsigned int txlowpower_threshold=0;
	if(priv->ieee80211->bdynamic_txpower_enable != true)
	{
		priv->bDynamicTxHighPower = false;
		priv->bDynamicTxLowPower = false;
		return;
	}
	//printk("priv->ieee80211->current_network.unknown_cap_exist is %d ,priv->ieee80211->current_network.broadcom_cap_exist is %d\n",priv->ieee80211->current_network.unknown_cap_exist,priv->ieee80211->current_network.broadcom_cap_exist);
        if((priv->ieee80211->current_network.atheros_cap_exist ) && (priv->ieee80211->mode == IEEE_G)){
		txhipower_threshhold = TX_POWER_ATHEROAP_THRESH_HIGH;
		txlowpower_threshold = TX_POWER_ATHEROAP_THRESH_LOW;
	}
	else
	{
		txhipower_threshhold = TX_POWER_NEAR_FIELD_THRESH_HIGH;
		txlowpower_threshold = TX_POWER_NEAR_FIELD_THRESH_LOW;
	}

//	printk("=======>%s(): txhipower_threshhold is %d,txlowpower_threshold is %d\n",__FUNCTION__,txhipower_threshhold,txlowpower_threshold);

	RT_TRACE(COMP_TXAGC,"priv->undecorated_smoothed_pwdb = %ld \n" , priv->undecorated_smoothed_pwdb);

	if(priv->ieee80211->state == IEEE80211_LINKED)
	{
		if(priv->undecorated_smoothed_pwdb >= txhipower_threshhold)
		{
			priv->bDynamicTxHighPower = true;
			priv->bDynamicTxLowPower = false;
		}
		else
		{
			// high power state check
			if(priv->undecorated_smoothed_pwdb < txlowpower_threshold && priv->bDynamicTxHighPower == true)
			{
				priv->bDynamicTxHighPower = false;
			}
			// low power state check
			if(priv->undecorated_smoothed_pwdb < 35)
			{
				priv->bDynamicTxLowPower = true;
			}
			else if(priv->undecorated_smoothed_pwdb >= 40)
			{
				priv->bDynamicTxLowPower = false;
			}
		}
	}
	else
	{
		//pHalData->bTXPowerCtrlforNearFarRange = !pHalData->bTXPowerCtrlforNearFarRange;
		priv->bDynamicTxHighPower = false;
		priv->bDynamicTxLowPower = false;
	}

	if( (priv->bDynamicTxHighPower != priv->bLastDTPFlag_High ) ||
		(priv->bDynamicTxLowPower != priv->bLastDTPFlag_Low ) )
	{
		RT_TRACE(COMP_TXAGC,"SetTxPowerLevel8190()  channel = %d \n" , priv->ieee80211->current_network.channel);


		rtl8192_phy_setTxPower(dev,priv->ieee80211->current_network.channel);

	}
	priv->bLastDTPFlag_High = priv->bDynamicTxHighPower;
	priv->bLastDTPFlag_Low = priv->bDynamicTxLowPower;

}