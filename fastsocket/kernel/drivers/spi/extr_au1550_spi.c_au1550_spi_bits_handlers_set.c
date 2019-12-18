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
struct au1550_spi {int /*<<< orphan*/ * irq_callback; int /*<<< orphan*/ * txrx_bufs; int /*<<< orphan*/ * tx_word; int /*<<< orphan*/ * rx_word; scalar_t__ usedma; } ;

/* Variables and functions */
 int /*<<< orphan*/  au1550_spi_dma_irq_callback ; 
 int /*<<< orphan*/  au1550_spi_dma_txrxb ; 
 int /*<<< orphan*/  au1550_spi_pio_irq_callback ; 
 int /*<<< orphan*/  au1550_spi_pio_txrxb ; 
 int /*<<< orphan*/  au1550_spi_rx_word_16 ; 
 int /*<<< orphan*/  au1550_spi_rx_word_32 ; 
 int /*<<< orphan*/  au1550_spi_rx_word_8 ; 
 int /*<<< orphan*/  au1550_spi_tx_word_16 ; 
 int /*<<< orphan*/  au1550_spi_tx_word_32 ; 
 int /*<<< orphan*/  au1550_spi_tx_word_8 ; 

__attribute__((used)) static void au1550_spi_bits_handlers_set(struct au1550_spi *hw, int bpw)
{
	if (bpw <= 8) {
		if (hw->usedma) {
			hw->txrx_bufs = &au1550_spi_dma_txrxb;
			hw->irq_callback = &au1550_spi_dma_irq_callback;
		} else {
			hw->rx_word = &au1550_spi_rx_word_8;
			hw->tx_word = &au1550_spi_tx_word_8;
			hw->txrx_bufs = &au1550_spi_pio_txrxb;
			hw->irq_callback = &au1550_spi_pio_irq_callback;
		}
	} else if (bpw <= 16) {
		hw->rx_word = &au1550_spi_rx_word_16;
		hw->tx_word = &au1550_spi_tx_word_16;
		hw->txrx_bufs = &au1550_spi_pio_txrxb;
		hw->irq_callback = &au1550_spi_pio_irq_callback;
	} else {
		hw->rx_word = &au1550_spi_rx_word_32;
		hw->tx_word = &au1550_spi_tx_word_32;
		hw->txrx_bufs = &au1550_spi_pio_txrxb;
		hw->irq_callback = &au1550_spi_pio_irq_callback;
	}
}