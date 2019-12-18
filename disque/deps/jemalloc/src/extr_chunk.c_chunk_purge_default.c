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
 int /*<<< orphan*/  chunk_arena_get (unsigned int) ; 
 int chunk_purge_arena (int /*<<< orphan*/ ,void*,size_t,size_t) ; 

__attribute__((used)) static bool
chunk_purge_default(void *chunk, size_t size, size_t offset, size_t length,
    unsigned arena_ind)
{

	return (chunk_purge_arena(chunk_arena_get(arena_ind), chunk, offset,
	    length));
}