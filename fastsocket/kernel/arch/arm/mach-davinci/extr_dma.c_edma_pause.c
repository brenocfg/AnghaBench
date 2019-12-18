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
struct TYPE_2__ {unsigned int num_channels; } ;

/* Variables and functions */
 unsigned int EDMA_CHAN_SLOT (unsigned int) ; 
 unsigned int EDMA_CTLR (unsigned int) ; 
 int /*<<< orphan*/  SH_EECR ; 
 TYPE_1__** edma_info ; 
 int /*<<< orphan*/  edma_shadow0_write_array (unsigned int,int /*<<< orphan*/ ,unsigned int,unsigned int) ; 

void edma_pause(unsigned channel)
{
	unsigned ctlr;

	ctlr = EDMA_CTLR(channel);
	channel = EDMA_CHAN_SLOT(channel);

	if (channel < edma_info[ctlr]->num_channels) {
		unsigned int mask = (1 << (channel & 0x1f));

		edma_shadow0_write_array(ctlr, SH_EECR, channel >> 5, mask);
	}
}