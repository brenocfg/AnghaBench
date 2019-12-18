#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct comedi_device {int dummy; } ;
struct TYPE_2__ {unsigned int* ao_buffer_bus_addr; scalar_t__ plx9080_iobase; } ;

/* Variables and functions */
 scalar_t__ PLX_DMA0_CS_REG ; 
 scalar_t__ PLX_DMA0_PCI_ADDRESS_REG ; 
 unsigned short PLX_DMA_DONE_BIT ; 
 unsigned int prev_ao_dma_index (struct comedi_device*) ; 
 TYPE_1__* priv (struct comedi_device*) ; 
 unsigned short readb (scalar_t__) ; 
 unsigned int readl (scalar_t__) ; 

__attribute__((used)) static int last_ao_dma_load_completed(struct comedi_device *dev)
{
	unsigned int buffer_index;
	unsigned int transfer_address;
	unsigned short dma_status;

	buffer_index = prev_ao_dma_index(dev);
	dma_status = readb(priv(dev)->plx9080_iobase + PLX_DMA0_CS_REG);
	if ((dma_status & PLX_DMA_DONE_BIT) == 0)
		return 0;

	transfer_address =
	    readl(priv(dev)->plx9080_iobase + PLX_DMA0_PCI_ADDRESS_REG);
	if (transfer_address != priv(dev)->ao_buffer_bus_addr[buffer_index])
		return 0;

	return 1;
}