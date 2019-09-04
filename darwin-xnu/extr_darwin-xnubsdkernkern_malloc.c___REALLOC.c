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
typedef  int /*<<< orphan*/  vm_allocation_site_t ;

/* Variables and functions */
 int /*<<< orphan*/  MIN (size_t,size_t) ; 
 int M_ZERO ; 
 int /*<<< orphan*/  _FREE (void*,int) ; 
 void* __MALLOC (size_t,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bcopy (void*,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bzero (void*,size_t) ; 
 size_t kalloc_bucket_size (size_t) ; 
 size_t kalloc_size (void*) ; 

void *
__REALLOC(
	void		*addr,
	size_t		size,
	int		type,
	int		flags,
	vm_allocation_site_t *site)
{
	void		*newaddr;
	size_t		alloc;

	/* realloc(NULL, ...) is equivalent to malloc(...) */
	if (addr == NULL)
		return (__MALLOC(size, type, flags, site));

	alloc = kalloc_size(addr);
	/* 
	 * Find out the size of the bucket in which the new sized allocation 
	 * would land. If it matches the bucket of the original allocation, 
	 * simply return the address.
	 */
	if (kalloc_bucket_size(size) == alloc) {
		if (flags & M_ZERO) { 
			if (alloc < size)
				bzero(addr + alloc, (size - alloc));
			else
				bzero(addr + size, (alloc - size));
		}
		return addr;
	}

	/* Allocate a new, bigger (or smaller) block */
	if ((newaddr = __MALLOC(size, type, flags, site)) == NULL)
		return (NULL);

	/* Copy over original contents */
	bcopy(addr, newaddr, MIN(size, alloc));
	_FREE(addr, type);

	return (newaddr);
}