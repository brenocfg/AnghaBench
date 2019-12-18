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
struct mv643xx_eth_shared_private {int extended_rx_coal_limit; int /*<<< orphan*/  tx_bw_control; scalar_t__ base; } ;

/* Variables and functions */
 scalar_t__ SDMA_CONFIG ; 
 int /*<<< orphan*/  TX_BW_CONTROL_ABSENT ; 
 int /*<<< orphan*/  TX_BW_CONTROL_NEW_LAYOUT ; 
 int /*<<< orphan*/  TX_BW_CONTROL_OLD_LAYOUT ; 
 scalar_t__ TX_BW_MTU_MOVED ; 
 scalar_t__ TX_BW_RATE ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static void infer_hw_params(struct mv643xx_eth_shared_private *msp)
{
	/*
	 * Check whether we have a 14-bit coal limit field in bits
	 * [21:8], or a 16-bit coal limit in bits [25,21:7] of the
	 * SDMA config register.
	 */
	writel(0x02000000, msp->base + 0x0400 + SDMA_CONFIG);
	if (readl(msp->base + 0x0400 + SDMA_CONFIG) & 0x02000000)
		msp->extended_rx_coal_limit = 1;
	else
		msp->extended_rx_coal_limit = 0;

	/*
	 * Check whether the MAC supports TX rate control, and if
	 * yes, whether its associated registers are in the old or
	 * the new place.
	 */
	writel(1, msp->base + 0x0400 + TX_BW_MTU_MOVED);
	if (readl(msp->base + 0x0400 + TX_BW_MTU_MOVED) & 1) {
		msp->tx_bw_control = TX_BW_CONTROL_NEW_LAYOUT;
	} else {
		writel(7, msp->base + 0x0400 + TX_BW_RATE);
		if (readl(msp->base + 0x0400 + TX_BW_RATE) & 7)
			msp->tx_bw_control = TX_BW_CONTROL_OLD_LAYOUT;
		else
			msp->tx_bw_control = TX_BW_CONTROL_ABSENT;
	}
}