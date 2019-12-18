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
struct r8192_priv {int bChangeRFInProgress; int /*<<< orphan*/  rf_sem; } ;
struct net_device {int dummy; } ;
typedef  int RF90_RADIO_PATH_E ;

/* Variables and functions */
 int /*<<< orphan*/  COMP_RF ; 
 int /*<<< orphan*/  RF_BB_CMD_ADDR ; 
 int /*<<< orphan*/  RF_BB_CMD_DATA ; 
 int /*<<< orphan*/  RT_TRACE (int /*<<< orphan*/ ,char*,int,...) ; 
 int /*<<< orphan*/  down (int /*<<< orphan*/ *) ; 
 struct r8192_priv* ieee80211_priv (struct net_device*) ; 
 int /*<<< orphan*/  msleep (int) ; 
 scalar_t__ read_nic_dword (struct net_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  up (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_nic_dword (struct net_device*,int /*<<< orphan*/ ,int) ; 

u32 phy_QueryUsbRFReg(	struct net_device* dev, RF90_RADIO_PATH_E eRFPath,	u32	Offset)
{

	struct r8192_priv *priv = ieee80211_priv(dev);
	//u32	value  = 0, ReturnValue = 0;
	u32	ReturnValue = 0;
	//u32 	tmplong,tmplong2;
	u8	PollingCnt = 50;
	u8	RFWaitCounter = 0;


	//
	// <Roger_Notes> Due to PASSIVE_LEVEL, so we ONLY simply busy waiting for a while here.
	// We have to make sure that previous RF I/O has been done.
	// 2008.08.20.
	//
	while(priv->bChangeRFInProgress)
	{
		//PlatformReleaseSpinLock(Adapter, RT_RF_OPERATE_SPINLOCK);
		//spin_lock_irqsave(&priv->rf_lock, flags);	//LZM,090318
		down(&priv->rf_sem);

		RFWaitCounter ++;
		RT_TRACE(COMP_RF, "phy_QueryUsbRFReg(): Wait 1 ms (%d times)...\n", RFWaitCounter);
		msleep(1); // 1 ms

		if((RFWaitCounter > 100)) //|| RT_USB_CANNOT_IO(Adapter))
		{
			RT_TRACE(COMP_RF, "phy_QueryUsbRFReg(): (%d) Wait too logn to query BB!!\n", RFWaitCounter);
			return 0xffffffff;
		}
		else
		{
			//PlatformAcquireSpinLock(Adapter, RT_RF_OPERATE_SPINLOCK);
		}
	}

	priv->bChangeRFInProgress = true;
	//PlatformReleaseSpinLock(Adapter, RT_RF_OPERATE_SPINLOCK);


	Offset &= 0x3f; //RF_Offset= 0x00~0x3F

	write_nic_dword(dev, RF_BB_CMD_ADDR, 0xF0000002|
						(Offset<<8)|	//RF_Offset= 0x00~0x3F
						(eRFPath<<16)); 	//RF_Path = 0(A) or 1(B)

	do
	{// Make sure that access could be done.
		if(read_nic_dword(dev, RF_BB_CMD_ADDR) == 0)
			break;
	}while( --PollingCnt );

	// Data FW read back.
	ReturnValue = read_nic_dword(dev, RF_BB_CMD_DATA);

	//PlatformAcquireSpinLock(Adapter, RT_RF_OPERATE_SPINLOCK);
	//spin_unlock_irqrestore(&priv->rf_lock, flags);   //LZM,090318
	up(&priv->rf_sem);
	priv->bChangeRFInProgress = false;

	RT_TRACE(COMP_RF, "phy_QueryUsbRFReg(): eRFPath(%d), Offset(%#x) = %#x\n", eRFPath, Offset, ReturnValue);

	return ReturnValue;

}