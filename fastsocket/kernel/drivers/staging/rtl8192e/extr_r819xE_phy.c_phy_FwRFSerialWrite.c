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
 int read_nic_dword (struct net_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 
 int /*<<< orphan*/  write_nic_dword (struct net_device*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
phy_FwRFSerialWrite(
		struct net_device* dev,
		RF90_RADIO_PATH_E	eRFPath,
		u32				Offset,
		u32				Data	)
{
	u8	time = 0;

	//DbgPrint("N FW RF CTRL RF-%d OF%02x DATA=%03x\n\r", eRFPath, Offset, Data);
	/* 2007/11/02 MH Firmware RF Write control. By Francis' suggestion, we can
	   not execute the scheme in the initial step. Otherwise, RF-R/W will waste
	   much time. This is only for site survey. */

	// 1. Set driver write bit and 12 bit data. bit 0-11
	//Data &= bMask12Bits;	// Done by uper layer.
	// 2. Write RF register address. bit 12-19
	Data |= ((Offset&0xFF)<<12);
	// 3. Write RF path.  bit 20-21
	Data |= ((eRFPath&0x3)<<20);
	// 4. Set RF write indicator. bit 22=1
	Data |= 0x400000;
	// 5. Trigger Fw to operate the command. bit 31=1
	Data |= 0x80000000;

	// 6. Write operation. We can not write if bit 31 is 1.
	while (read_nic_dword(dev, QPNR)&0x80000000)
	{
		// If FW can not finish RF-R/W for more than ?? times. We must reset FW.
		if (time++ < 100)
		{
			//DbgPrint("FW not finish RF-W Time=%d\n\r", time);
			udelay(10);
		}
		else
			break;
	}
	// 7. No matter check bit. We always force the write. Because FW will
	//    not accept the command.
	write_nic_dword(dev, QPNR, Data);
	/* 2007/11/02 MH Acoording to test, we must delay 20us to wait firmware
	   to finish RF write operation. */
	/* 2008/01/17 MH We support delay in firmware side now. */
	//delay_us(20);

}