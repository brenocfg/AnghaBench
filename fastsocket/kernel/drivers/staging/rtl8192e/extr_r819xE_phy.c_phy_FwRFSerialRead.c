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
typedef  scalar_t__ u8 ;
typedef  int u32 ;
struct net_device {int dummy; } ;
typedef  int RF90_RADIO_PATH_E ;

/* Variables and functions */
 int /*<<< orphan*/  QPNR ; 
 int /*<<< orphan*/  RF_DATA ; 
 int read_nic_dword (struct net_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 
 int /*<<< orphan*/  write_nic_dword (struct net_device*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static u32 phy_FwRFSerialRead(
	struct net_device* dev,
	RF90_RADIO_PATH_E	eRFPath,
	u32				Offset	)
{
	u32		retValue = 0;
	u32		Data = 0;
	u8		time = 0;
	//DbgPrint("FW RF CTRL\n\r");
	/* 2007/11/02 MH Firmware RF Write control. By Francis' suggestion, we can
	   not execute the scheme in the initial step. Otherwise, RF-R/W will waste
	   much time. This is only for site survey. */
	// 1. Read operation need not insert data. bit 0-11
	//Data &= bMask12Bits;
	// 2. Write RF register address. Bit 12-19
	Data |= ((Offset&0xFF)<<12);
	// 3. Write RF path.  bit 20-21
	Data |= ((eRFPath&0x3)<<20);
	// 4. Set RF read indicator. bit 22=0
	//Data |= 0x00000;
	// 5. Trigger Fw to operate the command. bit 31
	Data |= 0x80000000;
	// 6. We can not execute read operation if bit 31 is 1.
	while (read_nic_dword(dev, QPNR)&0x80000000)
	{
		// If FW can not finish RF-R/W for more than ?? times. We must reset FW.
		if (time++ < 100)
		{
			//DbgPrint("FW not finish RF-R Time=%d\n\r", time);
			udelay(10);
		}
		else
			break;
	}
	// 7. Execute read operation.
	write_nic_dword(dev, QPNR, Data);
	// 8. Check if firmawre send back RF content.
	while (read_nic_dword(dev, QPNR)&0x80000000)
	{
		// If FW can not finish RF-R/W for more than ?? times. We must reset FW.
		if (time++ < 100)
		{
			//DbgPrint("FW not finish RF-W Time=%d\n\r", time);
			udelay(10);
		}
		else
			return	(0);
	}
	retValue = read_nic_dword(dev, RF_DATA);

	return	(retValue);

}