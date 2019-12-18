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
struct TYPE_2__ {scalar_t__ plx9080_iobase; } ;

/* Variables and functions */
 scalar_t__ PLX_DMA0_DESCRIPTOR_REG ; 
 scalar_t__ PLX_DMA0_LOCAL_ADDRESS_REG ; 
 scalar_t__ PLX_DMA0_PCI_ADDRESS_REG ; 
 scalar_t__ PLX_DMA0_TRANSFER_SIZE_REG ; 
 scalar_t__ PLX_DMA1_DESCRIPTOR_REG ; 
 scalar_t__ PLX_DMA1_LOCAL_ADDRESS_REG ; 
 scalar_t__ PLX_DMA1_PCI_ADDRESS_REG ; 
 scalar_t__ PLX_DMA1_TRANSFER_SIZE_REG ; 
 TYPE_1__* priv (struct comedi_device*) ; 
 int /*<<< orphan*/  writel (unsigned int,scalar_t__) ; 

__attribute__((used)) static inline void load_first_dma_descriptor(struct comedi_device *dev,
					     unsigned int dma_channel,
					     unsigned int descriptor_bits)
{
	/* The transfer size, pci address, and local address registers
	 * are supposedly unused during chained dma,
	 * but I have found that left over values from last operation
	 * occasionally cause problems with transfer of first dma
	 * block.  Initializing them to zero seems to fix the problem. */
	if (dma_channel) {
		writel(0,
		       priv(dev)->plx9080_iobase + PLX_DMA1_TRANSFER_SIZE_REG);
		writel(0, priv(dev)->plx9080_iobase + PLX_DMA1_PCI_ADDRESS_REG);
		writel(0,
		       priv(dev)->plx9080_iobase + PLX_DMA1_LOCAL_ADDRESS_REG);
		writel(descriptor_bits,
		       priv(dev)->plx9080_iobase + PLX_DMA1_DESCRIPTOR_REG);
	} else {
		writel(0,
		       priv(dev)->plx9080_iobase + PLX_DMA0_TRANSFER_SIZE_REG);
		writel(0, priv(dev)->plx9080_iobase + PLX_DMA0_PCI_ADDRESS_REG);
		writel(0,
		       priv(dev)->plx9080_iobase + PLX_DMA0_LOCAL_ADDRESS_REG);
		writel(descriptor_bits,
		       priv(dev)->plx9080_iobase + PLX_DMA0_DESCRIPTOR_REG);
	}
}