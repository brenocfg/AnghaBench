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
 int UMEM_DEFAULT ; 
 int UMEM_NOFAIL ; 
 int /*<<< orphan*/  abort () ; 
 int /*<<< orphan*/  assert (int) ; 
 void* calloc (int,size_t) ; 
 int /*<<< orphan*/  nofail_cb () ; 

void *umem_zalloc(size_t size, int flags)
{
	assert(flags == UMEM_DEFAULT || flags == UMEM_NOFAIL);

	if(size == 0)
		return NULL;

	void *ret = calloc(1, size);
	if(ret == NULL) {
		if(!(flags & UMEM_NOFAIL))
			return NULL;

		if(nofail_cb != NULL)
			nofail_cb();
		abort();
	}

	return ret;
}