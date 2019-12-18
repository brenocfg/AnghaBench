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

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int ni_stc_dma_channel_select_bitfield (unsigned int) ; 

__attribute__((used)) static inline unsigned GPCT_DMA_Select_Bits(unsigned gpct_index,
					    unsigned mite_channel)
{
	BUG_ON(gpct_index > 1);
	return ni_stc_dma_channel_select_bitfield(mite_channel) << (4 *
								    gpct_index);
}