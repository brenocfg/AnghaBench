#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint32_t ;
struct TYPE_8__ {int FirstSegment; int LastSegment; int InterruptOnComplete; int /*<<< orphan*/  Own; } ;
struct TYPE_7__ {int TransmitBuffer1Size; } ;
struct TYPE_10__ {scalar_t__ Buffer2NextDescAddr; TYPE_2__ TDES0; scalar_t__ Buffer1Addr; TYPE_1__ TDES1; } ;
typedef  TYPE_4__ eth_dma_tx_descriptor_t ;
struct TYPE_11__ {TYPE_3__* dma_regs; TYPE_4__* tx_desc; } ;
typedef  TYPE_5__ emac_hal_context_t ;
struct TYPE_9__ {scalar_t__ dmatxpolldemand; } ;

/* Variables and functions */
 int CONFIG_ETH_DMA_BUFFER_SIZE ; 
 int /*<<< orphan*/  EMAC_DMADESC_OWNER_DMA ; 
 int /*<<< orphan*/  memcpy (void*,int /*<<< orphan*/ *,int) ; 

void emac_hal_transmit_frame(emac_hal_context_t *hal, uint8_t *buf, uint32_t length)
{
    /* Get the number of Tx buffers to use for the frame */
    uint32_t bufcount = 0;
    uint32_t lastlen = length;
    while (lastlen > CONFIG_ETH_DMA_BUFFER_SIZE) {
        lastlen -= CONFIG_ETH_DMA_BUFFER_SIZE;
        bufcount++;
    }
    if (lastlen) {
        bufcount++;
    }
    /* A frame is transmitted in multiple descriptor */
    for (uint32_t i = 0; i < bufcount; i++) {
        /* Clear FIRST and LAST segment bits */
        hal->tx_desc->TDES0.FirstSegment = 0;
        hal->tx_desc->TDES0.LastSegment = 0;
        if (i == 0) {
            /* Setting the first segment bit */
            hal->tx_desc->TDES0.FirstSegment = 1;
        }
        if (i == (bufcount - 1)) {
            /* Setting the last segment bit */
            hal->tx_desc->TDES0.LastSegment = 1;
            /* Enable transmit interrupt */
            hal->tx_desc->TDES0.InterruptOnComplete = 1;
            /* Program size */
            hal->tx_desc->TDES1.TransmitBuffer1Size = lastlen;
            /* copy data from uplayer stack buffer */
            memcpy((void *)(hal->tx_desc->Buffer1Addr), buf + i * CONFIG_ETH_DMA_BUFFER_SIZE, lastlen);
        } else {
            /* Program size */
            hal->tx_desc->TDES1.TransmitBuffer1Size = CONFIG_ETH_DMA_BUFFER_SIZE;
            /* copy data from uplayer stack buffer */
            memcpy((void *)(hal->tx_desc->Buffer1Addr), buf + i * CONFIG_ETH_DMA_BUFFER_SIZE, CONFIG_ETH_DMA_BUFFER_SIZE);
        }
        /* Set Own bit of the Tx descriptor Status: gives the buffer back to ETHERNET DMA */
        hal->tx_desc->TDES0.Own = EMAC_DMADESC_OWNER_DMA;
        /* Point to next descriptor */
        hal->tx_desc = (eth_dma_tx_descriptor_t *)(hal->tx_desc->Buffer2NextDescAddr);
    }
    hal->dma_regs->dmatxpolldemand = 0;
}