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
 void* kmem_zalloc_large (size_t) ; 

void *
kmem_zalloc_greedy(size_t *size, size_t minsize, size_t maxsize)
{
	void		*ptr;
	size_t		kmsize = maxsize;

	while (!(ptr = kmem_zalloc_large(kmsize))) {
		if ((kmsize >>= 1) <= minsize)
			kmsize = minsize;
	}
	if (ptr)
		*size = kmsize;
	return ptr;
}