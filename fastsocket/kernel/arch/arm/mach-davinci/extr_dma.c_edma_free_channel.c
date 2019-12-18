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
struct TYPE_2__ {unsigned int num_channels; int /*<<< orphan*/  edma_inuse; } ;

/* Variables and functions */
 unsigned int EDMA_CHAN_SLOT (unsigned int) ; 
 unsigned int EDMA_CTLR (unsigned int) ; 
 scalar_t__ PARM_OFFSET (unsigned int) ; 
 int /*<<< orphan*/  PARM_SIZE ; 
 int /*<<< orphan*/  clear_bit (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dummy_paramset ; 
 TYPE_1__** edma_info ; 
 scalar_t__* edmacc_regs_base ; 
 int /*<<< orphan*/  memcpy_toio (scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setup_dma_interrupt (unsigned int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void edma_free_channel(unsigned channel)
{
	unsigned ctlr;

	ctlr = EDMA_CTLR(channel);
	channel = EDMA_CHAN_SLOT(channel);

	if (channel >= edma_info[ctlr]->num_channels)
		return;

	setup_dma_interrupt(channel, NULL, NULL);
	/* REVISIT should probably take out of shadow region 0 */

	memcpy_toio(edmacc_regs_base[ctlr] + PARM_OFFSET(channel),
			&dummy_paramset, PARM_SIZE);
	clear_bit(channel, edma_info[ctlr]->edma_inuse);
}