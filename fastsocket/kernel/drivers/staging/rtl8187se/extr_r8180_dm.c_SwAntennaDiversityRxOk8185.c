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
typedef  int u8 ;
struct r8180_priv {int AdRxSignalStrength; int /*<<< orphan*/  AdAuxAntennaRxOkCnt; int /*<<< orphan*/  AdMainAntennaRxOkCnt; scalar_t__ LastRxPktAntenna; int /*<<< orphan*/  AdRxOkCnt; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 scalar_t__ ieee80211_priv (struct net_device*) ; 

void
SwAntennaDiversityRxOk8185(
	struct net_device *dev,
	u8 SignalStrength
	)
{
	struct r8180_priv *priv = (struct r8180_priv *)ieee80211_priv(dev);

//	printk("+SwAntennaDiversityRxOk8185: RxSs: %d\n", SignalStrength);

	priv->AdRxOkCnt++;

	if( priv->AdRxSignalStrength != -1)
	{
		priv->AdRxSignalStrength = ((priv->AdRxSignalStrength*7) + (SignalStrength*3)) / 10;
	}
	else
	{ // Initialization case.
		priv->AdRxSignalStrength = SignalStrength;
	}
//{+by amy 080312
	if( priv->LastRxPktAntenna ) //Main antenna.
		priv->AdMainAntennaRxOkCnt++;
	else	 // Aux antenna.
		priv->AdAuxAntennaRxOkCnt++;
//+by amy 080312
//	printk("-SwAntennaDiversityRxOk8185: AdRxOkCnt: %d AdRxSignalStrength: %d\n", priv->AdRxOkCnt, priv->AdRxSignalStrength);
}