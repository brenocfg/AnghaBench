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
struct scatterlist {long length; long offset; } ;

/* Variables and functions */
 int EFAULT ; 
 unsigned long PAGE_SHIFT ; 
 unsigned long page_to_pfn (int /*<<< orphan*/ ) ; 
 int pages_in_region (long,long) ; 
 int /*<<< orphan*/  sg_page (struct scatterlist*) ; 

__attribute__((used)) static int sg_count_one(struct scatterlist *sg)
{
	unsigned long base = page_to_pfn(sg_page(sg)) << PAGE_SHIFT;
	long len = sg->length;

	if ((sg->offset | len) & (8UL - 1))
		return -EFAULT;

	return pages_in_region(base + sg->offset, len);
}