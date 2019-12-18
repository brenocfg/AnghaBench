#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct comedi_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  G0_G1_Select ; 
 unsigned int GPCT_DMA_Select_Bits (unsigned int,int) ; 
 int /*<<< orphan*/  GPCT_DMA_Select_Mask (unsigned int) ; 
 int /*<<< orphan*/  ni_set_bitfield (struct comedi_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static inline void ni_set_gpct_dma_channel(struct comedi_device *dev,
					   unsigned gpct_index,
					   int mite_channel)
{
	unsigned bitfield;

	if (mite_channel >= 0) {
		bitfield = GPCT_DMA_Select_Bits(gpct_index, mite_channel);
	} else {
		bitfield = 0;
	}
	ni_set_bitfield(dev, G0_G1_Select, GPCT_DMA_Select_Mask(gpct_index),
			bitfield);
}