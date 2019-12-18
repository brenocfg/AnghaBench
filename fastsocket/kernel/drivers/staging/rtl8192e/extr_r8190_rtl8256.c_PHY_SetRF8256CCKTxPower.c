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
struct r8192_priv {int bDynamicTxLowPower; scalar_t__ CustomerID; int CckPwEnl; scalar_t__ rf_type; int RF_C_TxPwDiff; scalar_t__ CCKTxPowerLevelOriginalOffset; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CCK_TXAGC ; 
 scalar_t__ RF_2T4R ; 
 scalar_t__ RT_CID_819x_Netcore ; 
 int /*<<< orphan*/  bTxAGCRateCCK ; 
 struct r8192_priv* ieee80211_priv (struct net_device*) ; 
 int /*<<< orphan*/  rTxAGC_CCK_Mcs32 ; 
 int /*<<< orphan*/  rtl8192_setBBreg (struct net_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  write_nic_dword (struct net_device*,int /*<<< orphan*/ ,int) ; 

void PHY_SetRF8256CCKTxPower(struct net_device*	dev, u8	powerlevel)
{
	u32	TxAGC=0;
	struct r8192_priv *priv = ieee80211_priv(dev);
#ifdef RTL8190P
	u8				byte0, byte1;

	TxAGC |= ((powerlevel<<8)|powerlevel);
	TxAGC += priv->CCKTxPowerLevelOriginalOffset;

	if(priv->bDynamicTxLowPower == true  //cosa 04282008 for cck long range
		/*pMgntInfo->bScanInProgress == TRUE*/ ) //cosa 05/22/2008 for scan
	{
		if(priv->CustomerID == RT_CID_819x_Netcore)
			TxAGC = 0x2222;
		else
		TxAGC += ((priv->CckPwEnl<<8)|priv->CckPwEnl);
	}

	byte0 = (u8)(TxAGC & 0xff);
	byte1 = (u8)((TxAGC & 0xff00)>>8);
	if(byte0 > 0x24)
		byte0 = 0x24;
	if(byte1 > 0x24)
		byte1 = 0x24;
	if(priv->rf_type == RF_2T4R)	//Only 2T4R you have to care the Antenna Tx Power offset
	{	// check antenna C over the max index 0x24
			if(priv->RF_C_TxPwDiff > 0)
			{
				if( (byte0 + (u8)priv->RF_C_TxPwDiff) > 0x24)
					byte0 = 0x24 - priv->RF_C_TxPwDiff;
				if( (byte1 + (u8)priv->RF_C_TxPwDiff) > 0x24)
					byte1 = 0x24 - priv->RF_C_TxPwDiff;
			}
		}
	TxAGC = (byte1<<8) |byte0;
	write_nic_dword(dev, CCK_TXAGC, TxAGC);
#else
	#ifdef RTL8192E

	TxAGC = powerlevel;
	if(priv->bDynamicTxLowPower == true)//cosa 04282008 for cck long range
	{
		if(priv->CustomerID == RT_CID_819x_Netcore)
		TxAGC = 0x22;
	else
		TxAGC += priv->CckPwEnl;
	}
	if(TxAGC > 0x24)
		TxAGC = 0x24;
	rtl8192_setBBreg(dev, rTxAGC_CCK_Mcs32, bTxAGCRateCCK, TxAGC);
	#endif
#endif
}