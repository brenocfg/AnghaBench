#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_8__ ;
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  void* uint32_t ;
struct TYPE_13__ {int SecondAddressChained; int InterruptOnComplete; int TransmitTimestampEnable; } ;
struct TYPE_12__ {void* TransmitBuffer1Size; } ;
struct TYPE_15__ {void* Buffer2NextDescAddr; void* Buffer1Addr; TYPE_4__ TDES0; TYPE_3__ TDES1; } ;
typedef  TYPE_6__ eth_dma_tx_descriptor_t ;
struct TYPE_11__ {int SecondAddressChained; scalar_t__ DisableInterruptOnComplete; void* ReceiveBuffer1Size; } ;
struct TYPE_10__ {int Own; } ;
struct TYPE_16__ {void* Buffer2NextDescAddr; void* Buffer1Addr; TYPE_2__ RDES1; TYPE_1__ RDES0; } ;
typedef  TYPE_7__ eth_dma_rx_descriptor_t ;
struct TYPE_17__ {TYPE_6__* tx_desc; TYPE_5__* dma_regs; TYPE_7__* rx_desc; scalar_t__* tx_buf; scalar_t__* rx_buf; scalar_t__ descriptors; } ;
typedef  TYPE_8__ emac_hal_context_t ;
struct TYPE_14__ {void* dmatxbaseaddr; void* dmarxbaseaddr; } ;

/* Variables and functions */
 void* CONFIG_ETH_DMA_BUFFER_SIZE ; 
 int CONFIG_ETH_DMA_RX_BUFFER_NUM ; 
 int CONFIG_ETH_DMA_TX_BUFFER_NUM ; 

void emac_hal_reset_desc_chain(emac_hal_context_t *hal)
{
    /* reset DMA descriptors */
    hal->rx_desc = (eth_dma_rx_descriptor_t *)(hal->descriptors);
    hal->tx_desc = (eth_dma_tx_descriptor_t *)(hal->descriptors +
                   sizeof(eth_dma_rx_descriptor_t) * CONFIG_ETH_DMA_RX_BUFFER_NUM);
    /* init rx chain */
    for (int i = 0; i < CONFIG_ETH_DMA_RX_BUFFER_NUM; i++) {
        /* Set Own bit of the Rx descriptor Status: DMA */
        hal->rx_desc[i].RDES0.Own = 1;
        /* Set Buffer1 size and Second Address Chained bit */
        hal->rx_desc[i].RDES1.SecondAddressChained = 1;
        hal->rx_desc[i].RDES1.ReceiveBuffer1Size = CONFIG_ETH_DMA_BUFFER_SIZE;
        /* Enable Ethernet DMA Rx Descriptor interrupt */
        hal->rx_desc[i].RDES1.DisableInterruptOnComplete = 0;
        /* point to the buffer */
        hal->rx_desc[i].Buffer1Addr = (uint32_t)(hal->rx_buf[i]);
        /* point to next descriptor */
        hal->rx_desc[i].Buffer2NextDescAddr = (uint32_t)(hal->rx_desc + i + 1);
    }
    /* For last descriptor, set next descriptor address register equal to the first descriptor base address */
    hal->rx_desc[CONFIG_ETH_DMA_RX_BUFFER_NUM - 1].Buffer2NextDescAddr = (uint32_t)(hal->rx_desc);

    /* init tx chain */
    for (int i = 0; i < CONFIG_ETH_DMA_TX_BUFFER_NUM; i++) {
        /* Set Second Address Chained bit */
        hal->tx_desc[i].TDES0.SecondAddressChained = 1;
        hal->tx_desc[i].TDES1.TransmitBuffer1Size = CONFIG_ETH_DMA_BUFFER_SIZE;
        /* Enable Ethernet DMA Tx Descriptor interrupt */
        hal->tx_desc[1].TDES0.InterruptOnComplete = 1;
        /* Enable Transmit Timestamp */
        hal->tx_desc[i].TDES0.TransmitTimestampEnable = 1;
        /* point to the buffer */
        hal->tx_desc[i].Buffer1Addr = (uint32_t)(hal->tx_buf[i]);
        /* point to next descriptor */
        hal->tx_desc[i].Buffer2NextDescAddr = (uint32_t)(hal->tx_desc + i + 1);
    }
    /* For last descriptor, set next descriptor address register equal to the first descriptor base address */
    hal->tx_desc[CONFIG_ETH_DMA_TX_BUFFER_NUM - 1].Buffer2NextDescAddr = (uint32_t)(hal->tx_desc);

    /* set base address of the first descriptor */
    hal->dma_regs->dmarxbaseaddr = (uint32_t)hal->rx_desc;
    hal->dma_regs->dmatxbaseaddr = (uint32_t)hal->tx_desc;
}