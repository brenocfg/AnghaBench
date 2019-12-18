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
struct net_device {int dummy; } ;

/* Variables and functions */
 int AFE_BGEN ; 
 int AFE_MBEN ; 
 scalar_t__ AFE_MISC ; 
 scalar_t__ AFE_PLL_CTRL ; 
 scalar_t__ AFE_XTAL_CTRL ; 
 int BIT7 ; 
 scalar_t__ CMDR ; 
 int /*<<< orphan*/  COMP_INIT ; 
 int LDA15_EN ; 
 scalar_t__ LDOA15_CTRL ; 
 scalar_t__ LDOV12D_CTRL ; 
 int LDV12_EN ; 
 scalar_t__ PMC_FSM ; 
 scalar_t__ RPWM ; 
 int /*<<< orphan*/  RT_TRACE (int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ SPS0_CTRL ; 
 scalar_t__ SYS_CLKR ; 
 int SYS_CPU_CLKSEL ; 
 scalar_t__ SYS_FUNC_EN ; 
 scalar_t__ SYS_ISO_CTRL ; 
 scalar_t__ TCR ; 
 int TXDMA_EN ; 
 int TXDMA_INIT_VALUE ; 
 int read_nic_byte (struct net_device*,scalar_t__) ; 
 int read_nic_byte_E (struct net_device*,int) ; 
 int /*<<< orphan*/  udelay (int) ; 
 int /*<<< orphan*/  write_nic_byte (struct net_device*,scalar_t__,int) ; 
 int /*<<< orphan*/  write_nic_byte_E (struct net_device*,int,int) ; 

__attribute__((used)) static void rtl8192SU_MacConfigBeforeFwDownloadASIC(struct net_device *dev)
{
	u8				tmpU1b;// i;
//	u16				tmpU2b;
//	u32				tmpU4b;
	u8				PollingCnt = 20;

	RT_TRACE(COMP_INIT, "--->MacConfigBeforeFwDownloadASIC()\n");

	//2MAC Initialization for power on sequence, Revised by Roger. 2008.09.03.

	//
	//<Roger_Notes> Set control path switch to HW control and reset Digital Core,  CPU Core and
	// MAC I/O to solve FW download fail when system from resume sate.
	// 2008.11.04.
	//
       tmpU1b = read_nic_byte(dev, SYS_CLKR+1);
       if(tmpU1b & 0x80)
	{
       	tmpU1b &= 0x3f;
              write_nic_byte(dev, SYS_CLKR+1, tmpU1b);
       }
	// Clear FW RPWM for FW control LPS. by tynli. 2009.02.23
	write_nic_byte(dev, RPWM, 0x0);

       tmpU1b = read_nic_byte(dev, SYS_FUNC_EN+1);
       tmpU1b &= 0x73;
       write_nic_byte(dev, SYS_FUNC_EN+1, tmpU1b);
       udelay(1000);

	//Revised POS, suggested by SD1 Alex, 2008.09.27.
	write_nic_byte(dev, SPS0_CTRL+1, 0x53);
	write_nic_byte(dev, SPS0_CTRL, 0x57);

	//Enable AFE Macro Block's Bandgap adn Enable AFE Macro Block's Mbias
	tmpU1b = read_nic_byte(dev, AFE_MISC);
	write_nic_byte(dev, AFE_MISC, (tmpU1b|AFE_BGEN|AFE_MBEN));

	//Enable PLL Power (LDOA15V)
	tmpU1b = read_nic_byte(dev, LDOA15_CTRL);
	write_nic_byte(dev, LDOA15_CTRL, (tmpU1b|LDA15_EN));

	//Enable LDOV12D block
	tmpU1b = read_nic_byte(dev, LDOV12D_CTRL);
	write_nic_byte(dev, LDOV12D_CTRL, (tmpU1b|LDV12_EN));

	//mpU1b = read_nic_byte(Adapter, SPS1_CTRL);
	//write_nic_byte(dev, SPS1_CTRL, (tmpU1b|SPS1_LDEN));

	//PlatformSleepUs(2000);

	//Enable Switch Regulator Block
	//tmpU1b = read_nic_byte(Adapter, SPS1_CTRL);
	//write_nic_byte(dev, SPS1_CTRL, (tmpU1b|SPS1_SWEN));

	//write_nic_dword(Adapter, SPS1_CTRL, 0x00a7b267);

	tmpU1b = read_nic_byte(dev, SYS_ISO_CTRL+1);
	write_nic_byte(dev, SYS_ISO_CTRL+1, (tmpU1b|0x08));

	//Engineer Packet CP test Enable
	tmpU1b = read_nic_byte(dev, SYS_FUNC_EN+1);
	write_nic_byte(dev, SYS_FUNC_EN+1, (tmpU1b|0x20));

	//Support 64k IMEM, suggested by SD1 Alex.
	tmpU1b = read_nic_byte(dev, SYS_ISO_CTRL+1);
	write_nic_byte(dev, SYS_ISO_CTRL+1, (tmpU1b& 0x68));

	//Enable AFE clock
	tmpU1b = read_nic_byte(dev, AFE_XTAL_CTRL+1);
	write_nic_byte(dev, AFE_XTAL_CTRL+1, (tmpU1b& 0xfb));

	//Enable AFE PLL Macro Block
	tmpU1b = read_nic_byte(dev, AFE_PLL_CTRL);
	write_nic_byte(dev, AFE_PLL_CTRL, (tmpU1b|0x11));

	//Attatch AFE PLL to MACTOP/BB/PCIe Digital
	tmpU1b = read_nic_byte(dev, SYS_ISO_CTRL);
	write_nic_byte(dev, SYS_ISO_CTRL, (tmpU1b&0xEE));

	// Switch to 40M clock
	write_nic_byte(dev, SYS_CLKR, 0x00);

	//SSC Disable
	tmpU1b = read_nic_byte(dev, SYS_CLKR);
	//write_nic_byte(dev, SYS_CLKR, (tmpU1b&0x5f));
	write_nic_byte(dev, SYS_CLKR, (tmpU1b|0xa0));

	//Enable MAC clock
	tmpU1b = read_nic_byte(dev, SYS_CLKR+1);
	write_nic_byte(dev, SYS_CLKR+1, (tmpU1b|0x18));

	//Revised POS, suggested by SD1 Alex, 2008.09.27.
	write_nic_byte(dev, PMC_FSM, 0x02);

	//Enable Core digital and enable IOREG R/W
	tmpU1b = read_nic_byte(dev, SYS_FUNC_EN+1);
	write_nic_byte(dev, SYS_FUNC_EN+1, (tmpU1b|0x08));

	//Enable REG_EN
	tmpU1b = read_nic_byte(dev, SYS_FUNC_EN+1);
	write_nic_byte(dev, SYS_FUNC_EN+1, (tmpU1b|0x80));

	//Switch the control path to FW
	tmpU1b = read_nic_byte(dev, SYS_CLKR+1);
	write_nic_byte(dev, SYS_CLKR+1, (tmpU1b|0x80)& 0xBF);

	write_nic_byte(dev, CMDR, 0xFC);
	write_nic_byte(dev, CMDR+1, 0x37);

	//Fix the RX FIFO issue(usb error), 970410
	tmpU1b = read_nic_byte_E(dev, 0x5c);
	write_nic_byte_E(dev, 0x5c, (tmpU1b|BIT7));

	 //For power save, used this in the bit file after 970621
	tmpU1b = read_nic_byte(dev, SYS_CLKR);
	write_nic_byte(dev, SYS_CLKR, tmpU1b&(~SYS_CPU_CLKSEL));

	// Revised for 8051 ROM code wrong operation. Added by Roger. 2008.10.16.
	write_nic_byte_E(dev, 0x1c, 0x80);

	//
	// <Roger_EXP> To make sure that TxDMA can ready to download FW.
	// We should reset TxDMA if IMEM RPT was not ready.
	// Suggested by SD1 Alex. 2008.10.23.
	//
	do
	{
		tmpU1b = read_nic_byte(dev, TCR);
		if((tmpU1b & TXDMA_INIT_VALUE) == TXDMA_INIT_VALUE)
			break;
		//PlatformStallExecution(5);
		udelay(5);
	}while(PollingCnt--);	// Delay 1ms

	if(PollingCnt <= 0 )
	{
		RT_TRACE(COMP_INIT, "MacConfigBeforeFwDownloadASIC(): Polling TXDMA_INIT_VALUE timeout!! Current TCR(%#x)\n", tmpU1b);
		tmpU1b = read_nic_byte(dev, CMDR);
		write_nic_byte(dev, CMDR, tmpU1b&(~TXDMA_EN));
		udelay(2);
		write_nic_byte(dev, CMDR, tmpU1b|TXDMA_EN);// Reset TxDMA
	}


	RT_TRACE(COMP_INIT, "<---MacConfigBeforeFwDownloadASIC()\n");
}