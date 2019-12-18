#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct r8192_priv {void* CurrentChannelBW; scalar_t__ SetBWModeInProgress; scalar_t__ up; int /*<<< orphan*/  nCur40MhzPrimeSC; } ;
struct net_device {int dummy; } ;
typedef  scalar_t__ HT_EXTCHNL_OFFSET ;
typedef  void* HT_CHANNEL_WIDTH ;

/* Variables and functions */
 int /*<<< orphan*/  COMP_SCAN ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  HAL_PRIME_CHNL_OFFSET_DONT_CARE ; 
 int /*<<< orphan*/  HAL_PRIME_CHNL_OFFSET_LOWER ; 
 int /*<<< orphan*/  HAL_PRIME_CHNL_OFFSET_UPPER ; 
 scalar_t__ HT_EXTCHNL_OFFSET_LOWER ; 
 scalar_t__ HT_EXTCHNL_OFFSET_UPPER ; 
 int /*<<< orphan*/  RT_TRACE (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  SetBWModeCallback8192SUsbWorkItem (struct net_device*) ; 
 scalar_t__ TRUE ; 
 struct r8192_priv* ieee80211_priv (struct net_device*) ; 

void rtl8192_SetBWMode(struct net_device *dev, HT_CHANNEL_WIDTH	Bandwidth, HT_EXTCHNL_OFFSET Offset)
{
	struct r8192_priv *priv = ieee80211_priv(dev);
	HT_CHANNEL_WIDTH tmpBW = priv->CurrentChannelBW;


	// Modified it for 20/40 mhz switch by guangan 070531

	//return;

	//if(priv->SwChnlInProgress)
//	if(pMgntInfo->bScanInProgress)
//	{
//		RT_TRACE(COMP_SCAN, DBG_LOUD, ("SetBWMode8190Pci() %s Exit because bScanInProgress!\n",
//					Bandwidth == HT_CHANNEL_WIDTH_20?"20MHz":"40MHz"));
//		return;
//	}

//	if(priv->SetBWModeInProgress)
//	{
//		// Modified it for 20/40 mhz switch by guangan 070531
//		RT_TRACE(COMP_SCAN, DBG_LOUD, ("SetBWMode8190Pci() %s cancel last timer because SetBWModeInProgress!\n",
//					Bandwidth == HT_CHANNEL_WIDTH_20?"20MHz":"40MHz"));
//		PlatformCancelTimer(dev, &priv->SetBWModeTimer);
//		//return;
//	}

	if(priv->SetBWModeInProgress)
		return;

	priv->SetBWModeInProgress= TRUE;

	priv->CurrentChannelBW = Bandwidth;

	if(Offset==HT_EXTCHNL_OFFSET_LOWER)
		priv->nCur40MhzPrimeSC = HAL_PRIME_CHNL_OFFSET_UPPER;
	else if(Offset==HT_EXTCHNL_OFFSET_UPPER)
		priv->nCur40MhzPrimeSC = HAL_PRIME_CHNL_OFFSET_LOWER;
	else
		priv->nCur40MhzPrimeSC = HAL_PRIME_CHNL_OFFSET_DONT_CARE;

	if((priv->up) )// && !(RT_CANNOT_IO(Adapter) && Adapter->bInSetPower) )
	{
	SetBWModeCallback8192SUsbWorkItem(dev);
	}
	else
	{
		RT_TRACE(COMP_SCAN, "PHY_SetBWMode8192S() SetBWModeInProgress FALSE driver sleep or unload\n");
		priv->SetBWModeInProgress= FALSE;
		priv->CurrentChannelBW = tmpBW;
	}
}