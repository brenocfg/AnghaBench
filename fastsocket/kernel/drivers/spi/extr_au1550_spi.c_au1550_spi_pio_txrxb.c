#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct spi_transfer {scalar_t__ len; int /*<<< orphan*/  rx_buf; int /*<<< orphan*/  tx_buf; } ;
struct spi_device {int /*<<< orphan*/  master; } ;
struct au1550_spi {scalar_t__ len; scalar_t__ tx_count; scalar_t__ rx_count; int /*<<< orphan*/  master_done; TYPE_1__* regs; int /*<<< orphan*/  (* tx_word ) (struct au1550_spi*) ;int /*<<< orphan*/  rx; int /*<<< orphan*/  tx; } ;
struct TYPE_2__ {int psc_spistat; int psc_spimsk; int /*<<< orphan*/  psc_spipcr; } ;

/* Variables and functions */
 int PSC_SPIMSK_SD ; 
 int PSC_SPIMSK_TR ; 
 int /*<<< orphan*/  PSC_SPIPCR_MS ; 
 int PSC_SPISTAT_TF ; 
 int /*<<< orphan*/  au_sync () ; 
 struct au1550_spi* spi_master_get_devdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct au1550_spi*) ; 
 int /*<<< orphan*/  wait_for_completion (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int au1550_spi_pio_txrxb(struct spi_device *spi, struct spi_transfer *t)
{
	u32 stat, mask;
	struct au1550_spi *hw = spi_master_get_devdata(spi->master);

	hw->tx = t->tx_buf;
	hw->rx = t->rx_buf;
	hw->len = t->len;
	hw->tx_count = 0;
	hw->rx_count = 0;

	/* by default enable nearly all events after filling tx fifo */
	mask = PSC_SPIMSK_SD;

	/* fill the transmit FIFO */
	while (hw->tx_count < hw->len) {

		hw->tx_word(hw);

		if (hw->tx_count >= hw->len) {
			/* mask tx fifo request interrupt as we are done */
			mask |= PSC_SPIMSK_TR;
		}

		stat = hw->regs->psc_spistat;
		au_sync();
		if (stat & PSC_SPISTAT_TF)
			break;
	}

	/* enable event interrupts */
	hw->regs->psc_spimsk = mask;
	au_sync();

	/* start the transfer */
	hw->regs->psc_spipcr = PSC_SPIPCR_MS;
	au_sync();

	wait_for_completion(&hw->master_done);

	return hw->rx_count < hw->tx_count ? hw->rx_count : hw->tx_count;
}