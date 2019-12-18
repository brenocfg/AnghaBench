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
typedef  int u32 ;
struct r8192_priv {scalar_t__ rf_chip; int* RfReg0Value; scalar_t__ rf_type; TYPE_1__* PHYRegDef; } ;
struct net_device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  rf3wireOffset; } ;
typedef  size_t RF90_RADIO_PATH_E ;
typedef  TYPE_1__ BB_REGISTER_DEFINITION_T ;

/* Variables and functions */
 int COMP_ERR ; 
 int COMP_PHY ; 
 scalar_t__ RF_1T2R ; 
 scalar_t__ RF_2T4R ; 
 scalar_t__ RF_8256 ; 
 int /*<<< orphan*/  RT_TRACE (int,char*) ; 
 int bMaskDWord ; 
 struct r8192_priv* ieee80211_priv (struct net_device*) ; 
 int /*<<< orphan*/  rFPGA0_AnalogParameter4 ; 
 int /*<<< orphan*/  rtl8192_setBBreg (struct net_device*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void rtl8192_phy_RFSerialWrite(struct net_device* dev, RF90_RADIO_PATH_E eRFPath, u32 Offset, u32 Data)
{
	struct r8192_priv *priv = ieee80211_priv(dev);
	u32 DataAndAddr = 0, NewOffset = 0;
	BB_REGISTER_DEFINITION_T	*pPhyReg = &priv->PHYRegDef[eRFPath];

	Offset &= 0x3f;
	if (priv->rf_chip == RF_8256)
	{

#ifdef RTL8190P
		//analog to digital off, for protection
		rtl8192_setBBreg(dev, rFPGA0_AnalogParameter4, 0xf00, 0x0);// 0x88c[11:8]
#else
	#ifdef RTL8192E
		//analog to digital off, for protection
		rtl8192_setBBreg(dev, rFPGA0_AnalogParameter4, 0xf00, 0x0);// 0x88c[11:8]
	#endif
#endif

		if (Offset >= 31)
		{
			priv->RfReg0Value[eRFPath] |= 0x140;
			rtl8192_setBBreg(dev, pPhyReg->rf3wireOffset, bMaskDWord, (priv->RfReg0Value[eRFPath] << 16));
			NewOffset = Offset - 30;
		}
		else if (Offset >= 16)
		{
			priv->RfReg0Value[eRFPath] |= 0x100;
			priv->RfReg0Value[eRFPath] &= (~0x40);
			rtl8192_setBBreg(dev, pPhyReg->rf3wireOffset, bMaskDWord, (priv->RfReg0Value[eRFPath]<<16));
			NewOffset = Offset - 15;
		}
		else
			NewOffset = Offset;
	}
	else
	{
		RT_TRACE((COMP_PHY|COMP_ERR), "check RF type here, need to be 8256\n");
		NewOffset = Offset;
	}

	// Put write addr in [5:0]  and write data in [31:16]
	DataAndAddr = (Data<<16) | (NewOffset&0x3f);

	// Write Operation
	rtl8192_setBBreg(dev, pPhyReg->rf3wireOffset, bMaskDWord, DataAndAddr);


	if(Offset==0x0)
		priv->RfReg0Value[eRFPath] = Data;

	// Switch back to Reg_Mode0;
 	if(priv->rf_chip == RF_8256)
	{
		if(Offset != 0)
		{
			priv->RfReg0Value[eRFPath] &= 0xebf;
			rtl8192_setBBreg(
				dev,
				pPhyReg->rf3wireOffset,
				bMaskDWord,
				(priv->RfReg0Value[eRFPath] << 16));
		}
#ifdef RTL8190P
		if(priv->rf_type == RF_2T4R)
		{
			//analog to digital on
			rtl8192_setBBreg(dev, rFPGA0_AnalogParameter4, 0xf00, 0xf);// 0x88c[11:8]
		}
		else if(priv->rf_type == RF_1T2R)
		{
			//analog to digital on
			rtl8192_setBBreg(dev, rFPGA0_AnalogParameter4, 0xc00, 0x3);// 0x88c[11:10]
		}
#else
	#ifdef RTL8192E
		//analog to digital on
		rtl8192_setBBreg(dev, rFPGA0_AnalogParameter4, 0x300, 0x3);// 0x88c[9:8]
	#endif
#endif
	}

	return;
}