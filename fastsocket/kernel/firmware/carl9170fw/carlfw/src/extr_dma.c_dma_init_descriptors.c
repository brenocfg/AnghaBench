#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_23__   TYPE_8__ ;
typedef  struct TYPE_22__   TYPE_7__ ;
typedef  struct TYPE_21__   TYPE_6__ ;
typedef  struct TYPE_20__   TYPE_5__ ;
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;
typedef  struct TYPE_15__   TYPE_10__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_21__ {scalar_t__ head; } ;
struct TYPE_20__ {int fw_desc_available; TYPE_7__* fw_desc; TYPE_6__ rx_queue; TYPE_6__* tx_queue; TYPE_6__* cab_queue; TYPE_6__ tx_retry; } ;
struct TYPE_19__ {int int_desc_available; TYPE_7__* int_desc; } ;
struct TYPE_17__ {TYPE_6__ up_queue; TYPE_6__ down_queue; } ;
struct TYPE_23__ {TYPE_5__ wlan; TYPE_4__ usb; TYPE_2__ pta; } ;
struct TYPE_22__ {int dataSize; void* dataAddr; } ;
struct TYPE_18__ {int /*<<< orphan*/  rsp; } ;
struct TYPE_16__ {int /*<<< orphan*/  data; } ;
struct TYPE_15__ {TYPE_3__ reserved; int /*<<< orphan*/ * block; TYPE_1__* data; TYPE_7__* terminator; } ;

/* Variables and functions */
 unsigned int AR9170_BLOCK_NUMBER ; 
 int AR9170_BLOCK_SIZE ; 
 int AR9170_INT_MAGIC_HEADER_SIZE ; 
 int /*<<< orphan*/  AR9170_MAC_REG_DMA_RXQ_ADDR ; 
 int /*<<< orphan*/  AR9170_PTA_REG_DN_DMA_ADDRH ; 
 int /*<<< orphan*/  AR9170_PTA_REG_DN_DMA_ADDRL ; 
 int /*<<< orphan*/  AR9170_PTA_REG_UP_DMA_ADDRH ; 
 int /*<<< orphan*/  AR9170_PTA_REG_UP_DMA_ADDRL ; 
 int /*<<< orphan*/  AR9170_RX_BLOCK_NUMBER ; 
 unsigned int AR9170_TERMINATOR_NUMBER ; 
 unsigned int AR9170_TX_BLOCK_NUMBER ; 
 unsigned int ARRAY_SIZE (TYPE_7__*) ; 
 int /*<<< orphan*/  BUG_ON (int) ; 
 unsigned int CARL9170_INTF_NUM ; 
 int /*<<< orphan*/  DBG (char*,unsigned int,unsigned int,int /*<<< orphan*/ ,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  DESC_PAYLOAD (TYPE_7__*) ; 
 int /*<<< orphan*/  DESC_PAYLOAD_OFF (TYPE_7__*,int) ; 
 unsigned int __AR9170_NUM_TX_QUEUES ; 
 int /*<<< orphan*/  clear_descriptor (TYPE_7__*) ; 
 TYPE_10__ dma_mem ; 
 int /*<<< orphan*/  dma_reclaim (TYPE_6__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fill_descriptor (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 TYPE_8__ fw ; 
 int /*<<< orphan*/  init_queue (TYPE_6__*,TYPE_7__*) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  set (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  set_wlan_txq_dma_addr (unsigned int,int) ; 

void dma_init_descriptors(void)
{
	unsigned int i, j;

	for (i = 0; i < ARRAY_SIZE(dma_mem.terminator); i++)
		clear_descriptor(&dma_mem.terminator[i]);

	/* Assign terminators to DMA queues */
	i = 0;
	init_queue(&fw.pta.up_queue, &dma_mem.terminator[i++]);
	init_queue(&fw.pta.down_queue, &dma_mem.terminator[i++]);
	for (j = 0; j < __AR9170_NUM_TX_QUEUES; j++)
		init_queue(&fw.wlan.tx_queue[j], &dma_mem.terminator[i++]);
	init_queue(&fw.wlan.tx_retry, &dma_mem.terminator[i++]);
	init_queue(&fw.wlan.rx_queue, &dma_mem.terminator[i++]);
	fw.usb.int_desc = &dma_mem.terminator[i++];
	fw.wlan.fw_desc = &dma_mem.terminator[i++];

#ifdef CONFIG_CARL9170FW_CAB_QUEUE
	for (j = 0; j < CARL9170_INTF_NUM; j++)
		init_queue(&fw.wlan.cab_queue[j], &dma_mem.terminator[i++]);
#endif /* CONFIG_CARL9170FW_CAB_QUEUE */

	BUG_ON(AR9170_TERMINATOR_NUMBER != i);

	DBG("Blocks:%d [tx:%d, rx:%d] Terminators:%d/%d\n",
	    AR9170_BLOCK_NUMBER, AR9170_TX_BLOCK_NUMBER,
	    AR9170_RX_BLOCK_NUMBER, AR9170_TERMINATOR_NUMBER, i);

	/* Init descriptors and memory blocks */
	for (i = 0; i < AR9170_BLOCK_NUMBER; i++) {
		fill_descriptor(&dma_mem.block[i], AR9170_BLOCK_SIZE, dma_mem.data[i].data);

		if (i < AR9170_TX_BLOCK_NUMBER)
			dma_reclaim(&fw.pta.down_queue, &dma_mem.block[i]);
		else
			dma_reclaim(&fw.wlan.rx_queue, &dma_mem.block[i]);
	}

	/* Set DMA address registers */
	set(AR9170_PTA_REG_DN_DMA_ADDRH, (uint32_t) fw.pta.down_queue.head >> 16);
	set(AR9170_PTA_REG_DN_DMA_ADDRL, (uint32_t) fw.pta.down_queue.head & 0xffff);
	set(AR9170_PTA_REG_UP_DMA_ADDRH, (uint32_t) fw.pta.up_queue.head >> 16);
	set(AR9170_PTA_REG_UP_DMA_ADDRL, (uint32_t) fw.pta.up_queue.head & 0xffff);

	for (i = 0; i < __AR9170_NUM_TX_QUEUES; i++)
		set_wlan_txq_dma_addr(i, (uint32_t) fw.wlan.tx_queue[i].head);

	set(AR9170_MAC_REG_DMA_RXQ_ADDR, (uint32_t) fw.wlan.rx_queue.head);
	fw.usb.int_desc->dataSize = AR9170_BLOCK_SIZE;
	fw.usb.int_desc->dataAddr = (void *) &dma_mem.reserved.rsp;

	memset(DESC_PAYLOAD(fw.usb.int_desc), 0xff,
	       AR9170_INT_MAGIC_HEADER_SIZE);
	memset(DESC_PAYLOAD_OFF(fw.usb.int_desc, AR9170_INT_MAGIC_HEADER_SIZE),
	       0, AR9170_BLOCK_SIZE - AR9170_INT_MAGIC_HEADER_SIZE);

	/* rsp is now available for use */
	fw.usb.int_desc_available = 1;

	memset(DESC_PAYLOAD(fw.wlan.fw_desc), 0, 128);
	fw.wlan.fw_desc_available = 1;
}