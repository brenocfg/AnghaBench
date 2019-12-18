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
 int /*<<< orphan*/  DEBUG_PRINT (char*,unsigned int) ; 
 scalar_t__ PLX_DMA0_DESCRIPTOR_REG ; 
 unsigned int PLX_END_OF_CHAIN_BIT ; 
 int /*<<< orphan*/  dma_start_sync (struct comedi_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  load_first_dma_descriptor (struct comedi_device*,int /*<<< orphan*/ ,unsigned int) ; 
 TYPE_1__* priv (struct comedi_device*) ; 
 unsigned int readl (scalar_t__) ; 

__attribute__((used)) static void restart_ao_dma(struct comedi_device *dev)
{
	unsigned int dma_desc_bits;

	dma_desc_bits =
	    readl(priv(dev)->plx9080_iobase + PLX_DMA0_DESCRIPTOR_REG);
	dma_desc_bits &= ~PLX_END_OF_CHAIN_BIT;
	DEBUG_PRINT("restarting ao dma, descriptor reg 0x%x\n", dma_desc_bits);
	load_first_dma_descriptor(dev, 0, dma_desc_bits);

	dma_start_sync(dev, 0);
}