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
struct page {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  copy_user_page_asm (void*,void*) ; 
 int /*<<< orphan*/  flush_kernel_dcache_page_asm (void*) ; 
 int /*<<< orphan*/  parisc_requires_coherency () ; 

void copy_user_page(void *vto, void *vfrom, unsigned long vaddr,
		    struct page *pg)
{
	/* no coherency needed (all in kmap/kunmap) */
	copy_user_page_asm(vto, vfrom);
	if (!parisc_requires_coherency())
		flush_kernel_dcache_page_asm(vto);
}