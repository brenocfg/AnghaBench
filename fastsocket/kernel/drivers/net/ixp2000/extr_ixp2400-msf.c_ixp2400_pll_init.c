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
struct ixp2400_msf_parameters {int rx_mode; int tx_mode; int rxclk01_multiplier; int rxclk23_multiplier; int txclk01_multiplier; int txclk23_multiplier; } ;

/* Variables and functions */
 int /*<<< orphan*/  IXP2000_MSF_CLK_CNTRL ; 
 int IXP2400_RX_MODE_WIDTH_MASK ; 
 int IXP2400_TX_MODE_WIDTH_MASK ; 
 int ixp2000_reg_read (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ixp2000_reg_write (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void ixp2400_pll_init(struct ixp2400_msf_parameters *mp)
{
	int rx_dual_clock;
	int tx_dual_clock;
	u32 value;

	/*
	 * If the RX mode is not 1x32, we have to enable both RX PLLs
	 * (#0 and #1.)  The same thing for the TX direction.
	 */
	rx_dual_clock = !!(mp->rx_mode & IXP2400_RX_MODE_WIDTH_MASK);
	tx_dual_clock = !!(mp->tx_mode & IXP2400_TX_MODE_WIDTH_MASK);

	/*
	 * Read initial value.
	 */
	value = ixp2000_reg_read(IXP2000_MSF_CLK_CNTRL);

	/*
	 * Put PLLs in powerdown and bypass mode.
	 */
	value |= 0x0000f0f0;
	ixp2000_reg_write(IXP2000_MSF_CLK_CNTRL, value);

	/*
	 * Set single or dual clock mode bits.
	 */
	value &= ~0x03000000;
	value |= (rx_dual_clock << 24) | (tx_dual_clock << 25);

	/*
	 * Set multipliers.
	 */
	value &= ~0x00ff0000;
	value |= mp->rxclk01_multiplier << 16;
	value |= mp->rxclk23_multiplier << 18;
	value |= mp->txclk01_multiplier << 20;
	value |= mp->txclk23_multiplier << 22;

	/*
	 * And write value.
	 */
	ixp2000_reg_write(IXP2000_MSF_CLK_CNTRL, value);

	/*
	 * Disable PLL bypass mode.
	 */
	value &= ~(0x00005000 | rx_dual_clock << 13 | tx_dual_clock << 15);
	ixp2000_reg_write(IXP2000_MSF_CLK_CNTRL, value);

	/*
	 * Turn on PLLs.
	 */
	value &= ~(0x00000050 | rx_dual_clock << 5 | tx_dual_clock << 7);
	ixp2000_reg_write(IXP2000_MSF_CLK_CNTRL, value);

	/*
	 * Wait for PLLs to lock.  There are lock status bits, but IXP2400
	 * erratum #65 says that these lock bits should not be relied upon
	 * as they might not accurately reflect the true state of the PLLs.
	 */
	udelay(100);
}