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
typedef  int u32 ;
typedef  int u16 ;
struct r8192_priv {int bDynamicTxHighPower; int* MCSTxPowerLevelOriginalOffset; scalar_t__ rf_type; int RF_C_TxPwDiff; int Pwr_Track; int LegacyHTTxPowerDiff; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 scalar_t__ MCS_TXAGC ; 
 scalar_t__ RF_2T4R ; 
 struct r8192_priv* ieee80211_priv (struct net_device*) ; 
 int /*<<< orphan*/  rtl8192_setBBreg (struct net_device*,int,int,int) ; 
 int /*<<< orphan*/  write_nic_dword (struct net_device*,scalar_t__,int) ; 

void PHY_SetRF8256OFDMTxPower(struct net_device* dev, u8 powerlevel)
{
	struct r8192_priv *priv = ieee80211_priv(dev);
	//Joseph TxPower for 8192 testing
#ifdef RTL8190P
	u32				TxAGC1=0, TxAGC2=0, TxAGC2_tmp = 0;
	u8				i, byteVal1[4], byteVal2[4], byteVal3[4];

	if(priv->bDynamicTxHighPower == true)     //Add by Jacken 2008/03/06
	{
		TxAGC1 |= ((powerlevel<<24)|(powerlevel<<16)|(powerlevel<<8)|powerlevel);
		//for tx power track
		TxAGC2_tmp = TxAGC1;

		TxAGC1 += priv->MCSTxPowerLevelOriginalOffset[0];
		TxAGC2 =0x03030303;

		//for tx power track
		TxAGC2_tmp += priv->MCSTxPowerLevelOriginalOffset[1];
	}
	else
	{
		TxAGC1 |= ((powerlevel<<24)|(powerlevel<<16)|(powerlevel<<8)|powerlevel);
		TxAGC2 = TxAGC1;

		TxAGC1 += priv->MCSTxPowerLevelOriginalOffset[0];
		TxAGC2 += priv->MCSTxPowerLevelOriginalOffset[1];

		TxAGC2_tmp = TxAGC2;

	}
	for(i=0; i<4; i++)
	{
		byteVal1[i] = (u8)(  (TxAGC1 & (0xff<<(i*8))) >>(i*8) );
		if(byteVal1[i] > 0x24)
			byteVal1[i] = 0x24;
		byteVal2[i] = (u8)(  (TxAGC2 & (0xff<<(i*8))) >>(i*8) );
		if(byteVal2[i] > 0x24)
			byteVal2[i] = 0x24;

		//for tx power track
		byteVal3[i] = (u8)(  (TxAGC2_tmp & (0xff<<(i*8))) >>(i*8) );
		if(byteVal3[i] > 0x24)
			byteVal3[i] = 0x24;
	}

	if(priv->rf_type == RF_2T4R)	//Only 2T4R you have to care the Antenna Tx Power offset
	{	// check antenna C over the max index 0x24
		if(priv->RF_C_TxPwDiff > 0)
		{
			for(i=0; i<4; i++)
			{
				if( (byteVal1[i] + (u8)priv->RF_C_TxPwDiff) > 0x24)
					byteVal1[i] = 0x24 - priv->RF_C_TxPwDiff;
				if( (byteVal2[i] + (u8)priv->RF_C_TxPwDiff) > 0x24)
					byteVal2[i] = 0x24 - priv->RF_C_TxPwDiff;
				if( (byteVal3[i] + (u8)priv->RF_C_TxPwDiff) > 0x24)
					byteVal3[i] = 0x24 - priv->RF_C_TxPwDiff;
			}
		}
	}

	TxAGC1 = (byteVal1[3]<<24) | (byteVal1[2]<<16) |(byteVal1[1]<<8) |byteVal1[0];
	TxAGC2 = (byteVal2[3]<<24) | (byteVal2[2]<<16) |(byteVal2[1]<<8) |byteVal2[0];

	//for tx power track
	TxAGC2_tmp = (byteVal3[3]<<24) | (byteVal3[2]<<16) |(byteVal3[1]<<8) |byteVal3[0];
	priv->Pwr_Track = TxAGC2_tmp;
	//DbgPrint("TxAGC2_tmp = 0x%x\n", TxAGC2_tmp);

	//DbgPrint("TxAGC1/TxAGC2 = 0x%x/0x%x\n", TxAGC1, TxAGC2);
	write_nic_dword(dev, MCS_TXAGC, TxAGC1);
	write_nic_dword(dev, MCS_TXAGC+4, TxAGC2);
#else
#ifdef RTL8192E
	u32 writeVal, powerBase0, powerBase1, writeVal_tmp;
	u8 index = 0;
	u16 RegOffset[6] = {0xe00, 0xe04, 0xe10, 0xe14, 0xe18, 0xe1c};
	u8 byte0, byte1, byte2, byte3;

	powerBase0 = powerlevel + priv->LegacyHTTxPowerDiff;	//OFDM rates
	powerBase0 = (powerBase0<<24) | (powerBase0<<16) |(powerBase0<<8) |powerBase0;
	powerBase1 = powerlevel;							//MCS rates
	powerBase1 = (powerBase1<<24) | (powerBase1<<16) |(powerBase1<<8) |powerBase1;

	for(index=0; index<6; index++)
	{
		writeVal = priv->MCSTxPowerLevelOriginalOffset[index] + ((index<2)?powerBase0:powerBase1);
		byte0 = (u8)(writeVal & 0x7f);
		byte1 = (u8)((writeVal & 0x7f00)>>8);
		byte2 = (u8)((writeVal & 0x7f0000)>>16);
		byte3 = (u8)((writeVal & 0x7f000000)>>24);
		if(byte0 > 0x24)	// Max power index = 0x24
			byte0 = 0x24;
		if(byte1 > 0x24)
			byte1 = 0x24;
		if(byte2 > 0x24)
			byte2 = 0x24;
		if(byte3 > 0x24)
			byte3 = 0x24;

		if(index == 3)
		{
			writeVal_tmp = (byte3<<24) | (byte2<<16) |(byte1<<8) |byte0;
			priv->Pwr_Track = writeVal_tmp;
		}

		if(priv->bDynamicTxHighPower == true)     //Add by Jacken 2008/03/06  //when DM implement, add this
		{
			writeVal = 0x03030303;
		}
		else
		{
			writeVal = (byte3<<24) | (byte2<<16) |(byte1<<8) |byte0;
		}
		rtl8192_setBBreg(dev, RegOffset[index], 0x7f7f7f7f, writeVal);
	}

#endif
#endif
	return;
}