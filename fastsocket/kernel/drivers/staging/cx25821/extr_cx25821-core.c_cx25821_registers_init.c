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
struct cx25821_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLK_RST ; 
 int /*<<< orphan*/  DEV_CNTRL2 ; 
 int FLD_CFG_RCB_CK_EN ; 
 int FLD_USE_ALT_PLL_REF ; 
 int FLD_VID_I_CLK_NOE ; 
 int FLD_VID_J_CLK_NOE ; 
 int /*<<< orphan*/  PCI_INT_MSK ; 
 int /*<<< orphan*/  PLL_A_INT_FRAC ; 
 int /*<<< orphan*/  PLL_A_POST_STAT_BIST ; 
 int /*<<< orphan*/  PLL_B_INT_FRAC ; 
 int /*<<< orphan*/  PLL_B_POST_STAT_BIST ; 
 int /*<<< orphan*/  PLL_C_INT_FRAC ; 
 int /*<<< orphan*/  PLL_C_POST_STAT_BIST ; 
 int /*<<< orphan*/  PLL_D_INT_FRAC ; 
 int /*<<< orphan*/  PLL_D_POST_STAT_BIST ; 
 int /*<<< orphan*/  RDR_TLCTL0 ; 
 int /*<<< orphan*/  VID_CH_CLK_SEL ; 
 int /*<<< orphan*/  VID_CH_MODE_SEL ; 
 int cx_read (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cx_write (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mdelay (int) ; 

__attribute__((used)) static void cx25821_registers_init(struct cx25821_dev *dev)
{
	u32 tmp;

	// enable RUN_RISC in Pecos
	cx_write(DEV_CNTRL2, 0x20);

	// Set the master PCI interrupt masks to enable video, audio, MBIF, and GPIO interrupts
	// I2C interrupt masking is handled by the I2C objects themselves.
	cx_write(PCI_INT_MSK, 0x2001FFFF);

	tmp = cx_read(RDR_TLCTL0);
	tmp &= ~FLD_CFG_RCB_CK_EN;	// Clear the RCB_CK_EN bit
	cx_write(RDR_TLCTL0, tmp);

	// PLL-A setting for the Audio Master Clock
	cx_write(PLL_A_INT_FRAC, 0x9807A58B);

	// PLL_A_POST = 0x1C, PLL_A_OUT_TO_PIN = 0x1
	cx_write(PLL_A_POST_STAT_BIST, 0x8000019C);

	// clear reset bit [31]
	tmp = cx_read(PLL_A_INT_FRAC);
	cx_write(PLL_A_INT_FRAC, tmp & 0x7FFFFFFF);

	// PLL-B setting for Mobilygen Host Bus Interface
	cx_write(PLL_B_INT_FRAC, 0x9883A86F);

	// PLL_B_POST = 0xD, PLL_B_OUT_TO_PIN = 0x0
	cx_write(PLL_B_POST_STAT_BIST, 0x8000018D);

	// clear reset bit [31]
	tmp = cx_read(PLL_B_INT_FRAC);
	cx_write(PLL_B_INT_FRAC, tmp & 0x7FFFFFFF);

	// PLL-C setting for video upstream channel
	cx_write(PLL_C_INT_FRAC, 0x96A0EA3F);

	// PLL_C_POST = 0x3, PLL_C_OUT_TO_PIN = 0x0
	cx_write(PLL_C_POST_STAT_BIST, 0x80000103);

	// clear reset bit [31]
	tmp = cx_read(PLL_C_INT_FRAC);
	cx_write(PLL_C_INT_FRAC, tmp & 0x7FFFFFFF);

	// PLL-D setting for audio upstream channel
	cx_write(PLL_D_INT_FRAC, 0x98757F5B);

	// PLL_D_POST = 0x13, PLL_D_OUT_TO_PIN = 0x0
	cx_write(PLL_D_POST_STAT_BIST, 0x80000113);

	// clear reset bit [31]
	tmp = cx_read(PLL_D_INT_FRAC);
	cx_write(PLL_D_INT_FRAC, tmp & 0x7FFFFFFF);

	// This selects the PLL C clock source for the video upstream channel I and J
	tmp = cx_read(VID_CH_CLK_SEL);
	cx_write(VID_CH_CLK_SEL, (tmp & 0x00FFFFFF) | 0x24000000);

	// 656/VIP SRC Upstream Channel I & J and 7 - Host Bus Interface for channel A-C
	//select 656/VIP DST for downstream Channel A - C
	tmp = cx_read(VID_CH_MODE_SEL);
	//cx_write( VID_CH_MODE_SEL, tmp | 0x1B0001FF);
	cx_write(VID_CH_MODE_SEL, tmp & 0xFFFFFE00);

	// enables 656 port I and J as output
	tmp = cx_read(CLK_RST);
	tmp |= FLD_USE_ALT_PLL_REF;	// use external ALT_PLL_REF pin as its reference clock instead
	cx_write(CLK_RST, tmp & ~(FLD_VID_I_CLK_NOE | FLD_VID_J_CLK_NOE));

	mdelay(100);
}