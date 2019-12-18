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
struct scatterlist {long length; int dma_address; long dma_length; } ;
struct device {int dummy; } ;

/* Variables and functions */
 unsigned long PAGE_MASK ; 
 long SG_ENT_PHYS_ADDRESS (struct scatterlist*) ; 
 unsigned int dma_get_max_seg_size (struct device*) ; 

__attribute__((used)) static void
sg_classify(struct device *dev, struct scatterlist *sg, struct scatterlist *end,
	    int virt_ok)
{
	unsigned long next_paddr;
	struct scatterlist *leader;
	long leader_flag, leader_length;
	unsigned int max_seg_size;

	leader = sg;
	leader_flag = 0;
	leader_length = leader->length;
	next_paddr = SG_ENT_PHYS_ADDRESS(leader) + leader_length;

	/* we will not marge sg without device. */
	max_seg_size = dev ? dma_get_max_seg_size(dev) : 0;
	for (++sg; sg < end; ++sg) {
		unsigned long addr, len;
		addr = SG_ENT_PHYS_ADDRESS(sg);
		len = sg->length;

		if (leader_length + len > max_seg_size)
			goto new_segment;

		if (next_paddr == addr) {
			sg->dma_address = -1;
			leader_length += len;
		} else if (((next_paddr | addr) & ~PAGE_MASK) == 0 && virt_ok) {
			sg->dma_address = -2;
			leader_flag = 1;
			leader_length += len;
		} else {
new_segment:
			leader->dma_address = leader_flag;
			leader->dma_length = leader_length;
			leader = sg;
			leader_flag = 0;
			leader_length = len;
		}

		next_paddr = addr + len;
	}

	leader->dma_address = leader_flag;
	leader->dma_length = leader_length;
}