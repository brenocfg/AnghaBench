#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint32_t ;
struct TYPE_6__ {scalar_t__ Own; int FrameLength; scalar_t__ LastDescriptor; scalar_t__ FirstDescriptor; } ;
struct TYPE_8__ {scalar_t__ Buffer2NextDescAddr; TYPE_1__ RDES0; scalar_t__ Buffer1Addr; } ;
typedef  TYPE_3__ eth_dma_rx_descriptor_t ;
struct TYPE_9__ {TYPE_2__* dma_regs; TYPE_3__* rx_desc; } ;
typedef  TYPE_4__ emac_hal_context_t ;
struct TYPE_7__ {scalar_t__ dmarxpolldemand; } ;

/* Variables and functions */
 int CONFIG_ETH_DMA_BUFFER_SIZE ; 
 int CONFIG_ETH_DMA_RX_BUFFER_NUM ; 
 scalar_t__ EMAC_DMADESC_OWNER_DMA ; 
 int ETH_CRC_LENGTH ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,void*,int) ; 

uint32_t emac_hal_receive_frame(emac_hal_context_t *hal, uint8_t *buf, uint32_t size, uint32_t *frames_remain)
{
    eth_dma_rx_descriptor_t *desc_iter = NULL;
    eth_dma_rx_descriptor_t *first_desc = NULL;
    uint32_t iter = 0;
    uint32_t seg_count = 0;
    uint32_t len = 0;
    uint32_t frame_count = 0;

    first_desc = hal->rx_desc;
    desc_iter = hal->rx_desc;
    /* Traverse descriptors owned by CPU */
    while ((desc_iter->RDES0.Own != EMAC_DMADESC_OWNER_DMA) && (iter < CONFIG_ETH_DMA_RX_BUFFER_NUM) && !frame_count) {
        iter++;
        seg_count++;
        /* Last segment in frame */
        if (desc_iter->RDES0.LastDescriptor) {
            /* Get the Frame Length of the received packet: substruct 4 bytes of the CRC */
            len = desc_iter->RDES0.FrameLength - ETH_CRC_LENGTH;
            /* check if the buffer can store the whole frame */
            if (len > size) {
                /* return the real size that we want */
                /* user need to compare the return value to the size they prepared when this function returned */
                return len;
            }
            /* update unhandled frame count */
            frame_count++;
        }
        /* First segment in frame */
        if (desc_iter->RDES0.FirstDescriptor) {
            first_desc = desc_iter;
        }
        /* point to next descriptor */
        desc_iter = (eth_dma_rx_descriptor_t *)(desc_iter->Buffer2NextDescAddr);
    }
    /* there's at least one frame to process */
    if (frame_count) {
        /* check how many frames left to handle */
        while ((desc_iter->RDES0.Own != EMAC_DMADESC_OWNER_DMA) && (iter < CONFIG_ETH_DMA_RX_BUFFER_NUM)) {
            iter++;
            if (desc_iter->RDES0.LastDescriptor) {
                frame_count++;
            }
            /* point to next descriptor */
            desc_iter = (eth_dma_rx_descriptor_t *)(desc_iter->Buffer2NextDescAddr);
        }
        desc_iter = first_desc;
        for (iter = 0; iter < seg_count - 1; iter++) {
            /* copy data to buffer */
            memcpy(buf + iter * CONFIG_ETH_DMA_BUFFER_SIZE,
                   (void *)(desc_iter->Buffer1Addr), CONFIG_ETH_DMA_BUFFER_SIZE);
            /* Set Own bit in Rx descriptors: gives the buffers back to DMA */
            desc_iter->RDES0.Own = EMAC_DMADESC_OWNER_DMA;
            desc_iter = (eth_dma_rx_descriptor_t *)(desc_iter->Buffer2NextDescAddr);
        }
        memcpy(buf + iter * CONFIG_ETH_DMA_BUFFER_SIZE,
               (void *)(desc_iter->Buffer1Addr), len % CONFIG_ETH_DMA_BUFFER_SIZE);
        desc_iter->RDES0.Own = EMAC_DMADESC_OWNER_DMA;
        /* update rxdesc */
        hal->rx_desc = (eth_dma_rx_descriptor_t *)(desc_iter->Buffer2NextDescAddr);
        /* poll rx demand */
        hal->dma_regs->dmarxpolldemand = 0;
        frame_count--;
    }
    *frames_remain = frame_count;
    return len;
}