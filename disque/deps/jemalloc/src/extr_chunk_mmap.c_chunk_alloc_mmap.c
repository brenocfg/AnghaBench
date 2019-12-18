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
 size_t ALIGNMENT_ADDR2OFFSET (void*,size_t) ; 
 int /*<<< orphan*/  assert (int) ; 
 void* chunk_alloc_mmap_slow (size_t,size_t,int*,int*) ; 
 size_t chunksize_mask ; 
 int pages_decommit (void*,size_t) ; 
 void* pages_map (int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  pages_unmap (void*,size_t) ; 

void *
chunk_alloc_mmap(size_t size, size_t alignment, bool *zero, bool *commit)
{
	void *ret;
	size_t offset;

	/*
	 * Ideally, there would be a way to specify alignment to mmap() (like
	 * NetBSD has), but in the absence of such a feature, we have to work
	 * hard to efficiently create aligned mappings.  The reliable, but
	 * slow method is to create a mapping that is over-sized, then trim the
	 * excess.  However, that always results in one or two calls to
	 * pages_unmap().
	 *
	 * Optimistically try mapping precisely the right amount before falling
	 * back to the slow method, with the expectation that the optimistic
	 * approach works most of the time.
	 */

	assert(alignment != 0);
	assert((alignment & chunksize_mask) == 0);

	ret = pages_map(NULL, size);
	if (ret == NULL)
		return (NULL);
	offset = ALIGNMENT_ADDR2OFFSET(ret, alignment);
	if (offset != 0) {
		pages_unmap(ret, size);
		return (chunk_alloc_mmap_slow(size, alignment, zero, commit));
	}

	assert(ret != NULL);
	*zero = true;
	if (!*commit)
		*commit = pages_decommit(ret, size);
	return (ret);
}