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
struct TYPE_2__ {unsigned int num_channels; int /*<<< orphan*/  edma_noevent; } ;

/* Variables and functions */
 unsigned int EDMA_CHAN_SLOT (unsigned int) ; 
 unsigned int EDMA_CTLR (unsigned int) ; 
 int /*<<< orphan*/  EDMA_EMCR ; 
 int EINVAL ; 
 int /*<<< orphan*/  SH_EER ; 
 int /*<<< orphan*/  SH_EESR ; 
 int /*<<< orphan*/  SH_ER ; 
 int /*<<< orphan*/  SH_ESR ; 
 int /*<<< orphan*/  SH_SECR ; 
 TYPE_1__** edma_info ; 
 int /*<<< orphan*/  edma_shadow0_read_array (unsigned int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  edma_shadow0_write_array (unsigned int,int /*<<< orphan*/ ,int,unsigned int) ; 
 int /*<<< orphan*/  edma_write_array (unsigned int,int /*<<< orphan*/ ,int,unsigned int) ; 
 int /*<<< orphan*/  pr_debug (char*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ test_bit (unsigned int,int /*<<< orphan*/ ) ; 

int edma_start(unsigned channel)
{
	unsigned ctlr;

	ctlr = EDMA_CTLR(channel);
	channel = EDMA_CHAN_SLOT(channel);

	if (channel < edma_info[ctlr]->num_channels) {
		int j = channel >> 5;
		unsigned int mask = (1 << (channel & 0x1f));

		/* EDMA channels without event association */
		if (test_bit(channel, edma_info[ctlr]->edma_noevent)) {
			pr_debug("EDMA: ESR%d %08x\n", j,
				edma_shadow0_read_array(ctlr, SH_ESR, j));
			edma_shadow0_write_array(ctlr, SH_ESR, j, mask);
			return 0;
		}

		/* EDMA channel with event association */
		pr_debug("EDMA: ER%d %08x\n", j,
			edma_shadow0_read_array(ctlr, SH_ER, j));
		/* Clear any pending error */
		edma_write_array(ctlr, EDMA_EMCR, j, mask);
		/* Clear any SER */
		edma_shadow0_write_array(ctlr, SH_SECR, j, mask);
		edma_shadow0_write_array(ctlr, SH_EESR, j, mask);
		pr_debug("EDMA: EER%d %08x\n", j,
			edma_shadow0_read_array(ctlr, SH_EER, j));
		return 0;
	}

	return -EINVAL;
}