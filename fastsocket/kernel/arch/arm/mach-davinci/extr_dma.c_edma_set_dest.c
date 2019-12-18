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
typedef  enum fifo_width { ____Placeholder_fifo_width } fifo_width ;
typedef  enum address_mode { ____Placeholder_address_mode } address_mode ;
typedef  unsigned int dma_addr_t ;
struct TYPE_2__ {unsigned int num_slots; } ;

/* Variables and functions */
 int DAM ; 
 unsigned int EDMA_CHAN_SLOT (unsigned int) ; 
 unsigned int EDMA_CTLR (unsigned int) ; 
 unsigned int EDMA_FWID ; 
 int /*<<< orphan*/  PARM_DST ; 
 int /*<<< orphan*/  PARM_OPT ; 
 TYPE_1__** edma_info ; 
 unsigned int edma_parm_read (unsigned int,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  edma_parm_write (unsigned int,int /*<<< orphan*/ ,unsigned int,unsigned int) ; 

void edma_set_dest(unsigned slot, dma_addr_t dest_port,
				 enum address_mode mode, enum fifo_width width)
{
	unsigned ctlr;

	ctlr = EDMA_CTLR(slot);
	slot = EDMA_CHAN_SLOT(slot);

	if (slot < edma_info[ctlr]->num_slots) {
		unsigned int i = edma_parm_read(ctlr, PARM_OPT, slot);

		if (mode) {
			/* set DAM and program FWID */
			i = (i & ~(EDMA_FWID)) | (DAM | ((width & 0x7) << 8));
		} else {
			/* clear DAM */
			i &= ~DAM;
		}
		edma_parm_write(ctlr, PARM_OPT, slot, i);
		/* set the destination port address
		   in dest register of param structure */
		edma_parm_write(ctlr, PARM_DST, slot, dest_port);
	}
}