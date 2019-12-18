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
struct r8192_priv {int SetBWModeInProgress; int /*<<< orphan*/  nCur40MhzPrimeSC; int /*<<< orphan*/  CurrentChannelBW; TYPE_1__* ieee80211; } ;
struct net_device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  atm_swbw; } ;
typedef  scalar_t__ HT_EXTCHNL_OFFSET ;
typedef  int /*<<< orphan*/  HT_CHANNEL_WIDTH ;

/* Variables and functions */
 int /*<<< orphan*/  HAL_PRIME_CHNL_OFFSET_DONT_CARE ; 
 int /*<<< orphan*/  HAL_PRIME_CHNL_OFFSET_LOWER ; 
 int /*<<< orphan*/  HAL_PRIME_CHNL_OFFSET_UPPER ; 
 scalar_t__ HT_EXTCHNL_OFFSET_LOWER ; 
 scalar_t__ HT_EXTCHNL_OFFSET_UPPER ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 struct r8192_priv* ieee80211_priv (struct net_device*) ; 
 int /*<<< orphan*/  rtl8192_SetBWModeWorkItem (struct net_device*) ; 

void rtl8192_SetBWMode(struct net_device *dev, HT_CHANNEL_WIDTH	Bandwidth, HT_EXTCHNL_OFFSET Offset)
{
	struct r8192_priv *priv = ieee80211_priv(dev);


	if(priv->SetBWModeInProgress)
		return;

	 atomic_inc(&(priv->ieee80211->atm_swbw));
	priv->SetBWModeInProgress= true;

	priv->CurrentChannelBW = Bandwidth;

	if(Offset==HT_EXTCHNL_OFFSET_LOWER)
		priv->nCur40MhzPrimeSC = HAL_PRIME_CHNL_OFFSET_UPPER;
	else if(Offset==HT_EXTCHNL_OFFSET_UPPER)
		priv->nCur40MhzPrimeSC = HAL_PRIME_CHNL_OFFSET_LOWER;
	else
		priv->nCur40MhzPrimeSC = HAL_PRIME_CHNL_OFFSET_DONT_CARE;

	//queue_work(priv->priv_wq, &(priv->SetBWModeWorkItem));
	//	schedule_work(&(priv->SetBWModeWorkItem));
	rtl8192_SetBWModeWorkItem(dev);

}