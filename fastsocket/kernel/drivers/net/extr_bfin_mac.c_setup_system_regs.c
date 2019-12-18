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
struct net_device {int dummy; } ;

/* Variables and functions */
 int CROLL ; 
 int RSTC ; 
 unsigned short RXCKS ; 
 unsigned short RXDWA ; 
 unsigned short bfin_read_EMAC_SYSCTL () ; 
 int /*<<< orphan*/  bfin_write_DMA1_X_COUNT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfin_write_DMA1_X_MODIFY (int) ; 
 int /*<<< orphan*/  bfin_write_DMA1_Y_COUNT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfin_write_DMA1_Y_MODIFY (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfin_write_DMA2_X_COUNT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfin_write_DMA2_X_MODIFY (int) ; 
 int /*<<< orphan*/  bfin_write_DMA2_Y_COUNT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfin_write_DMA2_Y_MODIFY (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfin_write_EMAC_MMC_CTL (int) ; 
 int /*<<< orphan*/  bfin_write_EMAC_SYSCTL (unsigned short) ; 

void setup_system_regs(struct net_device *dev)
{
	unsigned short sysctl;

	/*
	 * Odd word alignment for Receive Frame DMA word
	 * Configure checksum support and rcve frame word alignment
	 */
	sysctl = bfin_read_EMAC_SYSCTL();
#if defined(BFIN_MAC_CSUM_OFFLOAD)
	sysctl |= RXDWA | RXCKS;
#else
	sysctl |= RXDWA;
#endif
	bfin_write_EMAC_SYSCTL(sysctl);

	bfin_write_EMAC_MMC_CTL(RSTC | CROLL);

	/* Initialize the TX DMA channel registers */
	bfin_write_DMA2_X_COUNT(0);
	bfin_write_DMA2_X_MODIFY(4);
	bfin_write_DMA2_Y_COUNT(0);
	bfin_write_DMA2_Y_MODIFY(0);

	/* Initialize the RX DMA channel registers */
	bfin_write_DMA1_X_COUNT(0);
	bfin_write_DMA1_X_MODIFY(4);
	bfin_write_DMA1_Y_COUNT(0);
	bfin_write_DMA1_Y_MODIFY(0);
}