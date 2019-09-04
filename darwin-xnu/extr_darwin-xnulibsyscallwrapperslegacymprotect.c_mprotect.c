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

/* Variables and functions */
 scalar_t__ EINVAL ; 
 scalar_t__ ENOMEM ; 
 uintptr_t PAGE_MASK ; 
 int __mprotect (void*,size_t,int) ; 
 scalar_t__ errno ; 

int
mprotect(void *addr, size_t len, int prot)
{
	void	*aligned_addr;
	size_t	offset;
	int	rv;

	/*
	 * Page-align "addr" since the system now requires it
	 * for standards compliance.
	 * Update "len" to reflect the alignment.
	 */
	offset = ((uintptr_t) addr) & PAGE_MASK;
	aligned_addr = (void *) (((uintptr_t) addr) & ~PAGE_MASK);
	len += offset;
	rv = __mprotect(aligned_addr, len, prot);
	if (rv == -1 && errno == ENOMEM) {
		/*
		 * Standards now require that we return ENOMEM if there was
		 * a hole in the address range.  Panther and earlier used
		 * to return an EINVAL error, so honor backwards compatibility.
		 */
		errno = EINVAL;
	}
	return rv;
}