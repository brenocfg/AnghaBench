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
struct TYPE_2__ {unsigned int num_slots; } ;

/* Variables and functions */
 unsigned int EDMA_CHAN_SLOT (unsigned int) ; 
 unsigned int EDMA_CTLR (unsigned int) ; 
 int /*<<< orphan*/  PARM_LINK_BCNTRLD ; 
 int /*<<< orphan*/  PARM_OFFSET (unsigned int) ; 
 TYPE_1__** edma_info ; 
 int /*<<< orphan*/  edma_parm_modify (unsigned int,int /*<<< orphan*/ ,unsigned int,int,int /*<<< orphan*/ ) ; 

void edma_link(unsigned from, unsigned to)
{
	unsigned ctlr_from, ctlr_to;

	ctlr_from = EDMA_CTLR(from);
	from = EDMA_CHAN_SLOT(from);
	ctlr_to = EDMA_CTLR(to);
	to = EDMA_CHAN_SLOT(to);

	if (from >= edma_info[ctlr_from]->num_slots)
		return;
	if (to >= edma_info[ctlr_to]->num_slots)
		return;
	edma_parm_modify(ctlr_from, PARM_LINK_BCNTRLD, from, 0xffff0000,
				PARM_OFFSET(to));
}