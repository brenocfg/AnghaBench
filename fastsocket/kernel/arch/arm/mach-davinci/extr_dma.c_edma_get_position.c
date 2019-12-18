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
struct edmacc_param {int /*<<< orphan*/  dst; int /*<<< orphan*/  src; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 unsigned int EDMA_CHAN_SLOT (unsigned int) ; 
 unsigned int EDMA_CTLR (unsigned int) ; 
 int /*<<< orphan*/  EDMA_CTLR_CHAN (unsigned int,unsigned int) ; 
 int /*<<< orphan*/  edma_read_slot (int /*<<< orphan*/ ,struct edmacc_param*) ; 

void edma_get_position(unsigned slot, dma_addr_t *src, dma_addr_t *dst)
{
	struct edmacc_param temp;
	unsigned ctlr;

	ctlr = EDMA_CTLR(slot);
	slot = EDMA_CHAN_SLOT(slot);

	edma_read_slot(EDMA_CTLR_CHAN(ctlr, slot), &temp);
	if (src != NULL)
		*src = temp.src;
	if (dst != NULL)
		*dst = temp.dst;
}