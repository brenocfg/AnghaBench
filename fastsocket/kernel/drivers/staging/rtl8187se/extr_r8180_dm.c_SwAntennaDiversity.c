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
struct r8180_priv {int AdTickCount; int AdCheckPeriod; int AdRxSignalStrength; int AdRxSsThreshold; int bAdSwitchedChecking; scalar_t__ AdRxOkCnt; int AdRxSsBeforeSwitched; int AdMaxRxSsThreshold; int AdMaxCheckPeriod; int AdMinCheckPeriod; scalar_t__ AdMainAntennaRxOkCnt; scalar_t__ AdAuxAntennaRxOkCnt; int CurrAntennaIndex; int bHWAdSwitched; TYPE_1__* ieee80211; } ;
struct net_device {int dummy; } ;
struct TYPE_2__ {scalar_t__ state; } ;

/* Variables and functions */
 scalar_t__ IEEE80211_LINKED ; 
 int /*<<< orphan*/  SwitchAntenna (struct net_device*) ; 
 scalar_t__ ieee80211_priv (struct net_device*) ; 
 int /*<<< orphan*/  printk (char*,int,int) ; 

void
SwAntennaDiversity(
	struct net_device *dev
	)
{
	struct r8180_priv *priv = (struct r8180_priv *)ieee80211_priv(dev);
	bool   bSwCheckSS=false;
//	printk("+SwAntennaDiversity(): CurrAntennaIndex: %d\n", priv->CurrAntennaIndex);
//	printk("AdTickCount is %d\n",priv->AdTickCount);
//by amy 080312
	if(bSwCheckSS)
	{
		priv->AdTickCount++;

		printk("(1) AdTickCount: %d, AdCheckPeriod: %d\n",
			priv->AdTickCount, priv->AdCheckPeriod);
		printk("(2) AdRxSignalStrength: %ld, AdRxSsThreshold: %ld\n",
			priv->AdRxSignalStrength, priv->AdRxSsThreshold);
	}
//	priv->AdTickCount++;//-by amy 080312

	// Case 1. No Link.
	if(priv->ieee80211->state != IEEE80211_LINKED)
	{
	//	printk("SwAntennaDiversity(): Case 1. No Link.\n");

		priv->bAdSwitchedChecking = false;
		// I switch antenna here to prevent any one of antenna is broken before link established, 2006.04.18, by rcnjko..
		SwitchAntenna(dev);
	}
	// Case 2. Linked but no packet received.
	else if(priv->AdRxOkCnt == 0)
	{
	//	printk("SwAntennaDiversity(): Case 2. Linked but no packet received.\n");

		priv->bAdSwitchedChecking = false;
		SwitchAntenna(dev);
	}
	// Case 3. Evaluate last antenna switch action and undo it if necessary.
	else if(priv->bAdSwitchedChecking == true)
	{
	//	printk("SwAntennaDiversity(): Case 3. Evaluate last antenna switch action.\n");

		priv->bAdSwitchedChecking = false;

		// Adjust Rx signal strength threashold.
		priv->AdRxSsThreshold = (priv->AdRxSignalStrength + priv->AdRxSsBeforeSwitched) / 2;

		priv->AdRxSsThreshold = (priv->AdRxSsThreshold > priv->AdMaxRxSsThreshold) ?
					priv->AdMaxRxSsThreshold: priv->AdRxSsThreshold;
		if(priv->AdRxSignalStrength < priv->AdRxSsBeforeSwitched)
		{ // Rx signal strength is not improved after we swtiched antenna. => Swich back.
//			printk("SwAntennaDiversity(): Rx Signal Strength is not improved, CurrRxSs: %d, LastRxSs: %d\n",
//				priv->AdRxSignalStrength, priv->AdRxSsBeforeSwitched);
//by amy 080312
			// Increase Antenna Diversity checking period due to bad decision.
			priv->AdCheckPeriod *= 2;
//by amy 080312
			// Increase Antenna Diversity checking period.
			if(priv->AdCheckPeriod > priv->AdMaxCheckPeriod)
				priv->AdCheckPeriod = priv->AdMaxCheckPeriod;

			// Wrong deceision => switch back.
			SwitchAntenna(dev);
		}
		else
		{ // Rx Signal Strength is improved.
//			printk("SwAntennaDiversity(): Rx Signal Strength is improved, CurrRxSs: %d, LastRxSs: %d\n",
//				priv->AdRxSignalStrength, priv->AdRxSsBeforeSwitched);

			// Reset Antenna Diversity checking period to its min value.
			priv->AdCheckPeriod = priv->AdMinCheckPeriod;
		}

//		printk("SwAntennaDiversity(): AdRxSsThreshold: %d, AdCheckPeriod: %d\n",
//			priv->AdRxSsThreshold, priv->AdCheckPeriod);
	}
	// Case 4. Evaluate if we shall switch antenna now.
	// Cause Table Speed is very fast in TRC Dell Lab, we check it every time.
	else// if(priv->AdTickCount >= priv->AdCheckPeriod)//-by amy 080312
	{
//		printk("SwAntennaDiversity(): Case 4. Evaluate if we shall switch antenna now.\n");

		priv->AdTickCount = 0;

		//
		// <Roger_Notes> We evaluate RxOk counts for each antenna first and than
		// evaluate signal strength.
		// The following operation can overcome the disability of CCA on both two antennas
		// When signal strength was extremely low or high.
		// 2008.01.30.
		//

		//
		// Evaluate RxOk count from each antenna if we shall switch default antenna now.
		// Added by Roger, 2008.02.21.
//{by amy 080312
		if((priv->AdMainAntennaRxOkCnt < priv->AdAuxAntennaRxOkCnt)
			&& (priv->CurrAntennaIndex == 0))
		{ // We set Main antenna as default but RxOk count was less than Aux ones.

	//		printk("SwAntennaDiversity(): Main antenna RxOK is poor, AdMainAntennaRxOkCnt: %d, AdAuxAntennaRxOkCnt: %d\n",
	//			priv->AdMainAntennaRxOkCnt, priv->AdAuxAntennaRxOkCnt);

			// Switch to Aux antenna.
			SwitchAntenna(dev);
			priv->bHWAdSwitched = true;
		}
		else if((priv->AdAuxAntennaRxOkCnt < priv->AdMainAntennaRxOkCnt)
			&& (priv->CurrAntennaIndex == 1))
		{ // We set Aux antenna as default but RxOk count was less than Main ones.

	//		printk("SwAntennaDiversity(): Aux antenna RxOK is poor, AdMainAntennaRxOkCnt: %d, AdAuxAntennaRxOkCnt: %d\n",
	//			priv->AdMainAntennaRxOkCnt, priv->AdAuxAntennaRxOkCnt);

			// Switch to Main antenna.
			SwitchAntenna(dev);
			priv->bHWAdSwitched = true;
		}
		else
		{// Default antenna is better.

	//		printk("SwAntennaDiversity(): Default antenna is better., AdMainAntennaRxOkCnt: %d, AdAuxAntennaRxOkCnt: %d\n",
	//			priv->AdMainAntennaRxOkCnt, priv->AdAuxAntennaRxOkCnt);

			// Still need to check current signal strength.
			priv->bHWAdSwitched = false;
		}
		//
		// <Roger_Notes> We evaluate Rx signal strength ONLY when default antenna
		// didn't changed by HW evaluation.
		// 2008.02.27.
		//
		// [TRC Dell Lab] SignalStrength is inaccuracy. Isaiah 2008-03-05
		// For example, Throughput of aux is better than main antenna(about 10M v.s 2M),
		// but AdRxSignalStrength is less than main.
		// Our guess is that main antenna have lower throughput and get many change
		// to receive more CCK packets(ex.Beacon) which have stronger SignalStrength.
		//
		if( (!priv->bHWAdSwitched) && (bSwCheckSS))
		{
//by amy 080312}
		// Evaluate Rx signal strength if we shall switch antenna now.
		if(priv->AdRxSignalStrength < priv->AdRxSsThreshold)
		{ // Rx signal strength is weak => Switch Antenna.
//			printk("SwAntennaDiversity(): Rx Signal Strength is weak, CurrRxSs: %d, RxSsThreshold: %d\n",
//				priv->AdRxSignalStrength, priv->AdRxSsThreshold);

			priv->AdRxSsBeforeSwitched = priv->AdRxSignalStrength;
			priv->bAdSwitchedChecking = true;

			SwitchAntenna(dev);
		}
		else
		{ // Rx signal strength is OK.
//			printk("SwAntennaDiversity(): Rx Signal Strength is OK, CurrRxSs: %d, RxSsThreshold: %d\n",
//				priv->AdRxSignalStrength, priv->AdRxSsThreshold);

			priv->bAdSwitchedChecking = false;
			// Increase Rx signal strength threashold if necessary.
			if(	(priv->AdRxSignalStrength > (priv->AdRxSsThreshold + 10)) && // Signal is much stronger than current threshold
				priv->AdRxSsThreshold <= priv->AdMaxRxSsThreshold) // Current threhold is not yet reach upper limit.
			{
				priv->AdRxSsThreshold = (priv->AdRxSsThreshold + priv->AdRxSignalStrength) / 2;
				priv->AdRxSsThreshold = (priv->AdRxSsThreshold > priv->AdMaxRxSsThreshold) ?
												priv->AdMaxRxSsThreshold: priv->AdRxSsThreshold;//+by amy 080312
			}

			// Reduce Antenna Diversity checking period if possible.
			if( priv->AdCheckPeriod > priv->AdMinCheckPeriod )
			{
				priv->AdCheckPeriod /= 2;
			}
		}
		}
	}
//by amy 080312
	// Reset antenna diversity Rx related statistics.
	priv->AdRxOkCnt = 0;
	priv->AdMainAntennaRxOkCnt = 0;
	priv->AdAuxAntennaRxOkCnt = 0;
//by amy 080312

//	priv->AdRxOkCnt = 0;//-by amy 080312

//	printk("-SwAntennaDiversity()\n");
}