#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_3__ {int /*<<< orphan*/  DIP2_parity_err; int /*<<< orphan*/  parity_err; int /*<<< orphan*/  rx_ovflw; int /*<<< orphan*/  tx_drops; int /*<<< orphan*/  rx_drops; int /*<<< orphan*/  DIP4_err; } ;
struct peespi {TYPE_2__* adapter; TYPE_1__ intr_cnt; } ;
struct TYPE_4__ {scalar_t__ regs; } ;

/* Variables and functions */
 scalar_t__ A_ESPI_DIP2_ERR_COUNT ; 
 scalar_t__ A_ESPI_INTR_STATUS ; 
 int F_DIP2PARITYERR ; 
 int F_DIP4ERR ; 
 int F_RAMPARITYERR ; 
 int F_RXDROP ; 
 int F_RXOVERFLOW ; 
 int F_TXDROP ; 
 int readl (scalar_t__) ; 
 scalar_t__ t1_is_T1B (TYPE_2__*) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

int t1_espi_intr_handler(struct peespi *espi)
{
	u32 status = readl(espi->adapter->regs + A_ESPI_INTR_STATUS);

	if (status & F_DIP4ERR)
		espi->intr_cnt.DIP4_err++;
	if (status & F_RXDROP)
		espi->intr_cnt.rx_drops++;
	if (status & F_TXDROP)
		espi->intr_cnt.tx_drops++;
	if (status & F_RXOVERFLOW)
		espi->intr_cnt.rx_ovflw++;
	if (status & F_RAMPARITYERR)
		espi->intr_cnt.parity_err++;
	if (status & F_DIP2PARITYERR) {
		espi->intr_cnt.DIP2_parity_err++;

		/*
		 * Must read the error count to clear the interrupt
		 * that it causes.
		 */
		readl(espi->adapter->regs + A_ESPI_DIP2_ERR_COUNT);
	}

	/*
	 * For T1B we need to write 1 to clear ESPI interrupts.  For T2+ we
	 * write the status as is.
	 */
	if (status && t1_is_T1B(espi->adapter))
		status = 1;
	writel(status, espi->adapter->regs + A_ESPI_INTR_STATUS);
	return 0;
}