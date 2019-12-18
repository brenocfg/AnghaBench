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
struct TYPE_3__ {int rx_bitlen; scalar_t__ rcv_buffer; scalar_t__ send_buffer; int /*<<< orphan*/  half_duplex; int /*<<< orphan*/  dmadesc_tx; int /*<<< orphan*/  tx_bitlen; scalar_t__ dma_enabled; int /*<<< orphan*/  dmadesc_rx; int /*<<< orphan*/ * hw; } ;
typedef  TYPE_1__ spi_hal_context_t ;
typedef  int /*<<< orphan*/  spi_dev_t ;

/* Variables and functions */
 int /*<<< orphan*/  lldesc_setup_link (int /*<<< orphan*/ ,scalar_t__,int,int) ; 
 int /*<<< orphan*/  spi_ll_enable_miso (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  spi_ll_enable_mosi (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  spi_ll_reset_dma (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spi_ll_rxdma_start (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spi_ll_txdma_start (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spi_ll_write_buffer (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ) ; 

void spi_hal_prepare_data(const spi_hal_context_t *hal)
{
    spi_dev_t *hw = hal->hw;
    spi_ll_reset_dma(hw);
    //Fill DMA descriptors
    if (hal->rcv_buffer) {
        if (!hal->dma_enabled) {
            //No need to setup anything; we'll copy the result out of the work registers directly later.
        } else {
            lldesc_setup_link(hal->dmadesc_rx, hal->rcv_buffer, ((hal->rx_bitlen + 7) / 8), true);
            spi_ll_rxdma_start(hw, hal->dmadesc_rx);
        }
    } else {
        //DMA temporary workaround: let RX DMA work somehow to avoid the issue in ESP32 v0/v1 silicon
        if (hal->dma_enabled) {
            spi_ll_rxdma_start(hw, 0);
        }
    }

    if (hal->send_buffer) {
        if (!hal->dma_enabled) {
            //Need to copy data to registers manually
            spi_ll_write_buffer(hw, hal->send_buffer, hal->tx_bitlen);
        } else {
            lldesc_setup_link(hal->dmadesc_tx, hal->send_buffer, (hal->tx_bitlen + 7) / 8, false);
            spi_ll_txdma_start(hw, hal->dmadesc_tx);
        }
    }
    //in ESP32 these registers should be configured after the DMA is set
    if ((!hal->half_duplex && hal->rcv_buffer) || hal->send_buffer) {
        spi_ll_enable_mosi(hw, 1);
    } else {
        spi_ll_enable_mosi(hw, 0);
    }
    spi_ll_enable_miso(hw, (hal->rcv_buffer) ? 1 : 0);
}