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
 int /*<<< orphan*/  EDMA_CCERRCLR ; 
 unsigned int EDMA_CHAN_SLOT (unsigned int) ; 
 unsigned int EDMA_CTLR (unsigned int) ; 
 int /*<<< orphan*/  EDMA_EMCR ; 
 int /*<<< orphan*/  EDMA_EMR ; 
 int /*<<< orphan*/  SH_ECR ; 
 int /*<<< orphan*/  SH_SECR ; 
 TYPE_1__** edma_info ; 
 int /*<<< orphan*/  edma_read_array (unsigned int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  edma_shadow0_write_array (unsigned int,int /*<<< orphan*/ ,int,unsigned int) ; 
 int /*<<< orphan*/  edma_write (unsigned int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  edma_write_array (unsigned int,int /*<<< orphan*/ ,int,unsigned int) ; 
 int /*<<< orphan*/  pr_debug (char*,int,int /*<<< orphan*/ ) ; 

void edma_clean_channel(unsigned channel)
{
	unsigned ctlr;

	ctlr = EDMA_CTLR(channel);
	channel = EDMA_CHAN_SLOT(channel);

	if (channel < edma_info[ctlr]->num_channels) {
		int j = (channel >> 5);
		unsigned int mask = 1 << (channel & 0x1f);

		pr_debug("EDMA: EMR%d %08x\n", j,
				edma_read_array(ctlr, EDMA_EMR, j));
		edma_shadow0_write_array(ctlr, SH_ECR, j, mask);
		/* Clear the corresponding EMR bits */
		edma_write_array(ctlr, EDMA_EMCR, j, mask);
		/* Clear any SER */
		edma_shadow0_write_array(ctlr, SH_SECR, j, mask);
		edma_write(ctlr, EDMA_CCERRCLR, (1 << 16) | 0x3);
	}
}