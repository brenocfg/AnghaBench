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
 uintptr_t ALIGNMENT_CEILING (uintptr_t,size_t) ; 
 size_t PAGE ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int pages_decommit (void*,size_t) ; 
 void* pages_map (int /*<<< orphan*/ *,size_t) ; 
 void* pages_trim (void*,size_t,size_t,size_t) ; 

__attribute__((used)) static void *
chunk_alloc_mmap_slow(size_t size, size_t alignment, bool *zero, bool *commit)
{
	void *ret;
	size_t alloc_size;

	alloc_size = size + alignment - PAGE;
	/* Beware size_t wrap-around. */
	if (alloc_size < size)
		return (NULL);
	do {
		void *pages;
		size_t leadsize;
		pages = pages_map(NULL, alloc_size);
		if (pages == NULL)
			return (NULL);
		leadsize = ALIGNMENT_CEILING((uintptr_t)pages, alignment) -
		    (uintptr_t)pages;
		ret = pages_trim(pages, alloc_size, leadsize, size);
	} while (ret == NULL);

	assert(ret != NULL);
	*zero = true;
	if (!*commit)
		*commit = pages_decommit(ret, size);
	return (ret);
}