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
 size_t EFAULT ; 
 unsigned long PAGE_SHIFT ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 scalar_t__ copy_to_user (char*,void*,size_t) ; 
 void* ioremap (unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iounmap (void*) ; 
 int /*<<< orphan*/  memcpy (char*,void*,size_t) ; 

ssize_t copy_oldmem_page(unsigned long pfn, char *buf,
                               size_t csize, unsigned long offset, int userbuf)
{
	void  *vaddr;

	if (!csize)
		return 0;

	vaddr = ioremap(pfn << PAGE_SHIFT, PAGE_SIZE);

	if (userbuf) {
		if (copy_to_user(buf, (vaddr + offset), csize)) {
			iounmap(vaddr);
			return -EFAULT;
		}
	} else
	memcpy(buf, (vaddr + offset), csize);

	iounmap(vaddr);
	return csize;
}