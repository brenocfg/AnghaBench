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
typedef  int u16 ;
struct xilinx_spi {int remaining_bytes; scalar_t__ regs; int /*<<< orphan*/  done; int /*<<< orphan*/  rx_ptr; int /*<<< orphan*/  tx_ptr; } ;
struct spi_transfer {int len; int /*<<< orphan*/  rx_buf; int /*<<< orphan*/  tx_buf; } ;
struct spi_device {int /*<<< orphan*/  master; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_COMPLETION (int /*<<< orphan*/ ) ; 
 scalar_t__ XIPIF_V123B_IIER_OFFSET ; 
 scalar_t__ XSPI_CR_OFFSET ; 
 int XSPI_CR_TRANS_INHIBIT ; 
 int XSPI_INTR_TX_EMPTY ; 
 int in_be16 (scalar_t__) ; 
 int in_be32 (scalar_t__) ; 
 int /*<<< orphan*/  out_be16 (scalar_t__,int) ; 
 int /*<<< orphan*/  out_be32 (scalar_t__,int) ; 
 struct xilinx_spi* spi_master_get_devdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wait_for_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xilinx_spi_fill_tx_fifo (struct xilinx_spi*) ; 

__attribute__((used)) static int xilinx_spi_txrx_bufs(struct spi_device *spi, struct spi_transfer *t)
{
	struct xilinx_spi *xspi = spi_master_get_devdata(spi->master);
	u32 ipif_ier;
	u16 cr;

	/* We get here with transmitter inhibited */

	xspi->tx_ptr = t->tx_buf;
	xspi->rx_ptr = t->rx_buf;
	xspi->remaining_bytes = t->len;
	INIT_COMPLETION(xspi->done);

	xilinx_spi_fill_tx_fifo(xspi);

	/* Enable the transmit empty interrupt, which we use to determine
	 * progress on the transmission.
	 */
	ipif_ier = in_be32(xspi->regs + XIPIF_V123B_IIER_OFFSET);
	out_be32(xspi->regs + XIPIF_V123B_IIER_OFFSET,
		 ipif_ier | XSPI_INTR_TX_EMPTY);

	/* Start the transfer by not inhibiting the transmitter any longer */
	cr = in_be16(xspi->regs + XSPI_CR_OFFSET) & ~XSPI_CR_TRANS_INHIBIT;
	out_be16(xspi->regs + XSPI_CR_OFFSET, cr);

	wait_for_completion(&xspi->done);

	/* Disable the transmit empty interrupt */
	out_be32(xspi->regs + XIPIF_V123B_IIER_OFFSET, ipif_ier);

	return t->len - xspi->remaining_bytes;
}