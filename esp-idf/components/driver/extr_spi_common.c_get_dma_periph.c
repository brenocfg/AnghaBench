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
typedef  int uint32_t ;

/* Variables and functions */
 int PERIPH_SPI2_DMA_MODULE ; 
 int PERIPH_SPI3_DMA_MODULE ; 
 int PERIPH_SPI_DMA_MODULE ; 
 int PERIPH_SPI_SHARED_DMA_MODULE ; 
 int /*<<< orphan*/  abort () ; 

__attribute__((used)) static inline uint32_t get_dma_periph(int dma_chan)
{
#ifdef CONFIG_IDF_TARGET_ESP32S2BETA
    if (dma_chan==1) {
        return PERIPH_SPI2_DMA_MODULE;
    } else if (dma_chan==2) {
        return PERIPH_SPI3_DMA_MODULE;
    } else if (dma_chan==3) {
        return PERIPH_SPI_SHARED_DMA_MODULE;
    } else {
        abort();
        return -1;
    }
#elif defined(CONFIG_IDF_TARGET_ESP32)
    return PERIPH_SPI_DMA_MODULE;
#endif
}