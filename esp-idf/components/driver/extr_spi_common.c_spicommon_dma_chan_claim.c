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

/* Variables and functions */
 int DMA_CHANNEL_ENABLED (int) ; 
 int /*<<< orphan*/  PERIPH_SPI2_DMA_MODULE ; 
 int /*<<< orphan*/  PERIPH_SPI3_DMA_MODULE ; 
 int /*<<< orphan*/  PERIPH_SPI_SHARED_DMA_MODULE ; 
 int SOC_SPI_DMA_CHAN_NUM ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  get_dma_periph (int) ; 
 int /*<<< orphan*/  periph_module_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  portENTER_CRITICAL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  portEXIT_CRITICAL (int /*<<< orphan*/ *) ; 
 int spi_dma_chan_enabled ; 
 int /*<<< orphan*/  spi_dma_spinlock ; 

bool spicommon_dma_chan_claim (int dma_chan)
{
    bool ret = false;
    assert(dma_chan >= 1 && dma_chan <= SOC_SPI_DMA_CHAN_NUM);

    portENTER_CRITICAL(&spi_dma_spinlock);
    if ( !(spi_dma_chan_enabled & DMA_CHANNEL_ENABLED(dma_chan)) ) {
        // get the channel only when it's not claimed yet.
        spi_dma_chan_enabled |= DMA_CHANNEL_ENABLED(dma_chan);
        ret = true;
    }

#if CONFIG_IDF_TARGET_ESP32
    periph_module_enable(get_dma_periph(dma_chan));
#elif CONFIG_IDF_TARGET_ESP32S2BETA
    if (dma_chan==1) {
        periph_module_enable(PERIPH_SPI2_DMA_MODULE);
    } else if (dma_chan==2) {
        periph_module_enable(PERIPH_SPI3_DMA_MODULE);
    } else if (dma_chan==3) {
        periph_module_enable(PERIPH_SPI_SHARED_DMA_MODULE);
    }
#endif
    portEXIT_CRITICAL(&spi_dma_spinlock);

    return ret;
}