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
struct dma_chunk {unsigned long size; void* addr; } ;

/* Variables and functions */
 unsigned long PAGE_MASK ; 
 scalar_t__ PAGE_SIZE ; 
 void* iseries_hv_addr (unsigned char*) ; 
 void* min (unsigned long,scalar_t__) ; 

__attribute__((used)) static inline void veth_build_dma_list(struct dma_chunk *list,
				       unsigned char *p, unsigned long length)
{
	unsigned long done;
	int i = 1;

	/* FIXME: skbs are continguous in real addresses.  Do we
	 * really need to break it into PAGE_SIZE chunks, or can we do
	 * it just at the granularity of iSeries real->absolute
	 * mapping?  Indeed, given the way the allocator works, can we
	 * count on them being absolutely contiguous? */
	list[0].addr = iseries_hv_addr(p);
	list[0].size = min(length,
			   PAGE_SIZE - ((unsigned long)p & ~PAGE_MASK));

	done = list[0].size;
	while (done < length) {
		list[i].addr = iseries_hv_addr(p + done);
		list[i].size = min(length-done, PAGE_SIZE);
		done += list[i].size;
		i++;
	}
}