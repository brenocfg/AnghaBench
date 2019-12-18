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
struct pcpu_chunk {int /*<<< orphan*/  populated; } ;
struct page {int dummy; } ;
typedef  int /*<<< orphan*/  pages ;

/* Variables and functions */
 int BITS_TO_LONGS (int) ; 
 int /*<<< orphan*/  bitmap_copy (unsigned long*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset (struct page**,int /*<<< orphan*/ ,size_t) ; 
 void* pcpu_mem_alloc (size_t) ; 
 int pcpu_nr_units ; 
 int pcpu_unit_pages ; 

__attribute__((used)) static struct page **pcpu_get_pages_and_bitmap(struct pcpu_chunk *chunk,
					       unsigned long **bitmapp,
					       bool may_alloc)
{
	static struct page **pages;
	static unsigned long *bitmap;
	size_t pages_size = pcpu_nr_units * pcpu_unit_pages * sizeof(pages[0]);
	size_t bitmap_size = BITS_TO_LONGS(pcpu_unit_pages) *
			     sizeof(unsigned long);

	if (!pages || !bitmap) {
		if (may_alloc && !pages)
			pages = pcpu_mem_alloc(pages_size);
		if (may_alloc && !bitmap)
			bitmap = pcpu_mem_alloc(bitmap_size);
		if (!pages || !bitmap)
			return NULL;
	}

	memset(pages, 0, pages_size);
	bitmap_copy(bitmap, chunk->populated, pcpu_unit_pages);

	*bitmapp = bitmap;
	return pages;
}