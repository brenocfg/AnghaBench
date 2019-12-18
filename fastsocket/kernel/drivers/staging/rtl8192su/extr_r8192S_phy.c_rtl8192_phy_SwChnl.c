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
typedef  int u8 ;
struct r8192_priv {int SwChnlInProgress; int chan; int /*<<< orphan*/  CurrentChannel; scalar_t__ up; scalar_t__ SwChnlStep; scalar_t__ SwChnlStage; TYPE_1__* ieee80211; scalar_t__ SetBWModeInProgress; } ;
struct net_device {int dummy; } ;
struct TYPE_2__ {int mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  COMP_ERR ; 
 int /*<<< orphan*/  COMP_SCAN ; 
 int /*<<< orphan*/  RT_TRACE (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  SwChnlCallback8192SUsbWorkItem (struct net_device*) ; 
 int TRUE ; 
#define  WIRELESS_MODE_A 132 
#define  WIRELESS_MODE_B 131 
#define  WIRELESS_MODE_G 130 
#define  WIRELESS_MODE_N_24G 129 
#define  WIRELESS_MODE_N_5G 128 
 scalar_t__ bResult ; 
 struct r8192_priv* ieee80211_priv (struct net_device*) ; 
 int /*<<< orphan*/  tmpchannel ; 

u8 rtl8192_phy_SwChnl(struct net_device* dev, u8 channel)
{
	struct r8192_priv *priv = ieee80211_priv(dev);
	//u8 			tmpchannel =channel;
	//bool			bResult = false;

        if(!priv->up)
		return false;

	if(priv->SwChnlInProgress)
		return false;

	if(priv->SetBWModeInProgress)
		return false;

	//--------------------------------------------
	switch(priv->ieee80211->mode)
	{
	case WIRELESS_MODE_A:
	case WIRELESS_MODE_N_5G:
		if (channel<=14){
			RT_TRACE(COMP_ERR, "WIRELESS_MODE_A but channel<=14");
			return false;
		}
		break;

	case WIRELESS_MODE_B:
		if (channel>14){
			RT_TRACE(COMP_ERR, "WIRELESS_MODE_B but channel>14");
			return false;
		}
		break;

	case WIRELESS_MODE_G:
	case WIRELESS_MODE_N_24G:
		if (channel>14){
			RT_TRACE(COMP_ERR, "WIRELESS_MODE_G but channel>14");
			return false;
		}
		break;

	default:
			;//RT_TRACE(COMP_ERR, "Invalid WirelessMode(%#x)!!\n", priv->ieee80211->mode);
		break;
	}
	//--------------------------------------------

	priv->SwChnlInProgress = TRUE;
	if( channel == 0)
		channel = 1;

	priv->chan=channel;

	priv->SwChnlStage=0;
	priv->SwChnlStep=0;

	if((priv->up))// && !(RT_CANNOT_IO(Adapter) && Adapter->bInSetPower))
	{
	SwChnlCallback8192SUsbWorkItem(dev);
#ifdef TO_DO_LIST
	if(bResult)
		{
			RT_TRACE(COMP_SCAN, "PHY_SwChnl8192S SwChnlInProgress TRUE schdule workitem done\n");
		}
		else
		{
			RT_TRACE(COMP_SCAN, "PHY_SwChnl8192S SwChnlInProgress FALSE schdule workitem error\n");
			priv->SwChnlInProgress = false;
			priv->CurrentChannel = tmpchannel;
		}
#endif
	}
	else
	{
		RT_TRACE(COMP_SCAN, "PHY_SwChnl8192S SwChnlInProgress FALSE driver sleep or unload\n");
		priv->SwChnlInProgress = false;
		//priv->CurrentChannel = tmpchannel;
	}
        return true;
}