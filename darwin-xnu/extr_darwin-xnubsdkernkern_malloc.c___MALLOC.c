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
typedef  size_t vm_size_t ;
typedef  int /*<<< orphan*/  vm_allocation_site_t ;
typedef  int /*<<< orphan*/  uint64_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int M_LAST ; 
 int M_NOWAIT ; 
 int M_NULL ; 
 int M_ZERO ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  bzero (void*,size_t) ; 
 scalar_t__ kalloc_canblock (size_t*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  panic (char*,...) ; 

void *
__MALLOC(
	size_t		size,
	int		type,
	int		flags,
	vm_allocation_site_t *site)
{
	void 	*addr = NULL;
	vm_size_t 	msize = size;

	if (type >= M_LAST)
		panic("_malloc TYPE");

	if (size == 0)
		return (NULL);

	if (msize != size) {
		panic("Requested size to __MALLOC is too large (%llx)!\n", (uint64_t)size);
	}

	if (flags & M_NOWAIT) {
		addr = (void *)kalloc_canblock(&msize, FALSE, site);
	} else {
		addr = (void *)kalloc_canblock(&msize, TRUE, site);
		if (addr == NULL) {
			/*
			 * We get here when the caller told us to block waiting for memory, but
			 * kalloc said there's no memory left to get.  Generally, this means there's a 
			 * leak or the caller asked for an impossibly large amount of memory. If the caller
			 * is expecting a NULL return code then it should explicitly set the flag M_NULL. 
			 * If the caller isn't expecting a NULL return code, we just panic. This is less 
			 * than ideal, but returning NULL when the caller isn't expecting it doesn't help 
			 * since the majority of callers don't check the return value and will just 
			 * dereference the pointer and trap anyway.  We may as well get a more 
			 * descriptive message out while we can.
			 */
			if (flags & M_NULL) {
				return NULL;
			}
			panic("_MALLOC: kalloc returned NULL (potential leak), size %llu", (uint64_t) size);
		}
	}
	if (!addr)
		return (0);

	if (flags & M_ZERO)
		bzero(addr, size);

	return  (addr);
}