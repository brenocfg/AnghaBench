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
struct TYPE_2__ {int ao_dma_index; } ;

/* Variables and functions */
 int AO_DMA_RING_COUNT ; 
 TYPE_1__* priv (struct comedi_device*) ; 

__attribute__((used)) static inline unsigned int prev_ao_dma_index(struct comedi_device *dev)
{
	unsigned int buffer_index;

	if (priv(dev)->ao_dma_index == 0)
		buffer_index = AO_DMA_RING_COUNT - 1;
	else
		buffer_index = priv(dev)->ao_dma_index - 1;
	return buffer_index;
}