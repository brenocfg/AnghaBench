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
struct r8192_priv {scalar_t__ Rf_Mode; int /*<<< orphan*/  rf_sem; int /*<<< orphan*/  being_init_adapter; TYPE_1__* ieee80211; } ;
struct net_device {int dummy; } ;
struct TYPE_2__ {scalar_t__ eRFPowerState; } ;
typedef  int /*<<< orphan*/  RF90_RADIO_PATH_E ;

/* Variables and functions */
 scalar_t__ RF_OP_By_FW ; 
 int /*<<< orphan*/  down (int /*<<< orphan*/ *) ; 
 scalar_t__ eRfOn ; 
 struct r8192_priv* ieee80211_priv (struct net_device*) ; 
 int phy_FwRFSerialRead (struct net_device*,int /*<<< orphan*/ ,int) ; 
 int rtl8192_CalculateBitShift (int) ; 
 int /*<<< orphan*/  rtl8192_phy_CheckIsLegalRFPath (struct net_device*,int /*<<< orphan*/ ) ; 
 int rtl8192_phy_RFSerialRead (struct net_device*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  udelay (int) ; 
 int /*<<< orphan*/  up (int /*<<< orphan*/ *) ; 

u32 rtl8192_phy_QueryRFReg(struct net_device* dev, RF90_RADIO_PATH_E eRFPath, u32 RegAddr, u32 BitMask)
{
	u32 Original_Value, Readback_Value, BitShift;
	struct r8192_priv *priv = ieee80211_priv(dev);
	if (!rtl8192_phy_CheckIsLegalRFPath(dev, eRFPath))
		return 0;
#ifdef RTL8192E
	if(priv->ieee80211->eRFPowerState != eRfOn && !priv->being_init_adapter)
		return	0;
#endif
	down(&priv->rf_sem);
	if (priv->Rf_Mode == RF_OP_By_FW)
	{
		Original_Value = phy_FwRFSerialRead(dev, eRFPath, RegAddr);
		udelay(200);
	}
	else
	{
		Original_Value = rtl8192_phy_RFSerialRead(dev, eRFPath, RegAddr);

	}
	BitShift =  rtl8192_CalculateBitShift(BitMask);
   	Readback_Value = (Original_Value & BitMask) >> BitShift;
	up(&priv->rf_sem);
//	udelay(200);
	return (Readback_Value);
}