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
typedef  size_t ssize_t ;

/* Variables and functions */
 unsigned long PAGE_SHIFT ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 void* __ioremap (unsigned long,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* __va (unsigned long) ; 
 size_t copy_oldmem_vaddr (void*,char*,size_t,unsigned long,int) ; 
 int /*<<< orphan*/  iounmap (void*) ; 
 unsigned long max_pfn ; 
 size_t min (size_t,int /*<<< orphan*/ ) ; 

ssize_t copy_oldmem_page(unsigned long pfn, char *buf,
			size_t csize, unsigned long offset, int userbuf)
{
	void  *vaddr;

	if (!csize)
		return 0;

	csize = min(csize, PAGE_SIZE);

	if (pfn < max_pfn) {
		vaddr = __va(pfn << PAGE_SHIFT);
		csize = copy_oldmem_vaddr(vaddr, buf, csize, offset, userbuf);
	} else {
		vaddr = __ioremap(pfn << PAGE_SHIFT, PAGE_SIZE, 0);
		csize = copy_oldmem_vaddr(vaddr, buf, csize, offset, userbuf);
		iounmap(vaddr);
	}

	return csize;
}