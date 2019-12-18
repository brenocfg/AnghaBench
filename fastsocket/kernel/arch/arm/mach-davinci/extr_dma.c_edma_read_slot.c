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
struct edmacc_param {int dummy; } ;
struct TYPE_2__ {unsigned int num_slots; } ;

/* Variables and functions */
 unsigned int EDMA_CHAN_SLOT (unsigned int) ; 
 unsigned int EDMA_CTLR (unsigned int) ; 
 scalar_t__ PARM_OFFSET (unsigned int) ; 
 int /*<<< orphan*/  PARM_SIZE ; 
 TYPE_1__** edma_info ; 
 scalar_t__* edmacc_regs_base ; 
 int /*<<< orphan*/  memcpy_fromio (struct edmacc_param*,scalar_t__,int /*<<< orphan*/ ) ; 

void edma_read_slot(unsigned slot, struct edmacc_param *param)
{
	unsigned ctlr;

	ctlr = EDMA_CTLR(slot);
	slot = EDMA_CHAN_SLOT(slot);

	if (slot >= edma_info[ctlr]->num_slots)
		return;
	memcpy_fromio(param, edmacc_regs_base[ctlr] + PARM_OFFSET(slot),
			PARM_SIZE);
}