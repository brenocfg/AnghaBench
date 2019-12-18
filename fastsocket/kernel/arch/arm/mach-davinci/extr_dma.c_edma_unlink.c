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
 TYPE_1__** edma_info ; 
 int /*<<< orphan*/  edma_parm_or (unsigned int,int /*<<< orphan*/ ,unsigned int,int) ; 

void edma_unlink(unsigned from)
{
	unsigned ctlr;

	ctlr = EDMA_CTLR(from);
	from = EDMA_CHAN_SLOT(from);

	if (from >= edma_info[ctlr]->num_slots)
		return;
	edma_parm_or(ctlr, PARM_LINK_BCNTRLD, from, 0xffff);
}