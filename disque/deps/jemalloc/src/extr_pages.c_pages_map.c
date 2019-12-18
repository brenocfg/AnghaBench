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
 int MAP_ANON ; 
 void* MAP_FAILED ; 
 int MAP_PRIVATE ; 
 int MEM_COMMIT ; 
 int MEM_RESERVE ; 
 int /*<<< orphan*/  PAGE_READWRITE ; 
 int PROT_READ ; 
 int PROT_WRITE ; 
 void* VirtualAlloc (void*,size_t,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int) ; 
 void* mmap (void*,size_t,int,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pages_unmap (void*,size_t) ; 

void *
pages_map(void *addr, size_t size)
{
	void *ret;

	assert(size != 0);

#ifdef _WIN32
	/*
	 * If VirtualAlloc can't allocate at the given address when one is
	 * given, it fails and returns NULL.
	 */
	ret = VirtualAlloc(addr, size, MEM_COMMIT | MEM_RESERVE,
	    PAGE_READWRITE);
#else
	/*
	 * We don't use MAP_FIXED here, because it can cause the *replacement*
	 * of existing mappings, and we only want to create new mappings.
	 */
	ret = mmap(addr, size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANON,
	    -1, 0);
	assert(ret != NULL);

	if (ret == MAP_FAILED)
		ret = NULL;
	else if (addr != NULL && ret != addr) {
		/*
		 * We succeeded in mapping memory, but not in the right place.
		 */
		pages_unmap(ret, size);
		ret = NULL;
	}
#endif
	assert(ret == NULL || (addr == NULL && ret != addr)
	    || (addr != NULL && ret == addr));
	return (ret);
}