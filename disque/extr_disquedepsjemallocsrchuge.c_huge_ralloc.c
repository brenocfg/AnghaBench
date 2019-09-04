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
typedef  int /*<<< orphan*/  tsd_t ;
typedef  int /*<<< orphan*/  tcache_t ;
typedef  int /*<<< orphan*/  arena_t ;

/* Variables and functions */
 void* huge_ralloc_move_helper (int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t,size_t,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  huge_ralloc_no_move (void*,size_t,size_t,size_t,int) ; 
 int /*<<< orphan*/  isqalloc (int /*<<< orphan*/ *,void*,size_t,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (void*,void*,size_t) ; 

void *
huge_ralloc(tsd_t *tsd, arena_t *arena, void *ptr, size_t oldsize, size_t usize,
    size_t alignment, bool zero, tcache_t *tcache)
{
	void *ret;
	size_t copysize;

	/* Try to avoid moving the allocation. */
	if (!huge_ralloc_no_move(ptr, oldsize, usize, usize, zero))
		return (ptr);

	/*
	 * usize and oldsize are different enough that we need to use a
	 * different size class.  In that case, fall back to allocating new
	 * space and copying.
	 */
	ret = huge_ralloc_move_helper(tsd, arena, usize, alignment, zero,
	    tcache);
	if (ret == NULL)
		return (NULL);

	copysize = (usize < oldsize) ? usize : oldsize;
	memcpy(ret, ptr, copysize);
	isqalloc(tsd, ptr, oldsize, tcache);
	return (ret);
}