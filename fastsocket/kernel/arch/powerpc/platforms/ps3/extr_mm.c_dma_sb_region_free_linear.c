#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct ps3_dma_region {unsigned long offset; unsigned long len; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;
struct TYPE_5__ {unsigned long size; unsigned long base; } ;
struct TYPE_4__ {unsigned long base; } ;
struct TYPE_6__ {TYPE_2__ rm; TYPE_1__ r1; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  dma_sb_lpar_to_bus (struct ps3_dma_region*,unsigned long) ; 
 int dma_sb_region_free (struct ps3_dma_region*) ; 
 int dma_sb_unmap_area (struct ps3_dma_region*,int /*<<< orphan*/ ,unsigned long) ; 
 TYPE_3__ map ; 

__attribute__((used)) static int dma_sb_region_free_linear(struct ps3_dma_region *r)
{
	int result;
	dma_addr_t bus_addr;
	unsigned long len, lpar_addr;

	if (r->offset < map.rm.size) {
		/* Unmap (part of) 1st RAM chunk */
		lpar_addr = map.rm.base + r->offset;
		len = map.rm.size - r->offset;
		if (len > r->len)
			len = r->len;
		bus_addr = dma_sb_lpar_to_bus(r, lpar_addr);
		result = dma_sb_unmap_area(r, bus_addr, len);
		BUG_ON(result);
	}

	if (r->offset + r->len > map.rm.size) {
		/* Unmap (part of) 2nd RAM chunk */
		lpar_addr = map.r1.base;
		len = r->len;
		if (r->offset >= map.rm.size)
			lpar_addr += r->offset - map.rm.size;
		else
			len -= map.rm.size - r->offset;
		bus_addr = dma_sb_lpar_to_bus(r, lpar_addr);
		result = dma_sb_unmap_area(r, bus_addr, len);
		BUG_ON(result);
	}

	result = dma_sb_region_free(r);
	BUG_ON(result);

	return result;
}