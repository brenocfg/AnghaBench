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
typedef  scalar_t__ u8 ;
typedef  scalar_t__ u32 ;
typedef  int u16 ;
struct r8180_priv {int RateAdaptivePeriod; int CurrRetryCnt; unsigned long NumTxOkTotal; unsigned long LastTxokCnt; unsigned long LastRxokCnt; long Stats_RecvSignalPower; int CurrentOperaRate; int LastRetryCnt; int TryupingCountNoData; int LastFailTxRate; int LastFailTxRateSS; int FailTxRateCount; int bTryuping; scalar_t__ LastTxThroughput; scalar_t__ TryupingCount; scalar_t__ TryDownCountLowData; int LastRetryRate; int bUpdateARFR; char* chtxpwr_ofdm; char* chtxpwr; int bEnhanceTxPwr; int InitialGain; int RegBModeGainStage; int InitialGainBackUp; TYPE_2__* ieee80211; scalar_t__ NumTxOkBytesTotal; scalar_t__ LastTxOKBytes; } ;
struct net_device {int dummy; } ;
struct TYPE_3__ {int HighestOperaRate; size_t channel; } ;
struct TYPE_4__ {unsigned long NumRxOkTotal; int rate; TYPE_1__ current_network; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARFR ; 
 int /*<<< orphan*/  CCK_TXAGC ; 
 int GetDegradeTxRate (struct net_device*,int) ; 
 void* GetUpgradeTxRate (struct net_device*,int) ; 
 scalar_t__ MgntIsCckRate (int) ; 
 int /*<<< orphan*/  OFDM_TXAGC ; 
 int RATE_ADAPTIVE_TIMER_PERIOD ; 
 int /*<<< orphan*/  UpdateInitialGain (struct net_device*) ; 
 scalar_t__ ieee80211_priv (struct net_device*) ; 
 int jiffies ; 
 int /*<<< orphan*/  printk (char*,...) ; 
 scalar_t__ read_nic_byte (struct net_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_nic_byte (struct net_device*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  write_nic_word (struct net_device*,int /*<<< orphan*/ ,int) ; 

void
StaRateAdaptive87SE(
	struct net_device *dev
	)
{
	struct r8180_priv *priv = (struct r8180_priv *)ieee80211_priv(dev);
	unsigned long 			CurrTxokCnt;
	u16			CurrRetryCnt;
	u16			CurrRetryRate;
	//u16			i,idx;
	unsigned long       	CurrRxokCnt;
	bool			bTryUp = false;
	bool			bTryDown = false;
	u8			TryUpTh = 1;
	u8			TryDownTh = 2;
	u32			TxThroughput;
	long		CurrSignalStrength;
	bool		bUpdateInitialGain = false;
    	u8			u1bOfdm=0, u1bCck = 0;
	char		OfdmTxPwrIdx, CckTxPwrIdx;

	priv->RateAdaptivePeriod= RATE_ADAPTIVE_TIMER_PERIOD;


	CurrRetryCnt	= priv->CurrRetryCnt;
	CurrTxokCnt	= priv->NumTxOkTotal - priv->LastTxokCnt;
	CurrRxokCnt	= priv->ieee80211->NumRxOkTotal - priv->LastRxokCnt;
	CurrSignalStrength = priv->Stats_RecvSignalPower;
	TxThroughput = (u32)(priv->NumTxOkBytesTotal - priv->LastTxOKBytes);
	priv->LastTxOKBytes = priv->NumTxOkBytesTotal;
	priv->CurrentOperaRate = priv->ieee80211->rate/5;
	//printk("priv->CurrentOperaRate is %d\n",priv->CurrentOperaRate);
	//2 Compute retry ratio.
	if (CurrTxokCnt>0)
	{
		CurrRetryRate = (u16)(CurrRetryCnt*100/CurrTxokCnt);
	}
	else
	{ // It may be serious retry. To distinguish serious retry or no packets modified by Bruce
		CurrRetryRate = (u16)(CurrRetryCnt*100/1);
	}


	//
	// Added by Roger, 2007.01.02.
	// For debug information.
	//
	//printk("\n(1) pHalData->LastRetryRate: %d \n",priv->LastRetryRate);
	//printk("(2) RetryCnt = %d  \n", CurrRetryCnt);
	//printk("(3) TxokCnt = %d \n", CurrTxokCnt);
	//printk("(4) CurrRetryRate = %d \n", CurrRetryRate);
	//printk("(5) CurrSignalStrength = %d \n",CurrSignalStrength);
	//printk("(6) TxThroughput is %d\n",TxThroughput);
	//printk("priv->NumTxOkBytesTotal is %d\n",priv->NumTxOkBytesTotal);

	priv->LastRetryCnt = priv->CurrRetryCnt;
	priv->LastTxokCnt = priv->NumTxOkTotal;
	priv->LastRxokCnt = priv->ieee80211->NumRxOkTotal;
	priv->CurrRetryCnt = 0;

	//2No Tx packets, return to init_rate or not?
	if (CurrRetryRate==0 && CurrTxokCnt == 0)
	{
		//
		//After 9 (30*300ms) seconds in this condition, we try to raise rate.
		//
		priv->TryupingCountNoData++;

//		printk("No Tx packets, TryupingCountNoData(%d)\n", priv->TryupingCountNoData);
		//[TRC Dell Lab] Extend raised period from 4.5sec to 9sec, Isaiah 2008-02-15 18:00
		if (priv->TryupingCountNoData>30)
		{
			priv->TryupingCountNoData = 0;
		 	priv->CurrentOperaRate = GetUpgradeTxRate(dev, priv->CurrentOperaRate);
			// Reset Fail Record
			priv->LastFailTxRate = 0;
			priv->LastFailTxRateSS = -200;
			priv->FailTxRateCount = 0;
		}
		goto SetInitialGain;
	}
        else
	{
		priv->TryupingCountNoData=0; //Reset trying up times.
	}


	//
	// For Netgear case, I comment out the following signal strength estimation,
	// which can results in lower rate to transmit when sample is NOT enough (e.g. PING request).
	// 2007.04.09, by Roger.
	//

	//
	// Restructure rate adaptive as the following main stages:
	// (1) Add retry threshold in 54M upgrading condition with signal strength.
	// (2) Add the mechanism to degrade to CCK rate according to signal strength
	//		and retry rate.
	// (3) Remove all Initial Gain Updates over OFDM rate. To avoid the complicated
	//		situation, Initial Gain Update is upon on DIG mechanism except CCK rate.
	// (4) Add the mehanism of trying to upgrade tx rate.
	// (5) Record the information of upping tx rate to avoid trying upping tx rate constantly.
	// By Bruce, 2007-06-05.
	//
	//

	// 11Mbps or 36Mbps
	// Check more times in these rate(key rates).
	//
	if(priv->CurrentOperaRate == 22 || priv->CurrentOperaRate == 72)
	{
		TryUpTh += 9;
	}
	//
	// Let these rates down more difficult.
	//
	if(MgntIsCckRate(priv->CurrentOperaRate) || priv->CurrentOperaRate == 36)
	{
			TryDownTh += 1;
	}

	//1 Adjust Rate.
	if (priv->bTryuping == true)
	{
		//2 For Test Upgrading mechanism
		// Note:
		// 	Sometimes the throughput is upon on the capability bwtween the AP and NIC,
		// 	thus the low data rate does not improve the performance.
		// 	We randomly upgrade the data rate and check if the retry rate is improved.

		// Upgrading rate did not improve the retry rate, fallback to the original rate.
		if ( (CurrRetryRate > 25) && TxThroughput < priv->LastTxThroughput)
		{
			//Not necessary raising rate, fall back rate.
			bTryDown = true;
			//printk("case1-1: Not necessary raising rate, fall back rate....\n");
			//printk("case1-1: pMgntInfo->CurrentOperaRate =%d, TxThroughput = %d, LastThroughput = %d\n",
			//		priv->CurrentOperaRate, TxThroughput, priv->LastTxThroughput);
		}
		else
		{
			priv->bTryuping = false;
		}
	}
	else if (CurrSignalStrength > -47 && (CurrRetryRate < 50))
	{
		//2For High Power
		//
		// Added by Roger, 2007.04.09.
		// Return to highest data rate, if signal strength is good enough.
		// SignalStrength threshold(-50dbm) is for RTL8186.
		// Revise SignalStrength threshold to -51dbm.
		//
		// Also need to check retry rate for safety, by Bruce, 2007-06-05.
		if(priv->CurrentOperaRate != priv->ieee80211->current_network.HighestOperaRate )
		{
			bTryUp = true;
			// Upgrade Tx Rate directly.
			priv->TryupingCount += TryUpTh;
		}
//		printk("case2: StaRateAdaptive87SE: Power(%d) is high enough!!. \n", CurrSignalStrength);

	}
	else if(CurrTxokCnt > 9 && CurrTxokCnt< 100 && CurrRetryRate >= 600)
	{
		//2 For Serious Retry
		//
		// Traffic is not busy but our Tx retry is serious.
		//
		bTryDown = true;
		// Let Rate Mechanism to degrade tx rate directly.
		priv->TryDownCountLowData += TryDownTh;
//		printk("case3: RA: Tx Retry is serious. Degrade Tx Rate to %d directly...\n", priv->CurrentOperaRate);
	}
	else if ( priv->CurrentOperaRate == 108 )
	{
		//2For 54Mbps
		// Air Link
		if ( (CurrRetryRate>26)&&(priv->LastRetryRate>25))
//		if ( (CurrRetryRate>40)&&(priv->LastRetryRate>39))
		{
			//Down to rate 48Mbps.
			bTryDown = true;
		}
		// Cable Link
		else if ( (CurrRetryRate>17)&&(priv->LastRetryRate>16) && (CurrSignalStrength > -72))
//		else if ( (CurrRetryRate>17)&&(priv->LastRetryRate>16) && (CurrSignalStrength > -72))
		{
			//Down to rate 48Mbps.
			bTryDown = true;
		}

		if(bTryDown && (CurrSignalStrength < -75)) //cable link
		{
			priv->TryDownCountLowData += TryDownTh;
		}
		//printk("case4---54M \n");

	}
	else if ( priv->CurrentOperaRate == 96 )
	{
		//2For 48Mbps
		//Air Link
		if ( ((CurrRetryRate>48) && (priv->LastRetryRate>47)))
//		if ( ((CurrRetryRate>65) && (priv->LastRetryRate>64)))

		{
			//Down to rate 36Mbps.
			bTryDown = true;
		}
		//Cable Link
		else if ( ((CurrRetryRate>21) && (priv->LastRetryRate>20)) && (CurrSignalStrength > -74))
		{
			//Down to rate 36Mbps.
			bTryDown = true;
		}
		else if((CurrRetryRate>  (priv->LastRetryRate + 50 )) && (priv->FailTxRateCount >2 ))
//		else if((CurrRetryRate>  (priv->LastRetryRate + 70 )) && (priv->FailTxRateCount >2 ))
		{
			bTryDown = true;
			priv->TryDownCountLowData += TryDownTh;
		}
		else if ( (CurrRetryRate<8) && (priv->LastRetryRate<8) ) //TO DO: need to consider (RSSI)
//		else if ( (CurrRetryRate<28) && (priv->LastRetryRate<8) )
		{
			bTryUp = true;
		}

		if(bTryDown && (CurrSignalStrength < -75))
		{
			priv->TryDownCountLowData += TryDownTh;
		}
		//printk("case5---48M \n");
	}
	else if ( priv->CurrentOperaRate == 72 )
	{
		//2For 36Mbps
		if ( (CurrRetryRate>43) && (priv->LastRetryRate>41))
//		if ( (CurrRetryRate>60) && (priv->LastRetryRate>59))
		{
			//Down to rate 24Mbps.
			bTryDown = true;
		}
		else if((CurrRetryRate>  (priv->LastRetryRate + 50 )) && (priv->FailTxRateCount >2 ))
//		else if((CurrRetryRate>  (priv->LastRetryRate + 70 )) && (priv->FailTxRateCount >2 ))
		{
			bTryDown = true;
			priv->TryDownCountLowData += TryDownTh;
		}
		else if ( (CurrRetryRate<15) &&  (priv->LastRetryRate<16)) //TO DO: need to consider (RSSI)
//		else if ( (CurrRetryRate<35) &&  (priv->LastRetryRate<36))
		{
			bTryUp = true;
		}

		if(bTryDown && (CurrSignalStrength < -80))
		{
			priv->TryDownCountLowData += TryDownTh;
		}
		//printk("case6---36M \n");
	}
	else if ( priv->CurrentOperaRate == 48 )
	{
		//2For 24Mbps
		// Air Link
		if ( ((CurrRetryRate>63) && (priv->LastRetryRate>62)))
//		if ( ((CurrRetryRate>83) && (priv->LastRetryRate>82)))
		{
			//Down to rate 18Mbps.
			bTryDown = true;
		}
		//Cable Link
		else if ( ((CurrRetryRate>33) && (priv->LastRetryRate>32)) && (CurrSignalStrength > -82) )
//		 else if ( ((CurrRetryRate>50) && (priv->LastRetryRate>49)) && (CurrSignalStrength > -82) )
		{
			//Down to rate 18Mbps.
			bTryDown = true;
		}
		else if((CurrRetryRate>  (priv->LastRetryRate + 50 )) && (priv->FailTxRateCount >2 ))
//		else if((CurrRetryRate>  (priv->LastRetryRate + 70 )) && (priv->FailTxRateCount >2 ))

		{
			bTryDown = true;
			priv->TryDownCountLowData += TryDownTh;
		}
  		else if ( (CurrRetryRate<20) && (priv->LastRetryRate<21)) //TO DO: need to consider (RSSI)
//		else if ( (CurrRetryRate<40) && (priv->LastRetryRate<41))
		{
			bTryUp = true;
		}

		if(bTryDown && (CurrSignalStrength < -82))
		{
			priv->TryDownCountLowData += TryDownTh;
		}
		//printk("case7---24M \n");
	}
	else if ( priv->CurrentOperaRate == 36 )
	{
		//2For 18Mbps
		// original (109, 109)
		//[TRC Dell Lab] (90, 91), Isaiah 2008-02-18 23:24
		//			     (85, 86), Isaiah 2008-02-18 24:00
		if ( ((CurrRetryRate>85) && (priv->LastRetryRate>86)))
//		if ( ((CurrRetryRate>115) && (priv->LastRetryRate>116)))
		{
			//Down to rate 11Mbps.
			bTryDown = true;
		}
		//[TRC Dell Lab]  Isaiah 2008-02-18 23:24
		else if((CurrRetryRate>  (priv->LastRetryRate + 50 )) && (priv->FailTxRateCount >2 ))
//		else if((CurrRetryRate>  (priv->LastRetryRate + 70 )) && (priv->FailTxRateCount >2 ))
		{
			bTryDown = true;
			priv->TryDownCountLowData += TryDownTh;
		}
		else if ( (CurrRetryRate<22) && (priv->LastRetryRate<23)) //TO DO: need to consider (RSSI)
//		else if ( (CurrRetryRate<42) && (priv->LastRetryRate<43))
		{
			bTryUp = true;
		}
		//printk("case8---18M \n");
	}
	else if ( priv->CurrentOperaRate == 22 )
	{
		//2For 11Mbps
		if (CurrRetryRate>95)
//		if (CurrRetryRate>155)
		{
			bTryDown = true;
		}
		else if ( (CurrRetryRate<29) && (priv->LastRetryRate <30) )//TO DO: need to consider (RSSI)
//		else if ( (CurrRetryRate<49) && (priv->LastRetryRate <50) )
			{
			bTryUp = true;
			}
		//printk("case9---11M \n");
		}
	else if ( priv->CurrentOperaRate == 11 )
	{
		//2For 5.5Mbps
		if (CurrRetryRate>149)
//		if (CurrRetryRate>189)
		{
			bTryDown = true;
		}
		else if ( (CurrRetryRate<60) && (priv->LastRetryRate < 65))
//		else if ( (CurrRetryRate<80) && (priv->LastRetryRate < 85))

			{
			bTryUp = true;
			}
		//printk("case10---5.5M \n");
		}
	else if ( priv->CurrentOperaRate == 4 )
	{
		//2For 2 Mbps
		if((CurrRetryRate>99) && (priv->LastRetryRate>99))
//		if((CurrRetryRate>199) && (priv->LastRetryRate>199))
		{
			bTryDown = true;
		}
		else if ( (CurrRetryRate < 65) && (priv->LastRetryRate < 70))
//		else if ( (CurrRetryRate < 85) && (priv->LastRetryRate < 90))
		{
			bTryUp = true;
		}
		//printk("case11---2M \n");
	}
	else if ( priv->CurrentOperaRate == 2 )
	{
		//2For 1 Mbps
		if( (CurrRetryRate<70) && (priv->LastRetryRate<75))
//		if( (CurrRetryRate<90) && (priv->LastRetryRate<95))
		{
			bTryUp = true;
		}
		//printk("case12---1M \n");
	}

	if(bTryUp && bTryDown)
    	printk("StaRateAdaptive87B(): Tx Rate tried upping and downing simultaneously!\n");

	//1 Test Upgrading Tx Rate
	// Sometimes the cause of the low throughput (high retry rate) is the compatibility between the AP and NIC.
	// To test if the upper rate may cause lower retry rate, this mechanism randomly occurs to test upgrading tx rate.
	if(!bTryUp && !bTryDown && (priv->TryupingCount == 0) && (priv->TryDownCountLowData == 0)
		&& priv->CurrentOperaRate != priv->ieee80211->current_network.HighestOperaRate && priv->FailTxRateCount < 2)
	{
		if(jiffies% (CurrRetryRate + 101) == 0)
		{
			bTryUp = true;
			priv->bTryuping = true;
			//printk("StaRateAdaptive87SE(): Randomly try upgrading...\n");
		}
	}

	//1 Rate Mechanism
	if(bTryUp)
	{
		priv->TryupingCount++;
		priv->TryDownCountLowData = 0;

		{
//			printk("UP: pHalData->TryupingCount = %d\n", priv->TryupingCount);
//			printk("UP: TryUpTh(%d)+ (FailTxRateCount(%d))^2 =%d\n",
//				TryUpTh, priv->FailTxRateCount, (TryUpTh + priv->FailTxRateCount * priv->FailTxRateCount) );
//			printk("UP: pHalData->bTryuping=%d\n",  priv->bTryuping);

		}

		//
		// Check more times if we need to upgrade indeed.
		// Because the largest value of pHalData->TryupingCount is 0xFFFF and
		// the largest value of pHalData->FailTxRateCount is 0x14,
		// this condition will be satisfied at most every 2 min.
		//

		if((priv->TryupingCount > (TryUpTh + priv->FailTxRateCount * priv->FailTxRateCount)) ||
			(CurrSignalStrength > priv->LastFailTxRateSS) || priv->bTryuping)
		{
			priv->TryupingCount = 0;
			//
			// When transfering from CCK to OFDM, DIG is an important issue.
			//
			if(priv->CurrentOperaRate == 22)
				bUpdateInitialGain = true;

			// The difference in throughput between 48Mbps and 36Mbps is 8M.
			// So, we must be carefully in this rate scale. Isaiah 2008-02-15.
			//
			if(  ((priv->CurrentOperaRate == 72) || (priv->CurrentOperaRate == 48) || (priv->CurrentOperaRate == 36)) &&
				(priv->FailTxRateCount > 2) )
				priv->RateAdaptivePeriod= (RATE_ADAPTIVE_TIMER_PERIOD/2);

			// (1)To avoid upgrade frequently to the fail tx rate, add the FailTxRateCount into the threshold.
			// (2)If the signal strength is increased, it may be able to upgrade.

			priv->CurrentOperaRate = GetUpgradeTxRate(dev, priv->CurrentOperaRate);
//			printk("StaRateAdaptive87SE(): Upgrade Tx Rate to %d\n", priv->CurrentOperaRate);

			//[TRC Dell Lab] Bypass 12/9/6, Isaiah 2008-02-18 20:00
			if(priv->CurrentOperaRate ==36)
			{
				priv->bUpdateARFR=true;
				write_nic_word(dev, ARFR, 0x0F8F); //bypass 12/9/6
//				printk("UP: ARFR=0xF8F\n");
			}
			else if(priv->bUpdateARFR)
			{
				priv->bUpdateARFR=false;
				write_nic_word(dev, ARFR, 0x0FFF); //set 1M ~ 54Mbps.
//				printk("UP: ARFR=0xFFF\n");
			}

			// Update Fail Tx rate and count.
			if(priv->LastFailTxRate != priv->CurrentOperaRate)
			{
				priv->LastFailTxRate = priv->CurrentOperaRate;
				priv->FailTxRateCount = 0;
				priv->LastFailTxRateSS = -200; // Set lowest power.
			}
		}
	}
	else
	{
		if(priv->TryupingCount > 0)
			priv->TryupingCount --;
	}

	if(bTryDown)
	{
		priv->TryDownCountLowData++;
		priv->TryupingCount = 0;
		{
//			printk("DN: pHalData->TryDownCountLowData = %d\n",priv->TryDownCountLowData);
//			printk("DN: TryDownTh =%d\n", TryDownTh);
//			printk("DN: pHalData->bTryuping=%d\n",  priv->bTryuping);
		}

		//Check if Tx rate can be degraded or Test trying upgrading should fallback.
		if(priv->TryDownCountLowData > TryDownTh || priv->bTryuping)
		{
			priv->TryDownCountLowData = 0;
			priv->bTryuping = false;
			// Update fail information.
			if(priv->LastFailTxRate == priv->CurrentOperaRate)
			{
				priv->FailTxRateCount ++;
				// Record the Tx fail rate signal strength.
				if(CurrSignalStrength > priv->LastFailTxRateSS)
				{
					priv->LastFailTxRateSS = CurrSignalStrength;
				}
			}
			else
			{
				priv->LastFailTxRate = priv->CurrentOperaRate;
				priv->FailTxRateCount = 1;
				priv->LastFailTxRateSS = CurrSignalStrength;
			}
			priv->CurrentOperaRate = GetDegradeTxRate(dev, priv->CurrentOperaRate);

			// Reduce chariot training time at weak signal strength situation. SD3 ED demand.
			//[TRC Dell Lab] Revise Signal Threshold from -75 to -80 , Isaiah 2008-02-18 20:00
			if( (CurrSignalStrength < -80) && (priv->CurrentOperaRate > 72 ))
			{
				priv->CurrentOperaRate = 72;
//				printk("DN: weak signal strength (%d), degrade to 36Mbps\n", CurrSignalStrength);
			}

			//[TRC Dell Lab] Bypass 12/9/6, Isaiah 2008-02-18 20:00
			if(priv->CurrentOperaRate ==36)
			{
				priv->bUpdateARFR=true;
				write_nic_word(dev, ARFR, 0x0F8F); //bypass 12/9/6
//				printk("DN: ARFR=0xF8F\n");
			}
			else if(priv->bUpdateARFR)
			{
				priv->bUpdateARFR=false;
				write_nic_word(dev, ARFR, 0x0FFF); //set 1M ~ 54Mbps.
//				printk("DN: ARFR=0xFFF\n");
			}

			//
			// When it is CCK rate, it may need to update initial gain to receive lower power packets.
			//
			if(MgntIsCckRate(priv->CurrentOperaRate))
			{
				bUpdateInitialGain = true;
			}
//			printk("StaRateAdaptive87SE(): Degrade Tx Rate to %d\n", priv->CurrentOperaRate);
		}
	}
	else
	{
		if(priv->TryDownCountLowData > 0)
			priv->TryDownCountLowData --;
	}

	// Keep the Tx fail rate count to equal to 0x15 at most.
	// Reduce the fail count at least to 10 sec if tx rate is tending stable.
	if(priv->FailTxRateCount >= 0x15 ||
		(!bTryUp && !bTryDown && priv->TryDownCountLowData == 0 && priv->TryupingCount && priv->FailTxRateCount > 0x6))
	{
		priv->FailTxRateCount --;
	}


	OfdmTxPwrIdx  = priv->chtxpwr_ofdm[priv->ieee80211->current_network.channel];
	CckTxPwrIdx  = priv->chtxpwr[priv->ieee80211->current_network.channel];

	//[TRC Dell Lab] Mac0x9e increase 2 level in 36M~18M situation, Isaiah 2008-02-18 24:00
	if((priv->CurrentOperaRate < 96) &&(priv->CurrentOperaRate > 22))
	{
		u1bCck = read_nic_byte(dev, CCK_TXAGC);
		u1bOfdm = read_nic_byte(dev, OFDM_TXAGC);

		// case 1: Never enter High power
		if(u1bCck == CckTxPwrIdx )
		{
			if(u1bOfdm != (OfdmTxPwrIdx+2) )
			{
			priv->bEnhanceTxPwr= true;
			u1bOfdm = ((u1bOfdm+2) > 35) ? 35: (u1bOfdm+2);
			write_nic_byte(dev, OFDM_TXAGC, u1bOfdm);
//			printk("Enhance OFDM_TXAGC : +++++ u1bOfdm= 0x%x\n", u1bOfdm);
			}
		}
		// case 2: enter high power
		else if(u1bCck < CckTxPwrIdx)
		{
			if(!priv->bEnhanceTxPwr)
			{
				priv->bEnhanceTxPwr= true;
				u1bOfdm = ((u1bOfdm+2) > 35) ? 35: (u1bOfdm+2);
				write_nic_byte(dev, OFDM_TXAGC, u1bOfdm);
				//RT_TRACE(COMP_RATE, DBG_TRACE, ("Enhance OFDM_TXAGC(2) : +++++ u1bOfdm= 0x%x\n", u1bOfdm));
			}
		}
	}
	else if(priv->bEnhanceTxPwr)  //54/48/11/5.5/2/1
	{
		u1bCck = read_nic_byte(dev, CCK_TXAGC);
		u1bOfdm = read_nic_byte(dev, OFDM_TXAGC);

		// case 1: Never enter High power
		if(u1bCck == CckTxPwrIdx )
		{
		priv->bEnhanceTxPwr= false;
		write_nic_byte(dev, OFDM_TXAGC, OfdmTxPwrIdx);
		//printk("Recover OFDM_TXAGC : ===== u1bOfdm= 0x%x\n", OfdmTxPwrIdx);
		}
		// case 2: enter high power
		else if(u1bCck < CckTxPwrIdx)
		{
			priv->bEnhanceTxPwr= false;
			u1bOfdm = ((u1bOfdm-2) > 0) ? (u1bOfdm-2): 0;
			write_nic_byte(dev, OFDM_TXAGC, u1bOfdm);
			//RT_TRACE(COMP_RATE, DBG_TRACE, ("Recover OFDM_TXAGC(2): ===== u1bOfdm= 0x%x\n", u1bOfdm));

		}
	}

	//
	// We need update initial gain when we set tx rate "from OFDM to CCK" or
	// "from CCK to OFDM".
	//
SetInitialGain:
	if(bUpdateInitialGain)
	{
		if(MgntIsCckRate(priv->CurrentOperaRate)) // CCK
		{
			if(priv->InitialGain > priv->RegBModeGainStage)
			{
				priv->InitialGainBackUp= priv->InitialGain;

				if(CurrSignalStrength < -85) // Low power, OFDM [0x17] = 26.
				{
					//SD3 SYs suggest that CurrSignalStrength < -65, ofdm 0x17=26.
					priv->InitialGain = priv->RegBModeGainStage;
				}
				else if(priv->InitialGain > priv->RegBModeGainStage + 1)
				{
					priv->InitialGain -= 2;
				}
				else
				{
					priv->InitialGain --;
				}
				printk("StaRateAdaptive87SE(): update init_gain to index %d for date rate %d\n",priv->InitialGain, priv->CurrentOperaRate);
				UpdateInitialGain(dev);
			}
		}
		else // OFDM
		{
			if(priv->InitialGain < 4)
			{
				priv->InitialGainBackUp= priv->InitialGain;

				priv->InitialGain ++;
				printk("StaRateAdaptive87SE(): update init_gain to index %d for date rate %d\n",priv->InitialGain, priv->CurrentOperaRate);
				UpdateInitialGain(dev);
			}
		}
	}

	//Record the related info
	priv->LastRetryRate = CurrRetryRate;
	priv->LastTxThroughput = TxThroughput;
	priv->ieee80211->rate = priv->CurrentOperaRate * 5;
}