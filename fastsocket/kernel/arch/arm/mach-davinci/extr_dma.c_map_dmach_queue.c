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
typedef  enum dma_event_q { ____Placeholder_dma_event_q } dma_event_q ;
struct TYPE_2__ {int default_queue; } ;

/* Variables and functions */
 int /*<<< orphan*/  EDMA_DMAQNUM ; 
 int EVENTQ_DEFAULT ; 
 TYPE_1__** edma_info ; 
 int /*<<< orphan*/  edma_modify_array (unsigned int,int /*<<< orphan*/ ,unsigned int,int,int) ; 

__attribute__((used)) static void map_dmach_queue(unsigned ctlr, unsigned ch_no,
		enum dma_event_q queue_no)
{
	int bit = (ch_no & 0x7) * 4;

	/* default to low priority queue */
	if (queue_no == EVENTQ_DEFAULT)
		queue_no = edma_info[ctlr]->default_queue;

	queue_no &= 7;
	edma_modify_array(ctlr, EDMA_DMAQNUM, (ch_no >> 3),
			~(0x7 << bit), queue_no << bit);
}