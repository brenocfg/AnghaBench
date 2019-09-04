#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  dss_prec; } ;
typedef  TYPE_1__ arena_t ;

/* Variables and functions */
 int /*<<< orphan*/  JEMALLOC_VALGRIND_MAKE_MEM_UNDEFINED (void*,size_t) ; 
 void* chunk_alloc_core (TYPE_1__*,void*,size_t,size_t,int*,int*,int /*<<< orphan*/ ) ; 
 TYPE_1__* chunk_arena_get (unsigned int) ; 
 scalar_t__ config_valgrind ; 

__attribute__((used)) static void *
chunk_alloc_default(void *new_addr, size_t size, size_t alignment, bool *zero,
    bool *commit, unsigned arena_ind)
{
	void *ret;
	arena_t *arena;

	arena = chunk_arena_get(arena_ind);
	ret = chunk_alloc_core(arena, new_addr, size, alignment, zero,
	    commit, arena->dss_prec);
	if (ret == NULL)
		return (NULL);
	if (config_valgrind)
		JEMALLOC_VALGRIND_MAKE_MEM_UNDEFINED(ret, size);

	return (ret);
}