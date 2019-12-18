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
struct TYPE_2__ {int* dma_configuration_soft_copies; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMAConfigRegister ; 
 int /*<<< orphan*/  IOConfigReg (unsigned int) ; 
 unsigned int MAX_DMA_CHANNEL ; 
 unsigned int NUM_PFI_CHANNELS ; 
 int dma_select_bits (unsigned int,int /*<<< orphan*/ ) ; 
 int dma_select_mask (unsigned int) ; 
 int /*<<< orphan*/  dma_selection_none ; 
 int /*<<< orphan*/  ni_660x_write_register (struct comedi_device*,int,int,int /*<<< orphan*/ ) ; 
 TYPE_1__* private (struct comedi_device*) ; 

__attribute__((used)) static void init_tio_chip(struct comedi_device *dev, int chipset)
{
	unsigned i;

	/*  init dma configuration register */
	private(dev)->dma_configuration_soft_copies[chipset] = 0;
	for (i = 0; i < MAX_DMA_CHANNEL; ++i) {
		private(dev)->dma_configuration_soft_copies[chipset] |=
		    dma_select_bits(i, dma_selection_none) & dma_select_mask(i);
	}
	ni_660x_write_register(dev, chipset,
			       private(dev)->
			       dma_configuration_soft_copies[chipset],
			       DMAConfigRegister);
	for (i = 0; i < NUM_PFI_CHANNELS; ++i) {
		ni_660x_write_register(dev, chipset, 0, IOConfigReg(i));
	}
}