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
typedef  int u16 ;
struct net_device {int dummy; } ;
typedef  int /*<<< orphan*/  RT_STATUS ;

/* Variables and functions */
 int /*<<< orphan*/  COMP_FIRMWARE ; 
 int FEN_CPUEN ; 
 int IMEM_RDY ; 
 int /*<<< orphan*/  RT_STATUS_FAILURE ; 
 int /*<<< orphan*/  RT_STATUS_SUCCESS ; 
 int /*<<< orphan*/  RT_TRACE (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  SYS_CLKR ; 
 int SYS_CPU_CLKSEL ; 
 int /*<<< orphan*/  SYS_FUNC_EN ; 
 int /*<<< orphan*/  TCR ; 
 int read_nic_byte (struct net_device*,int /*<<< orphan*/ ) ; 
 int read_nic_word (struct net_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 
 int /*<<< orphan*/  write_nic_byte (struct net_device*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  write_nic_word (struct net_device*,int /*<<< orphan*/ ,int) ; 

RT_STATUS
FirmwareEnableCPU(struct net_device *dev)
{

	RT_STATUS	rtStatus = RT_STATUS_SUCCESS;
	u8		tmpU1b, CPUStatus = 0;
	u16		tmpU2b;
	u32		iCheckTime = 200;

	RT_TRACE(COMP_FIRMWARE, "-->FirmwareEnableCPU()\n" );
	// Enable CPU.
	tmpU1b = read_nic_byte(dev, SYS_CLKR);
	write_nic_byte(dev,  SYS_CLKR, (tmpU1b|SYS_CPU_CLKSEL)); //AFE source

	tmpU2b = read_nic_word(dev, SYS_FUNC_EN);
	write_nic_word(dev, SYS_FUNC_EN, (tmpU2b|FEN_CPUEN));

	//Polling IMEM Ready after CPU has refilled.
	do
	{
		CPUStatus = read_nic_byte(dev, TCR);
		if(CPUStatus& IMEM_RDY)
		{
			RT_TRACE(COMP_FIRMWARE, "IMEM Ready after CPU has refilled.\n");
			break;
		}

		//usleep(100);
		udelay(100);
	}while(iCheckTime--);

	if(!(CPUStatus & IMEM_RDY))
		return RT_STATUS_FAILURE;

	RT_TRACE(COMP_FIRMWARE, "<--FirmwareEnableCPU(): rtStatus(%#x)\n", rtStatus);
	return rtStatus;
}