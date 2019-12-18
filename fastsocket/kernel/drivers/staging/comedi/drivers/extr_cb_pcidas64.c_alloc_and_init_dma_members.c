#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct plx_dma_desc {int dummy; } ;
struct comedi_device {int dummy; } ;
struct TYPE_10__ {scalar_t__ layout; } ;
struct TYPE_9__ {int* ai_buffer_bus_addr; int* ao_buffer_bus_addr; int ai_dma_desc_bus_addr; int ao_dma_desc_bus_addr; int local1_iobase; int local0_iobase; TYPE_2__* ao_dma_desc; TYPE_1__* ai_dma_desc; int /*<<< orphan*/  hw_dev; int /*<<< orphan*/ ** ao_buffer; int /*<<< orphan*/ ** ai_buffer; } ;
struct TYPE_8__ {void* next; void* transfer_size; void* local_start_addr; void* pci_start_addr; } ;
struct TYPE_7__ {void* next; void* transfer_size; void* local_start_addr; void* pci_start_addr; } ;

/* Variables and functions */
 int ADC_FIFO_REG ; 
 int AO_DMA_RING_COUNT ; 
 int DAC_FIFO_REG ; 
 int /*<<< orphan*/  DEBUG_PRINT (char*,int) ; 
 int DMA_BUFFER_SIZE ; 
 int ENOMEM ; 
 scalar_t__ LAYOUT_4020 ; 
 int PLX_DESC_IN_PCI_BIT ; 
 int PLX_INTR_TERM_COUNT ; 
 int PLX_XFER_LOCAL_TO_PCI ; 
 int ai_dma_ring_count (TYPE_4__*) ; 
 scalar_t__ ao_cmd_is_supported (TYPE_4__*) ; 
 TYPE_4__* board (struct comedi_device*) ; 
 void* cpu_to_le32 (int) ; 
 void* pci_alloc_consistent (int /*<<< orphan*/ ,int,int*) ; 
 TYPE_3__* priv (struct comedi_device*) ; 

int alloc_and_init_dma_members(struct comedi_device *dev)
{
	int i;

	/*  alocate pci dma buffers */
	for (i = 0; i < ai_dma_ring_count(board(dev)); i++) {
		priv(dev)->ai_buffer[i] =
		    pci_alloc_consistent(priv(dev)->hw_dev, DMA_BUFFER_SIZE,
					 &priv(dev)->ai_buffer_bus_addr[i]);
		if (priv(dev)->ai_buffer[i] == NULL) {
			return -ENOMEM;
		}
	}
	for (i = 0; i < AO_DMA_RING_COUNT; i++) {
		if (ao_cmd_is_supported(board(dev))) {
			priv(dev)->ao_buffer[i] =
			    pci_alloc_consistent(priv(dev)->hw_dev,
						 DMA_BUFFER_SIZE,
						 &priv(dev)->
						 ao_buffer_bus_addr[i]);
			if (priv(dev)->ao_buffer[i] == NULL) {
				return -ENOMEM;
			}
		}
	}
	/*  allocate dma descriptors */
	priv(dev)->ai_dma_desc =
	    pci_alloc_consistent(priv(dev)->hw_dev,
				 sizeof(struct plx_dma_desc) *
				 ai_dma_ring_count(board(dev)),
				 &priv(dev)->ai_dma_desc_bus_addr);
	if (priv(dev)->ai_dma_desc == NULL) {
		return -ENOMEM;
	}
	DEBUG_PRINT("ai dma descriptors start at bus addr 0x%x\n",
		    priv(dev)->ai_dma_desc_bus_addr);
	if (ao_cmd_is_supported(board(dev))) {
		priv(dev)->ao_dma_desc =
		    pci_alloc_consistent(priv(dev)->hw_dev,
					 sizeof(struct plx_dma_desc) *
					 AO_DMA_RING_COUNT,
					 &priv(dev)->ao_dma_desc_bus_addr);
		if (priv(dev)->ao_dma_desc == NULL) {
			return -ENOMEM;
		}
		DEBUG_PRINT("ao dma descriptors start at bus addr 0x%x\n",
			    priv(dev)->ao_dma_desc_bus_addr);
	}
	/*  initialize dma descriptors */
	for (i = 0; i < ai_dma_ring_count(board(dev)); i++) {
		priv(dev)->ai_dma_desc[i].pci_start_addr =
		    cpu_to_le32(priv(dev)->ai_buffer_bus_addr[i]);
		if (board(dev)->layout == LAYOUT_4020)
			priv(dev)->ai_dma_desc[i].local_start_addr =
			    cpu_to_le32(priv(dev)->local1_iobase +
					ADC_FIFO_REG);
		else
			priv(dev)->ai_dma_desc[i].local_start_addr =
			    cpu_to_le32(priv(dev)->local0_iobase +
					ADC_FIFO_REG);
		priv(dev)->ai_dma_desc[i].transfer_size = cpu_to_le32(0);
		priv(dev)->ai_dma_desc[i].next =
		    cpu_to_le32((priv(dev)->ai_dma_desc_bus_addr + ((i +
								     1) %
								    ai_dma_ring_count
								    (board
								     (dev))) *
				 sizeof(priv(dev)->ai_dma_desc[0])) |
				PLX_DESC_IN_PCI_BIT | PLX_INTR_TERM_COUNT |
				PLX_XFER_LOCAL_TO_PCI);
	}
	if (ao_cmd_is_supported(board(dev))) {
		for (i = 0; i < AO_DMA_RING_COUNT; i++) {
			priv(dev)->ao_dma_desc[i].pci_start_addr =
			    cpu_to_le32(priv(dev)->ao_buffer_bus_addr[i]);
			priv(dev)->ao_dma_desc[i].local_start_addr =
			    cpu_to_le32(priv(dev)->local0_iobase +
					DAC_FIFO_REG);
			priv(dev)->ao_dma_desc[i].transfer_size =
			    cpu_to_le32(0);
			priv(dev)->ao_dma_desc[i].next =
			    cpu_to_le32((priv(dev)->ao_dma_desc_bus_addr +
					 ((i + 1) % (AO_DMA_RING_COUNT)) *
					 sizeof(priv(dev)->ao_dma_desc[0])) |
					PLX_DESC_IN_PCI_BIT |
					PLX_INTR_TERM_COUNT);
		}
	}
	return 0;
}