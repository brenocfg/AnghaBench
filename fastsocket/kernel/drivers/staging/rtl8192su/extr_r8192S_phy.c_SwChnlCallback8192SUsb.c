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
typedef  scalar_t__ u32 ;
struct r8192_priv {scalar_t__ rf_chip; void* SwChnlInProgress; int /*<<< orphan*/  SwChnlStep; int /*<<< orphan*/  SwChnlStage; int /*<<< orphan*/  chan; int /*<<< orphan*/  up; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  COMP_SCAN ; 
 void* FALSE ; 
 scalar_t__ RF_PSEUDO_11N ; 
 int /*<<< orphan*/  RT_TRACE (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ TRUE ; 
 struct r8192_priv* ieee80211_priv (struct net_device*) ; 
 int /*<<< orphan*/  phy_SwChnlStepByStep (struct net_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__*) ; 

void SwChnlCallback8192SUsb(struct net_device *dev)
{

	struct r8192_priv *priv = ieee80211_priv(dev);
	u32			delay;
//	bool			ret;

	RT_TRACE(COMP_SCAN, "==>SwChnlCallback8190Pci(), switch to channel\
				%d\n", priv->chan);


	if(!priv->up)
		return;

	if(priv->rf_chip == RF_PSEUDO_11N)
	{
		priv->SwChnlInProgress=FALSE;
		return; 								//return immediately if it is peudo-phy
	}

	do{
		if(!priv->SwChnlInProgress)
			break;

		if(!phy_SwChnlStepByStep(dev, priv->chan, &priv->SwChnlStage, &priv->SwChnlStep, &delay))
		{
			if(delay>0)
			{
				//PlatformSetTimer(dev, &priv->SwChnlTimer, delay);

			}
			else
			continue;
		}
		else
		{
			priv->SwChnlInProgress=FALSE;
		}
		break;
	}while(TRUE);
}