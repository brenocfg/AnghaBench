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
 int /*<<< orphan*/  COMP_CH ; 
 void* FALSE ; 
 scalar_t__ RF_PSEUDO_11N ; 
 int /*<<< orphan*/  RT_TRACE (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 struct r8192_priv* ieee80211_priv (struct net_device*) ; 
 int /*<<< orphan*/  mdelay (scalar_t__) ; 
 int /*<<< orphan*/  phy_SwChnlStepByStep (struct net_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__*) ; 

void PHY_SwChnlCallback8192S(struct net_device *dev)
{

	struct r8192_priv *priv = ieee80211_priv(dev);
	u32		delay;
	//bool			ret;

	RT_TRACE(COMP_CH, "==>SwChnlCallback8190Pci(), switch to channel %d\n", priv->chan);

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

		//if(!phy_SwChnlStepByStep(dev, priv->CurrentChannel, &priv->SwChnlStage, &priv->SwChnlStep, &delay))
		if(!phy_SwChnlStepByStep(dev, priv->chan, &priv->SwChnlStage, &priv->SwChnlStep, &delay))
		{
			if(delay>0)
			{
				mdelay(delay);
				//PlatformSetTimer(dev, &priv->SwChnlTimer, delay);
				//mod_timer(&priv->SwChnlTimer,  jiffies + MSECS(delay));
				//==>PHY_SwChnlCallback8192S(dev); for 92se
				//==>SwChnlCallback8192SUsb(dev) for 92su
			}
			else
			continue;
		}
		else
		{
			priv->SwChnlInProgress=FALSE;
			break;
		}
	}while(true);
}