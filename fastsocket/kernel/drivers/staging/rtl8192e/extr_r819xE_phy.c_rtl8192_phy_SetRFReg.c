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
struct r8192_priv {scalar_t__ Rf_Mode; int /*<<< orphan*/  being_init_adapter; TYPE_1__* ieee80211; } ;
struct net_device {int dummy; } ;
struct TYPE_2__ {scalar_t__ eRFPowerState; } ;
typedef  int /*<<< orphan*/  RF90_RADIO_PATH_E ;
typedef  int Original_Value ;

/* Variables and functions */
 int /*<<< orphan*/  COMP_PHY ; 
 scalar_t__ RF_OP_By_FW ; 
 int /*<<< orphan*/  RT_TRACE (int /*<<< orphan*/ ,char*) ; 
 int bMask12Bits ; 
 scalar_t__ eRfOn ; 
 struct r8192_priv* ieee80211_priv (struct net_device*) ; 
 int phy_FwRFSerialRead (struct net_device*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  phy_FwRFSerialWrite (struct net_device*,int /*<<< orphan*/ ,int,int) ; 
 int rtl8192_CalculateBitShift (int) ; 
 int /*<<< orphan*/  rtl8192_phy_CheckIsLegalRFPath (struct net_device*,int /*<<< orphan*/ ) ; 
 int rtl8192_phy_RFSerialRead (struct net_device*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rtl8192_phy_RFSerialWrite (struct net_device*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  udelay (int) ; 

void rtl8192_phy_SetRFReg(struct net_device* dev, RF90_RADIO_PATH_E eRFPath, u32 RegAddr, u32 BitMask, u32 Data)
{
	struct r8192_priv *priv = ieee80211_priv(dev);
	u32 Original_Value, BitShift, New_Value;
//	u8	time = 0;

	if (!rtl8192_phy_CheckIsLegalRFPath(dev, eRFPath))
		return;
#ifdef RTL8192E
	if(priv->ieee80211->eRFPowerState != eRfOn && !priv->being_init_adapter)
		return;
#endif
	//spin_lock_irqsave(&priv->rf_lock, flags);
	//down(&priv->rf_sem);

	RT_TRACE(COMP_PHY, "FW RF CTRL is not ready now\n");
	if (priv->Rf_Mode == RF_OP_By_FW)
	{
		if (BitMask != bMask12Bits) // RF data is 12 bits only
		{
			Original_Value = phy_FwRFSerialRead(dev, eRFPath, RegAddr);
			BitShift =  rtl8192_CalculateBitShift(BitMask);
			New_Value = (((Original_Value) & (~BitMask)) | (Data<< BitShift));

			phy_FwRFSerialWrite(dev, eRFPath, RegAddr, New_Value);
		}else
			phy_FwRFSerialWrite(dev, eRFPath, RegAddr, Data);
		udelay(200);

	}
	else
	{
		if (BitMask != bMask12Bits) // RF data is 12 bits only
   	        {
			Original_Value = rtl8192_phy_RFSerialRead(dev, eRFPath, RegAddr);
      			BitShift =  rtl8192_CalculateBitShift(BitMask);
      			New_Value = (((Original_Value) & (~BitMask)) | (Data<< BitShift));

			rtl8192_phy_RFSerialWrite(dev, eRFPath, RegAddr, New_Value);
	        }else
			rtl8192_phy_RFSerialWrite(dev, eRFPath, RegAddr, Data);
	}
	//spin_unlock_irqrestore(&priv->rf_lock, flags);
	//up(&priv->rf_sem);
	return;
}