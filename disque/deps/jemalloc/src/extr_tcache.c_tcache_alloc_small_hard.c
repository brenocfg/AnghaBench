#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tsd_t ;
struct TYPE_3__ {scalar_t__ prof_accumbytes; } ;
typedef  TYPE_1__ tcache_t ;
typedef  int /*<<< orphan*/  tcache_bin_t ;
typedef  int /*<<< orphan*/  szind_t ;
typedef  int /*<<< orphan*/  arena_t ;

/* Variables and functions */
 int /*<<< orphan*/  arena_tcache_fill_small (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ config_prof ; 
 void* tcache_alloc_easy (int /*<<< orphan*/ *) ; 

void *
tcache_alloc_small_hard(tsd_t *tsd, arena_t *arena, tcache_t *tcache,
    tcache_bin_t *tbin, szind_t binind)
{
	void *ret;

	arena_tcache_fill_small(arena, tbin, binind, config_prof ?
	    tcache->prof_accumbytes : 0);
	if (config_prof)
		tcache->prof_accumbytes = 0;
	ret = tcache_alloc_easy(tbin);

	return (ret);
}