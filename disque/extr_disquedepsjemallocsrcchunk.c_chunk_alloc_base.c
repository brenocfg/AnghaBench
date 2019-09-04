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
 int /*<<< orphan*/  JEMALLOC_VALGRIND_MAKE_MEM_UNDEFINED (void*,size_t) ; 
 void* chunk_alloc_mmap (size_t,int /*<<< orphan*/ ,int*,int*) ; 
 int /*<<< orphan*/  chunksize ; 
 scalar_t__ config_valgrind ; 

void *
chunk_alloc_base(size_t size)
{
	void *ret;
	bool zero, commit;

	/*
	 * Directly call chunk_alloc_mmap() rather than chunk_alloc_core()
	 * because it's critical that chunk_alloc_base() return untouched
	 * demand-zeroed virtual memory.
	 */
	zero = true;
	commit = true;
	ret = chunk_alloc_mmap(size, chunksize, &zero, &commit);
	if (ret == NULL)
		return (NULL);
	if (config_valgrind)
		JEMALLOC_VALGRIND_MAKE_MEM_UNDEFINED(ret, size);

	return (ret);
}