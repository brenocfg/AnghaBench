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
typedef  int u32 ;
struct net_device {int dummy; } ;
typedef  int /*<<< orphan*/  RT_STATUS ;
typedef  int /*<<< orphan*/  RF90_RADIO_PATH_E ;
typedef  int HW90_BLOCK_E ;

/* Variables and functions */
 int /*<<< orphan*/  COMP_ERR ; 
 int /*<<< orphan*/  COMP_INIT ; 
#define  HW90_BLOCK_MAC 131 
#define  HW90_BLOCK_PHY0 130 
#define  HW90_BLOCK_PHY1 129 
#define  HW90_BLOCK_RF 128 
 int /*<<< orphan*/  RT_STATUS_FAILURE ; 
 int /*<<< orphan*/  RT_STATUS_SUCCESS ; 
 int /*<<< orphan*/  RT_TRACE (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  bMaskDWord ; 
 int /*<<< orphan*/  bRFRegOffsetMask ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int read_nic_dword (struct net_device*,int) ; 
 int rtl8192_phy_QueryRFReg (struct net_device*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtl8192_phy_SetRFReg (struct net_device*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  write_nic_dword (struct net_device*,int,int) ; 

RT_STATUS
PHY_CheckBBAndRFOK(
	struct net_device* dev,
	HW90_BLOCK_E		CheckBlock,
	RF90_RADIO_PATH_E	eRFPath
	)
{
	//struct r8192_priv *priv = ieee80211_priv(dev);
	RT_STATUS			rtStatus = RT_STATUS_SUCCESS;
	u32				i, CheckTimes = 4,ulRegRead = 0;
	u32				WriteAddr[4];
	u32				WriteData[] = {0xfffff027, 0xaa55a02f, 0x00000027, 0x55aa502f};

	// Initialize register address offset to be checked
	WriteAddr[HW90_BLOCK_MAC] = 0x100;
	WriteAddr[HW90_BLOCK_PHY0] = 0x900;
	WriteAddr[HW90_BLOCK_PHY1] = 0x800;
	WriteAddr[HW90_BLOCK_RF] = 0x3;

	for(i=0 ; i < CheckTimes ; i++)
	{

		//
		// Write Data to register and readback
		//
		switch(CheckBlock)
		{
		case HW90_BLOCK_MAC:
			//RT_ASSERT(FALSE, ("PHY_CheckBBRFOK(): Never Write 0x100 here!"));
			RT_TRACE(COMP_INIT, "PHY_CheckBBRFOK(): Never Write 0x100 here!\n");
			break;

		case HW90_BLOCK_PHY0:
		case HW90_BLOCK_PHY1:
			write_nic_dword(dev, WriteAddr[CheckBlock], WriteData[i]);
			ulRegRead = read_nic_dword(dev, WriteAddr[CheckBlock]);
			break;

		case HW90_BLOCK_RF:
			// When initialization, we want the delay function(mdelay(), delay_us()
			// ==> actually we call PlatformStallExecution()) to do NdisStallExecution()
			// [busy wait] instead of NdisMSleep(). So we acquire RT_INITIAL_SPINLOCK
			// to run at Dispatch level to achive it.
			//cosa PlatformAcquireSpinLock(dev, RT_INITIAL_SPINLOCK);
			WriteData[i] &= 0xfff;
			rtl8192_phy_SetRFReg(dev, eRFPath, WriteAddr[HW90_BLOCK_RF], bRFRegOffsetMask, WriteData[i]);
			// TODO: we should not delay for such a long time. Ask SD3
			mdelay(10);
			ulRegRead = rtl8192_phy_QueryRFReg(dev, eRFPath, WriteAddr[HW90_BLOCK_RF], bMaskDWord);
			mdelay(10);
			//cosa PlatformReleaseSpinLock(dev, RT_INITIAL_SPINLOCK);
			break;

		default:
			rtStatus = RT_STATUS_FAILURE;
			break;
		}


		//
		// Check whether readback data is correct
		//
		if(ulRegRead != WriteData[i])
		{
			//RT_TRACE(COMP_FPGA,  ("ulRegRead: %x, WriteData: %x \n", ulRegRead, WriteData[i]));
			RT_TRACE(COMP_ERR, "read back error(read:%x, write:%x)\n", ulRegRead, WriteData[i]);
			rtStatus = RT_STATUS_FAILURE;
			break;
		}
	}

	return rtStatus;
}