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
typedef  int /*<<< orphan*/  arena_t ;

/* Variables and functions */
 int /*<<< orphan*/ * a0get () ; 
 int /*<<< orphan*/ * arena_get (int /*<<< orphan*/ ,unsigned int,int,int) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tsd_fetch () ; 

__attribute__((used)) static arena_t *
chunk_arena_get(unsigned arena_ind)
{
	arena_t *arena;

	/* Dodge tsd for a0 in order to avoid bootstrapping issues. */
	arena = (arena_ind == 0) ? a0get() : arena_get(tsd_fetch(), arena_ind,
	     false, true);
	/*
	 * The arena we're allocating on behalf of must have been initialized
	 * already.
	 */
	assert(arena != NULL);
	return (arena);
}