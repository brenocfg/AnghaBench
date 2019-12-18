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
struct smsc9420_pdata {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMAC_CONTROL ; 
 int DMAC_CONTROL_ST_ ; 
 int /*<<< orphan*/  DMAC_INTR_ENA ; 
 int DMAC_INTR_ENA_TX_ ; 
 int /*<<< orphan*/  DMAC_STATUS ; 
 int DMAC_STS_TS_ ; 
 int DMAC_STS_TXPS_ ; 
 int /*<<< orphan*/  IFDOWN ; 
 int /*<<< orphan*/  MAC_CR ; 
 int MAC_CR_TXEN_ ; 
 int /*<<< orphan*/  smsc9420_pci_flush_write (struct smsc9420_pdata*) ; 
 int smsc9420_reg_read (struct smsc9420_pdata*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smsc9420_reg_write (struct smsc9420_pdata*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  smsc_warn (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void smsc9420_stop_tx(struct smsc9420_pdata *pd)
{
	u32 dmac_control, mac_cr, dma_intr_ena;
	int timeout = 1000;

	/* disable TX DMAC */
	dmac_control = smsc9420_reg_read(pd, DMAC_CONTROL);
	dmac_control &= (~DMAC_CONTROL_ST_);
	smsc9420_reg_write(pd, DMAC_CONTROL, dmac_control);

	/* Wait max 10ms for transmit process to stop */
	while (--timeout) {
		if (smsc9420_reg_read(pd, DMAC_STATUS) & DMAC_STS_TS_)
			break;
		udelay(10);
	}

	if (!timeout)
		smsc_warn(IFDOWN, "TX DMAC failed to stop");

	/* ACK Tx DMAC stop bit */
	smsc9420_reg_write(pd, DMAC_STATUS, DMAC_STS_TXPS_);

	/* mask TX DMAC interrupts */
	dma_intr_ena = smsc9420_reg_read(pd, DMAC_INTR_ENA);
	dma_intr_ena &= ~(DMAC_INTR_ENA_TX_);
	smsc9420_reg_write(pd, DMAC_INTR_ENA, dma_intr_ena);
	smsc9420_pci_flush_write(pd);

	/* stop MAC TX */
	mac_cr = smsc9420_reg_read(pd, MAC_CR) & (~MAC_CR_TXEN_);
	smsc9420_reg_write(pd, MAC_CR, mac_cr);
	smsc9420_pci_flush_write(pd);
}