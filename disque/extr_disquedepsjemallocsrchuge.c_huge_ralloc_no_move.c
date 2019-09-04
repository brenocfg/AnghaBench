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
 scalar_t__ CHUNK_CEILING (size_t) ; 
 int /*<<< orphan*/  assert (int) ; 
 size_t chunksize ; 
 scalar_t__ huge_ralloc_no_move_expand (void*,size_t,size_t,int) ; 
 int huge_ralloc_no_move_shrink (void*,size_t,size_t) ; 
 int /*<<< orphan*/  huge_ralloc_no_move_similar (void*,size_t,size_t,size_t,int) ; 
 size_t s2u (size_t) ; 

bool
huge_ralloc_no_move(void *ptr, size_t oldsize, size_t usize_min,
    size_t usize_max, bool zero)
{

	assert(s2u(oldsize) == oldsize);

	/* Both allocations must be huge to avoid a move. */
	if (oldsize < chunksize || usize_max < chunksize)
		return (true);

	if (CHUNK_CEILING(usize_max) > CHUNK_CEILING(oldsize)) {
		/* Attempt to expand the allocation in-place. */
		if (!huge_ralloc_no_move_expand(ptr, oldsize, usize_max, zero))
			return (false);
		/* Try again, this time with usize_min. */
		if (usize_min < usize_max && CHUNK_CEILING(usize_min) >
		    CHUNK_CEILING(oldsize) && huge_ralloc_no_move_expand(ptr,
		    oldsize, usize_min, zero))
			return (false);
	}

	/*
	 * Avoid moving the allocation if the existing chunk size accommodates
	 * the new size.
	 */
	if (CHUNK_CEILING(oldsize) >= CHUNK_CEILING(usize_min)
	    && CHUNK_CEILING(oldsize) <= CHUNK_CEILING(usize_max)) {
		huge_ralloc_no_move_similar(ptr, oldsize, usize_min, usize_max,
		    zero);
		return (false);
	}

	/* Attempt to shrink the allocation in-place. */
	if (CHUNK_CEILING(oldsize) > CHUNK_CEILING(usize_max))
		return (huge_ralloc_no_move_shrink(ptr, oldsize, usize_max));
	return (true);
}