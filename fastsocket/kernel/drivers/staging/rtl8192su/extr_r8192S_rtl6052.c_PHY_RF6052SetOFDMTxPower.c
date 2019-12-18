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
typedef  int u8 ;
typedef  int u32 ;
typedef  int u16 ;
struct r8192_priv {int EEPROMVersion; int LegacyHTTxPowerDiff; int** TxPwrLegacyHtDiff; int TxPwrbandEdgeFlag; int** TxPwrbandEdgeLegacyOfdm; scalar_t__ CurrentChannelBW; int** TxPwrHt20Diff; int** TxPwrbandEdgeHt40; int** TxPwrbandEdgeHt20; int* MCSTxPowerLevelOriginalOffset; scalar_t__ rf_type; int* AntennaTxPwDiff; scalar_t__ bDynamicTxHighPower; scalar_t__ bIgnoreDiffRateTxPowerOffset; TYPE_2__* ieee80211; } ;
struct net_device {int dummy; } ;
struct TYPE_3__ {int channel; } ;
struct TYPE_4__ {TYPE_1__ current_network; } ;

/* Variables and functions */
 scalar_t__ HT_CHANNEL_WIDTH_20 ; 
 scalar_t__ HT_CHANNEL_WIDTH_20_40 ; 
 int RF6052_MAX_TX_PWR ; 
 size_t RF90_PATH_A ; 
 scalar_t__ RF_2T2R ; 
 scalar_t__ TRUE ; 
 struct r8192_priv* ieee80211_priv (struct net_device*) ; 
 int /*<<< orphan*/  rtl8192_setBBreg (struct net_device*,int,int,int) ; 

