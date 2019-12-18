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
typedef  int u32 ;
typedef  int u16 ;
struct r8180_priv {int FalseAlarmRegValue; int InitialGain; int DozePeriodInPast2Sec; int RegBModeGainStage; int DIG_NumberFallbackVote; int InitialGainBackUp; int DIG_NumberUpgradeVote; scalar_t__ RegDigOfdmFaUpTh; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  UpdateInitialGain (struct net_device*) ; 
 struct r8180_priv* ieee80211_priv (struct net_device*) ; 

void
DIG_Zebra(
	struct net_device *dev
	)
{
	struct r8180_priv *priv = ieee80211_priv(dev);
	u16			CCKFalseAlarm, OFDMFalseAlarm;
	u16			OfdmFA1, OfdmFA2;
	int			InitialGainStep = 7; // The number of initial gain stages.
	int			LowestGainStage = 4; // The capable lowest stage of performing dig workitem.
	u32 			AwakePeriodIn2Sec=0;

	//printk("---------> DIG_Zebra()\n");

	CCKFalseAlarm = (u16)(priv->FalseAlarmRegValue & 0x0000ffff);
	OFDMFalseAlarm = (u16)((priv->FalseAlarmRegValue >> 16) & 0x0000ffff);
	OfdmFA1 =  0x15;
	OfdmFA2 = ((u16)(priv->RegDigOfdmFaUpTh)) << 8;

//	printk("DIG**********CCK False Alarm: %#X \n",CCKFalseAlarm);
//	printk("DIG**********OFDM False Alarm: %#X \n",OFDMFalseAlarm);

        // The number of initial gain steps is different, by Bruce, 2007-04-13.
	if (priv->InitialGain == 0 ) //autoDIG
	{ // Advised from SD3 DZ
		priv->InitialGain = 4; // In 87B, m74dBm means State 4 (m82dBm)
	}
	//if(pHalData->VersionID != VERSION_8187B_B)
	{ // Advised from SD3 DZ
		OfdmFA1 =  0x20;
	}

#if 1 //lzm reserved 080826
	AwakePeriodIn2Sec = (2000-priv ->DozePeriodInPast2Sec);
	//printk("&&& DozePeriod=%d AwakePeriod=%d\n", priv->DozePeriodInPast2Sec, AwakePeriodIn2Sec);
	priv ->DozePeriodInPast2Sec=0;

	if(AwakePeriodIn2Sec)
	{
		//RT_TRACE(COMP_DIG, DBG_TRACE, ("DIG: AwakePeriodIn2Sec(%d) - FATh(0x%X , 0x%X) ->",AwakePeriodIn2Sec, OfdmFA1, OfdmFA2));
		// adjuest DIG threshold.
		OfdmFA1 =  (u16)((OfdmFA1*AwakePeriodIn2Sec)  / 2000) ;
		OfdmFA2 =  (u16)((OfdmFA2*AwakePeriodIn2Sec)  / 2000) ;
		//RT_TRACE(COMP_DIG, DBG_TRACE, ("( 0x%X , 0x%X)\n", OfdmFA1, OfdmFA2));
	}
	else
	{
		;//RT_TRACE(COMP_DIG, DBG_WARNING, ("ERROR!!  AwakePeriodIn2Sec should not be ZERO!!\n"));
	}
#endif

	InitialGainStep = 8;
	LowestGainStage = priv->RegBModeGainStage; // Lowest gain stage.

	if (OFDMFalseAlarm > OfdmFA1)
	{
		if (OFDMFalseAlarm > OfdmFA2)
		{
			priv->DIG_NumberFallbackVote++;
			if (priv->DIG_NumberFallbackVote >1)
			{
				//serious OFDM  False Alarm, need fallback
				if (priv->InitialGain < InitialGainStep)
				{
					priv->InitialGainBackUp= priv->InitialGain;

					priv->InitialGain = (priv->InitialGain + 1);
//					printk("DIG**********OFDM False Alarm: %#X,  OfdmFA1: %#X, OfdmFA2: %#X\n", OFDMFalseAlarm, OfdmFA1, OfdmFA2);
//					printk("DIG+++++++ fallback OFDM:%d \n", priv->InitialGain);
					UpdateInitialGain(dev);
				}
				priv->DIG_NumberFallbackVote = 0;
				priv->DIG_NumberUpgradeVote=0;
			}
		}
		else
		{
			if (priv->DIG_NumberFallbackVote)
				priv->DIG_NumberFallbackVote--;
		}
		priv->DIG_NumberUpgradeVote=0;
	}
	else
	{
		if (priv->DIG_NumberFallbackVote)
			priv->DIG_NumberFallbackVote--;
		priv->DIG_NumberUpgradeVote++;

		if (priv->DIG_NumberUpgradeVote>9)
		{
			if (priv->InitialGain > LowestGainStage) // In 87B, m78dBm means State 4 (m864dBm)
			{
				priv->InitialGainBackUp= priv->InitialGain;

				priv->InitialGain = (priv->InitialGain - 1);
//				printk("DIG**********OFDM False Alarm: %#X,  OfdmFA1: %#X, OfdmFA2: %#X\n", OFDMFalseAlarm, OfdmFA1, OfdmFA2);
//				printk("DIG--------- Upgrade OFDM:%d \n", priv->InitialGain);
				UpdateInitialGain(dev);
			}
			priv->DIG_NumberFallbackVote = 0;
			priv->DIG_NumberUpgradeVote=0;
		}
	}

//	printk("DIG+++++++ OFDM:%d\n", priv->InitialGain);
	//printk("<--------- DIG_Zebra()\n");
}