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
struct r8180_priv {scalar_t__ CurrAntennaIndex; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int SetAntenna8185 (struct net_device*,int) ; 
 scalar_t__ ieee80211_priv (struct net_device*) ; 

bool
SwitchAntenna(
	struct net_device *dev
	)
{
	struct r8180_priv *priv = (struct r8180_priv *)ieee80211_priv(dev);

	bool		bResult;

	if(priv->CurrAntennaIndex == 0)
	{
			bResult = SetAntenna8185(dev, 1);
//by amy 080312
//		printk("SwitchAntenna(): switching to antenna 1 ......\n");
//		bResult = SetAntenna8185(dev, 1);//-by amy 080312
	}
	else
	{
			bResult = SetAntenna8185(dev, 0);
//by amy 080312
//		printk("SwitchAntenna(): switching to antenna 0 ......\n");
//		bResult = SetAntenna8185(dev, 0);//-by amy 080312
	}

	return bResult;
}