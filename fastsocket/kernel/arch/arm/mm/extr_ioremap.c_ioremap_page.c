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
struct mem_type {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  __phys_to_pfn (unsigned long) ; 
 int remap_area_pages (unsigned long,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct mem_type const*) ; 

int ioremap_page(unsigned long virt, unsigned long phys,
		 const struct mem_type *mtype)
{
	return remap_area_pages(virt, __phys_to_pfn(phys), PAGE_SIZE, mtype);
}