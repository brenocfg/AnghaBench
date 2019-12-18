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
struct r8192_priv {scalar_t__ OFDM_index; scalar_t__ CCK_index; scalar_t__* ThermalMeter; scalar_t__ CurrentChannelBW; scalar_t__ txpower_count; void* bcck_in_ch14; TYPE_2__* ieee80211; void* btxpower_trackingInit; } ;
struct net_device {int dummy; } ;
struct TYPE_3__ {int channel; } ;
struct TYPE_4__ {TYPE_1__ current_network; } ;

/* Variables and functions */
 scalar_t__** CCKSwingTable_Ch1_Ch13 ; 
 int CCK_Table_length ; 
 int /*<<< orphan*/  COMP_POWER_TRACKING ; 
 void* FALSE ; 
 scalar_t__ HT_CHANNEL_WIDTH_20 ; 
 scalar_t__* OFDMSwingTable ; 
 int OFDM_Table_Length ; 
 int /*<<< orphan*/  RF90_PATH_A ; 
 int /*<<< orphan*/  RT_TRACE (int /*<<< orphan*/ ,char*,size_t,...) ; 
 void* TRUE ; 
 void* ThermalMeterVal ; 
 int /*<<< orphan*/  bMaskByte2 ; 
 int /*<<< orphan*/  bMaskDWord ; 
 int /*<<< orphan*/  dm_cck_txpower_adjust (struct net_device*,void*) ; 
 struct r8192_priv* ieee80211_priv (struct net_device*) ; 
 int /*<<< orphan*/  rCCK0_TxFilter1 ; 
 int /*<<< orphan*/  rOFDM0_XATxIQImbalance ; 
 scalar_t__ rtl8192_QueryBBReg (struct net_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ rtl8192_phy_QueryRFReg (struct net_device*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  rtl8192_setBBreg (struct net_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void dm_TXPowerTrackingCallback_ThermalMeter(struct net_device * dev)
{
#define ThermalMeterVal	9
	struct r8192_priv *priv = ieee80211_priv(dev);
	u32 tmpRegA, TempCCk;
	u8 tmpOFDMindex, tmpCCKindex, tmpCCK20Mindex, tmpCCK40Mindex, tmpval;
	int i =0, CCKSwingNeedUpdate=0;

	if(!priv->btxpower_trackingInit)
	{
		//Query OFDM default setting
		tmpRegA= rtl8192_QueryBBReg(dev, rOFDM0_XATxIQImbalance, bMaskDWord);
		for(i=0; i<OFDM_Table_Length; i++)	//find the index
		{
			if(tmpRegA == OFDMSwingTable[i])
			{
				priv->OFDM_index= (u8)i;
				RT_TRACE(COMP_POWER_TRACKING, "Initial reg0x%x = 0x%x, OFDM_index=0x%x\n",
					rOFDM0_XATxIQImbalance, tmpRegA, priv->OFDM_index);
			}
		}

		//Query CCK default setting From 0xa22
		TempCCk = rtl8192_QueryBBReg(dev, rCCK0_TxFilter1, bMaskByte2);
		for(i=0 ; i<CCK_Table_length ; i++)
		{
			if(TempCCk == (u32)CCKSwingTable_Ch1_Ch13[i][0])
			{
				priv->CCK_index =(u8) i;
				RT_TRACE(COMP_POWER_TRACKING, "Initial reg0x%x = 0x%x, CCK_index=0x%x\n",
					rCCK0_TxFilter1, TempCCk, priv->CCK_index);
				break;
			}
		}
		priv->btxpower_trackingInit = TRUE;
		//pHalData->TXPowercount = 0;
		return;
	}

	// read and filter out unreasonable value
	tmpRegA = rtl8192_phy_QueryRFReg(dev, RF90_PATH_A, 0x12, 0x078);	// 0x12: RF Reg[10:7]
	RT_TRACE(COMP_POWER_TRACKING, "Readback ThermalMeterA = %d \n", tmpRegA);
	if(tmpRegA < 3 || tmpRegA > 13)
		return;
	if(tmpRegA >= 12)	// if over 12, TP will be bad when high temprature
		tmpRegA = 12;
	RT_TRACE(COMP_POWER_TRACKING, "Valid ThermalMeterA = %d \n", tmpRegA);
	priv->ThermalMeter[0] = ThermalMeterVal;	//We use fixed value by Bryant's suggestion
	priv->ThermalMeter[1] = ThermalMeterVal;	//We use fixed value by Bryant's suggestion

	//Get current RF-A temprature index
	if(priv->ThermalMeter[0] >= (u8)tmpRegA)	//lower temprature
	{
		tmpOFDMindex = tmpCCK20Mindex = 6+(priv->ThermalMeter[0]-(u8)tmpRegA);
		tmpCCK40Mindex = tmpCCK20Mindex - 6;
		if(tmpOFDMindex >= OFDM_Table_Length)
			tmpOFDMindex = OFDM_Table_Length-1;
		if(tmpCCK20Mindex >= CCK_Table_length)
			tmpCCK20Mindex = CCK_Table_length-1;
		if(tmpCCK40Mindex >= CCK_Table_length)
			tmpCCK40Mindex = CCK_Table_length-1;
	}
	else
	{
		tmpval = ((u8)tmpRegA - priv->ThermalMeter[0]);
		if(tmpval >= 6)								// higher temprature
			tmpOFDMindex = tmpCCK20Mindex = 0;		// max to +6dB
		else
			tmpOFDMindex = tmpCCK20Mindex = 6 - tmpval;
		tmpCCK40Mindex = 0;
	}
	//DbgPrint("%ddb, tmpOFDMindex = %d, tmpCCK20Mindex = %d, tmpCCK40Mindex = %d",
		//((u1Byte)tmpRegA - pHalData->ThermalMeter[0]),
		//tmpOFDMindex, tmpCCK20Mindex, tmpCCK40Mindex);
	if(priv->CurrentChannelBW != HT_CHANNEL_WIDTH_20)	//40M
		tmpCCKindex = tmpCCK40Mindex;
	else
		tmpCCKindex = tmpCCK20Mindex;

	if(priv->ieee80211->current_network.channel == 14 && !priv->bcck_in_ch14)
	{
		priv->bcck_in_ch14 = TRUE;
		CCKSwingNeedUpdate = 1;
	}
	else if(priv->ieee80211->current_network.channel != 14 && priv->bcck_in_ch14)
	{
		priv->bcck_in_ch14 = FALSE;
		CCKSwingNeedUpdate = 1;
	}

	if(priv->CCK_index != tmpCCKindex)
	{
		priv->CCK_index = tmpCCKindex;
		CCKSwingNeedUpdate = 1;
	}

	if(CCKSwingNeedUpdate)
	{
		//DbgPrint("Update CCK Swing, CCK_index = %d\n", pHalData->CCK_index);
		dm_cck_txpower_adjust(dev, priv->bcck_in_ch14);
	}
	if(priv->OFDM_index != tmpOFDMindex)
	{
		priv->OFDM_index = tmpOFDMindex;
		rtl8192_setBBreg(dev, rOFDM0_XATxIQImbalance, bMaskDWord, OFDMSwingTable[priv->OFDM_index]);
		RT_TRACE(COMP_POWER_TRACKING, "Update OFDMSwing[%d] = 0x%x\n",
			priv->OFDM_index, OFDMSwingTable[priv->OFDM_index]);
	}
	priv->txpower_count = 0;
}