#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int bitlen; int /*<<< orphan*/ * rx_buffer; int /*<<< orphan*/  hw; int /*<<< orphan*/ * tx_buffer; int /*<<< orphan*/ * dmadesc_tx; int /*<<< orphan*/ * dmadesc_rx; scalar_t__ use_dma; } ;
typedef  TYPE_1__ spi_slave_hal_context_t ;

/* Variables and functions */
 int /*<<< orphan*/  lldesc_setup_link (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  spi_ll_enable_miso (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spi_ll_enable_mosi (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spi_ll_reset_dma (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spi_ll_rxdma_start (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spi_ll_slave_reset (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spi_ll_slave_set_rx_bitlen (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spi_ll_slave_set_tx_bitlen (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spi_ll_txdma_start (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spi_ll_write_buffer (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

void spi_slave_hal_prepare_data(const spi_slave_hal_context_t *hal)
{
    spi_ll_slave_reset(hal->hw);
    if (hal->use_dma) {
        spi_ll_reset_dma(hal->hw);

        //Fill DMA descriptors
        if (hal->rx_buffer) {
            lldesc_setup_link(hal->dmadesc_rx, hal->rx_buffer, ((hal->bitlen + 7) / 8), true);
            spi_ll_rxdma_start(hal->hw, &hal->dmadesc_rx[0]);
        }
        if (hal->tx_buffer) {
            lldesc_setup_link(hal->dmadesc_tx, hal->tx_buffer, (hal->bitlen + 7) / 8, false);
            spi_ll_txdma_start(hal->hw, (&hal->dmadesc_tx[0]));
        }
    } else {
        //No DMA. Turn off SPI and copy data to transmit buffers.
        if (hal->tx_buffer) {
            spi_ll_write_buffer(hal->hw, hal->tx_buffer, hal->bitlen);
        }
    }

    spi_ll_slave_set_rx_bitlen(hal->hw, hal->bitlen);
    spi_ll_slave_set_tx_bitlen(hal->hw, hal->bitlen);
    spi_ll_enable_mosi(hal->hw, (hal->tx_buffer == NULL) ? 0 : 1);
    spi_ll_enable_miso(hal->hw, (hal->rx_buffer == NULL) ? 0 : 1);
}