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
struct r8192_priv {int bChangeBBInProgress; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  COMP_RF ; 
 int HST_RDBUSY ; 
 int /*<<< orphan*/  PHY_REG ; 
 int PHY_REG_DATA ; 
 int /*<<< orphan*/  RT_TRACE (int /*<<< orphan*/ ,char*,int,...) ; 
 struct r8192_priv* ieee80211_priv (struct net_device*) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int read_nic_byte (struct net_device*,int /*<<< orphan*/ ) ; 
 int read_nic_dword (struct net_device*,int) ; 

u32 phy_QueryUsbBBReg(struct net_device* dev, u32	RegAddr)
{
	struct r8192_priv *priv = ieee80211_priv(dev);
	u32	ReturnValue = 0xffffffff;
	u8	PollingCnt = 50;
	u8	BBWaitCounter = 0;


	//
	// <Roger_Notes> Due to PASSIVE_LEVEL, so we ONLY simply busy waiting for a while here.
	// We have to make sure that previous BB I/O has been done.
	// 2008.08.20.
	//
	while(priv->bChangeBBInProgress)
	{
		BBWaitCounter ++;
		RT_TRACE(COMP_RF, "phy_QueryUsbBBReg(): Wait 1 ms (%d times)...\n", BBWaitCounter);
		msleep(1); // 1 ms

		// Wait too long, return FALSE to avoid to be stuck here.
		if((BBWaitCounter > 100) )//||RT_USB_CANNOT_IO(Adapter))
		{
			RT_TRACE(COMP_RF, "phy_QueryUsbBBReg(): (%d) Wait too logn to query BB!!\n", BBWaitCounter);
			return ReturnValue;
		}
	}

	priv->bChangeBBInProgress = true;

	read_nic_dword(dev, RegAddr);

	do
	{// Make sure that access could be done.
		if((read_nic_byte(dev, PHY_REG)&HST_RDBUSY) == 0)
			break;
	}while( --PollingCnt );

	if(PollingCnt == 0)
	{
		RT_TRACE(COMP_RF, "Fail!!!phy_QueryUsbBBReg(): RegAddr(%#x) = %#x\n", RegAddr, ReturnValue);
	}
	else
	{
		// Data FW read back.
		ReturnValue = read_nic_dword(dev, PHY_REG_DATA);
		RT_TRACE(COMP_RF, "phy_QueryUsbBBReg(): RegAddr(%#x) = %#x, PollingCnt(%d)\n", RegAddr, ReturnValue, PollingCnt);
	}

	priv->bChangeBBInProgress = false;

	return ReturnValue;
}