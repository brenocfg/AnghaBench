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
struct r8192_priv {int txpower_count; int /*<<< orphan*/  txpower_tracking_wq; int /*<<< orphan*/  priv_wq; int /*<<< orphan*/  btxpower_tracking; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  RF90_PATH_A ; 
 int /*<<< orphan*/  bRFRegOffsetMask ; 
 struct r8192_priv* ieee80211_priv (struct net_device*) ; 
 int /*<<< orphan*/  queue_delayed_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtl8192_phy_SetRFReg (struct net_device*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void dm_CheckTXPowerTracking_ThermalMeter(struct net_device *dev)
{
	struct r8192_priv *priv = ieee80211_priv(dev);
	static u8 	TM_Trigger=0;

	//DbgPrint("dm_CheckTXPowerTracking() \n");
	if(!priv->btxpower_tracking)
		return;
	else
	{
		if(priv->txpower_count  <= 2)
		{
			priv->txpower_count++;
			return;
		}
	}

	if(!TM_Trigger)
	{
		//Attention!! You have to wirte all 12bits data to RF, or it may cause RF to crash
		//actually write reg0x02 bit1=0, then bit1=1.
		//DbgPrint("Trigger ThermalMeter, write RF reg0x2 = 0x4d to 0x4f\n");
		rtl8192_phy_SetRFReg(dev, RF90_PATH_A, 0x02, bRFRegOffsetMask, 0x4d);
		rtl8192_phy_SetRFReg(dev, RF90_PATH_A, 0x02, bRFRegOffsetMask, 0x4f);
		rtl8192_phy_SetRFReg(dev, RF90_PATH_A, 0x02, bRFRegOffsetMask, 0x4d);
		rtl8192_phy_SetRFReg(dev, RF90_PATH_A, 0x02, bRFRegOffsetMask, 0x4f);
		TM_Trigger = 1;
		return;
	}
	else
	{
		//DbgPrint("Schedule TxPowerTrackingWorkItem\n");
			queue_delayed_work(priv->priv_wq,&priv->txpower_tracking_wq,0);
		TM_Trigger = 0;
	}
}