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
 void* CHUNK_ADDR2BASE (void*) ; 
 size_t PAGE_MASK ; 
 int /*<<< orphan*/  assert (int) ; 
 int pages_purge (void*,size_t) ; 

bool
chunk_purge_arena(arena_t *arena, void *chunk, size_t offset, size_t length)
{

	assert(chunk != NULL);
	assert(CHUNK_ADDR2BASE(chunk) == chunk);
	assert((offset & PAGE_MASK) == 0);
	assert(length != 0);
	assert((length & PAGE_MASK) == 0);

	return (pages_purge((void *)((uintptr_t)chunk + (uintptr_t)offset),
	    length));
}