extern void PHY_RF6052SetOFDMTxPower(struct net_device* dev, u8 powerlevel)
{
	struct r8192_priv *priv = ieee80211_priv(dev);
	u32 	writeVal, powerBase0, powerBase1;
	u8 	index = 0;
	u16 	RegOffset[6] = {0xe00, 0xe04, 0xe10, 0xe14, 0xe18, 0xe1c};
	//u8 	byte0, byte1, byte2, byte3;
	u8    Channel = priv->ieee80211->current_network.channel;
	u8	rfa_pwr[4];
	u8	rfa_lower_bound = 0, rfa_upper_bound = 0 /*, rfa_htpwr, rfa_legacypwr*/;
	u8	i;
	u8	rf_pwr_diff = 0;
	u8	Legacy_pwrdiff=0, HT20_pwrdiff=0, BandEdge_Pwrdiff=0;
	u8	ofdm_bandedge_chnl_low=0, ofdm_bandedge_chnl_high=0;


	// We only care about the path A for legacy.
	if (priv->EEPROMVersion != 2)
	powerBase0 = powerlevel + (priv->LegacyHTTxPowerDiff & 0xf);
	else if (priv->EEPROMVersion == 2)	// Defined by SD1 Jong
	{
		//
		// 2009/01/21 MH Support new EEPROM format from SD3 requirement
		//
		Legacy_pwrdiff = priv->TxPwrLegacyHtDiff[RF90_PATH_A][Channel-1];
		// For legacy OFDM, tx pwr always > HT OFDM pwr. We do not care Path B
		// legacy OFDM pwr diff. NO BB register to notify HW.
		powerBase0 = powerlevel + Legacy_pwrdiff;
		//RTPRINT(FPHY, PHY_TXPWR, (" [LagacyToHT40 pwr diff = %d]\n", Legacy_pwrdiff));

		// Band Edge scheme is enabled for FCC mode
		if (priv->TxPwrbandEdgeFlag == 1/* && pHalData->ChannelPlan == 0*/)
		{
			ofdm_bandedge_chnl_low = 1;
			ofdm_bandedge_chnl_high = 11;
			BandEdge_Pwrdiff = 0;
			if (Channel <= ofdm_bandedge_chnl_low)
				BandEdge_Pwrdiff = priv->TxPwrbandEdgeLegacyOfdm[RF90_PATH_A][0];
			else if (Channel >= ofdm_bandedge_chnl_high)
			{
				BandEdge_Pwrdiff = priv->TxPwrbandEdgeLegacyOfdm[RF90_PATH_A][1];
			}
			powerBase0 -= BandEdge_Pwrdiff;
			if (Channel <= ofdm_bandedge_chnl_low || Channel >= ofdm_bandedge_chnl_high)
			{
				//RTPRINT(FPHY, PHY_TXPWR, (" [OFDM band-edge channel = %d, pwr diff = %d]\n",
				//Channel, BandEdge_Pwrdiff));
			}
		}
		//RTPRINT(FPHY, PHY_TXPWR, (" [OFDM power base index = 0x%x]\n", powerBase0));
	}
	powerBase0 = (powerBase0<<24) | (powerBase0<<16) |(powerBase0<<8) |powerBase0;

	//MCS rates
	if(priv->EEPROMVersion == 2)
	{
		//Cosa add for new EEPROM content. 02102009

		//Check HT20 to HT40 diff
		if (priv->CurrentChannelBW == HT_CHANNEL_WIDTH_20)
		{
			// HT 20<->40 pwr diff
			HT20_pwrdiff = priv->TxPwrHt20Diff[RF90_PATH_A][Channel-1];

			// Calculate Antenna pwr diff
			if (HT20_pwrdiff < 8)	// 0~+7
				powerlevel += HT20_pwrdiff;
			else				// index8-15=-8~-1
				powerlevel -= (16-HT20_pwrdiff);

			//RTPRINT(FPHY, PHY_TXPWR, (" [HT20 to HT40 pwrdiff = %d]\n", HT20_pwrdiff));
			//RTPRINT(FPHY, PHY_TXPWR, (" [MCS power base index = 0x%x]\n", powerlevel));
		}

		// Band Edge scheme is enabled for FCC mode
		if (priv->TxPwrbandEdgeFlag == 1/* && pHalData->ChannelPlan == 0*/)
		{
			BandEdge_Pwrdiff = 0;
			if (priv->CurrentChannelBW == HT_CHANNEL_WIDTH_20_40)
			{
				if (Channel <= 3)
					BandEdge_Pwrdiff = priv->TxPwrbandEdgeHt40[RF90_PATH_A][0];
				else if (Channel >= 9)
					BandEdge_Pwrdiff = priv->TxPwrbandEdgeHt40[RF90_PATH_A][1];
				if (Channel <= 3 || Channel >= 9)
				{
					//RTPRINT(FPHY, PHY_TXPWR, (" [HT40 band-edge channel = %d, pwr diff = %d]\n",
					//Channel, BandEdge_Pwrdiff));
				}
			}
			else if (priv->CurrentChannelBW == HT_CHANNEL_WIDTH_20)
			{
				if (Channel <= 1)
					BandEdge_Pwrdiff = priv->TxPwrbandEdgeHt20[RF90_PATH_A][0];
				else if (Channel >= 11)
					BandEdge_Pwrdiff = priv->TxPwrbandEdgeHt20[RF90_PATH_A][1];
				if (Channel <= 1 || Channel >= 11)
				{
					//RTPRINT(FPHY, PHY_TXPWR, (" [HT20 band-edge channel = %d, pwr diff = %d]\n",
					//Channel, BandEdge_Pwrdiff));
				}
			}
			powerlevel -= BandEdge_Pwrdiff;
			//RTPRINT(FPHY, PHY_TXPWR, (" [MCS power base index = 0x%x]\n", powerlevel));
		}
	}
	powerBase1 = powerlevel;
	powerBase1 = (powerBase1<<24) | (powerBase1<<16) |(powerBase1<<8) |powerBase1;

	//RTPRINT(FPHY, PHY_TXPWR, (" [Legacy/HT power index= %x/%x]\n", powerBase0, powerBase1));

	for(index=0; index<6; index++)
	{
		//
		// Index 0 & 1= legacy OFDM, 2-5=HT_MCS rate
		//
		//cosa add for lenovo, to pass the safety spec, don't increase power index for different rates.
		if(priv->bIgnoreDiffRateTxPowerOffset)
			writeVal = ((index<2)?powerBase0:powerBase1);
		else
		writeVal = priv->MCSTxPowerLevelOriginalOffset[index] + ((index<2)?powerBase0:powerBase1);

		//RTPRINT(FPHY, PHY_TXPWR, ("Reg 0x%x, Original=%x writeVal=%x\n",
		//RegOffset[index], priv->MCSTxPowerLevelOriginalOffset[index], writeVal));

		//
		// If path A and Path B coexist, we must limit Path A tx power.
		// Protect Path B pwr over or under flow. We need to calculate upper and
		// lower bound of path A tx power.
		//
		if (priv->rf_type == RF_2T2R)
		{
			rf_pwr_diff = priv->AntennaTxPwDiff[0];
			//RTPRINT(FPHY, PHY_TXPWR, ("2T2R RF-B to RF-A PWR DIFF=%d\n", rf_pwr_diff));

			if (rf_pwr_diff >= 8)		// Diff=-8~-1
			{	// Prevent underflow!!
				rfa_lower_bound = 0x10-rf_pwr_diff;
				//RTPRINT(FPHY, PHY_TXPWR, ("rfa_lower_bound= %d\n", rfa_lower_bound));
			}
			else if (rf_pwr_diff >= 0)	// Diff = 0-7
			{
				rfa_upper_bound = RF6052_MAX_TX_PWR-rf_pwr_diff;
				//RTPRINT(FPHY, PHY_TXPWR, ("rfa_upper_bound= %d\n", rfa_upper_bound));
			}
		}

		for (i=  0; i <4; i++)
		{
			rfa_pwr[i] = (u8)((writeVal & (0x7f<<(i*8)))>>(i*8));
			if (rfa_pwr[i]  > RF6052_MAX_TX_PWR)
				rfa_pwr[i]  = RF6052_MAX_TX_PWR;

			//
			// If path A and Path B coexist, we must limit Path A tx power.
			// Protect Path B pwr over or under flow. We need to calculate upper and
			// lower bound of path A tx power.
			//
			if (priv->rf_type == RF_2T2R)
			{
				if (rf_pwr_diff >= 8)		// Diff=-8~-1
				{	// Prevent underflow!!
					if (rfa_pwr[i] <rfa_lower_bound)
					{
						//RTPRINT(FPHY, PHY_TXPWR, ("Underflow"));
						rfa_pwr[i] = rfa_lower_bound;
					}
				}
				else if (rf_pwr_diff >= 1)	// Diff = 0-7
				{	// Prevent overflow
					if (rfa_pwr[i] > rfa_upper_bound)
					{
						//RTPRINT(FPHY, PHY_TXPWR, ("Overflow"));
						rfa_pwr[i] = rfa_upper_bound;
					}
				}
				//RTPRINT(FPHY, PHY_TXPWR, ("rfa_pwr[%d]=%x\n", i, rfa_pwr[i]));
			}

		}

		//
		// Add description: PWDB > threshold!!!High power issue!!
		// We must decrease tx power !! Why is the value ???
		//
		if(priv->bDynamicTxHighPower == TRUE)
		{
			// For MCS rate
			if(index > 1)
			{
				writeVal = 0x03030303;
			}
			// For Legacy rate
			else
			{
				writeVal = (rfa_pwr[3]<<24) | (rfa_pwr[2]<<16) |(rfa_pwr[1]<<8) |rfa_pwr[0];
			}
			//RTPRINT(FPHY, PHY_TXPWR, ("HighPower=%08x\n", writeVal));
		}
		else
		{
			writeVal = (rfa_pwr[3]<<24) | (rfa_pwr[2]<<16) |(rfa_pwr[1]<<8) |rfa_pwr[0];
			//RTPRINT(FPHY, PHY_TXPWR, ("NormalPower=%08x\n", writeVal));
		}

		//
		// Write different rate set tx power index.
		//
		//if (DCMD_Test_Flag == 0)
		rtl8192_setBBreg(dev, RegOffset[index], 0x7f7f7f7f, writeVal);
	}

}