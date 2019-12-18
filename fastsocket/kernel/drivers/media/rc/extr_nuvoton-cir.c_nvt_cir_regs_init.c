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
struct nvt_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CIR_FIFOCON ; 
 int CIR_FIFOCON_RX_TRIGGER_LEV ; 
 int CIR_FIFOCON_TX_TRIGGER_LEV ; 
 int /*<<< orphan*/  CIR_IRCON ; 
 int CIR_IRCON_RXEN ; 
 int CIR_IRCON_RXINV ; 
 int CIR_IRCON_SAMPLE_PERIOD_SEL ; 
 int CIR_IRCON_TXEN ; 
 int /*<<< orphan*/  CIR_IRSTS ; 
 int CIR_RX_LIMIT_COUNT ; 
 int /*<<< orphan*/  CIR_SLCH ; 
 int /*<<< orphan*/  CIR_SLCL ; 
 int /*<<< orphan*/  nvt_cir_reg_write (struct nvt_dev*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvt_clear_cir_fifo (struct nvt_dev*) ; 
 int /*<<< orphan*/  nvt_clear_tx_fifo (struct nvt_dev*) ; 
 int /*<<< orphan*/  nvt_set_cir_iren (struct nvt_dev*) ; 

__attribute__((used)) static void nvt_cir_regs_init(struct nvt_dev *nvt)
{
	/* set sample limit count (PE interrupt raised when reached) */
	nvt_cir_reg_write(nvt, CIR_RX_LIMIT_COUNT >> 8, CIR_SLCH);
	nvt_cir_reg_write(nvt, CIR_RX_LIMIT_COUNT & 0xff, CIR_SLCL);

	/* set fifo irq trigger levels */
	nvt_cir_reg_write(nvt, CIR_FIFOCON_TX_TRIGGER_LEV |
			  CIR_FIFOCON_RX_TRIGGER_LEV, CIR_FIFOCON);

	/*
	 * Enable TX and RX, specify carrier on = low, off = high, and set
	 * sample period (currently 50us)
	 */
	nvt_cir_reg_write(nvt,
			  CIR_IRCON_TXEN | CIR_IRCON_RXEN |
			  CIR_IRCON_RXINV | CIR_IRCON_SAMPLE_PERIOD_SEL,
			  CIR_IRCON);

	/* clear hardware rx and tx fifos */
	nvt_clear_cir_fifo(nvt);
	nvt_clear_tx_fifo(nvt);

	/* clear any and all stray interrupts */
	nvt_cir_reg_write(nvt, 0xff, CIR_IRSTS);

	/* and finally, enable interrupts */
	nvt_set_cir_iren(nvt);
}