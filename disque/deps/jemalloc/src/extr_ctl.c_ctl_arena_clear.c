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
typedef  int /*<<< orphan*/  malloc_large_stats_t ;
typedef  int /*<<< orphan*/  malloc_huge_stats_t ;
typedef  int /*<<< orphan*/  malloc_bin_stats_t ;
struct TYPE_3__ {int lg_dirty_mult; int /*<<< orphan*/ * hstats; int /*<<< orphan*/ * lstats; int /*<<< orphan*/ * bstats; scalar_t__ nrequests_small; scalar_t__ ndalloc_small; scalar_t__ nmalloc_small; scalar_t__ allocated_small; int /*<<< orphan*/  astats; scalar_t__ pdirty; scalar_t__ pactive; int /*<<< orphan*/  dss; } ;
typedef  TYPE_1__ ctl_arena_stats_t ;
typedef  int /*<<< orphan*/  arena_stats_t ;

/* Variables and functions */
 int NBINS ; 
 scalar_t__ config_stats ; 
 size_t dss_prec_limit ; 
 int /*<<< orphan*/ * dss_prec_names ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int nhclasses ; 
 int nlclasses ; 

__attribute__((used)) static void
ctl_arena_clear(ctl_arena_stats_t *astats)
{

	astats->dss = dss_prec_names[dss_prec_limit];
	astats->lg_dirty_mult = -1;
	astats->pactive = 0;
	astats->pdirty = 0;
	if (config_stats) {
		memset(&astats->astats, 0, sizeof(arena_stats_t));
		astats->allocated_small = 0;
		astats->nmalloc_small = 0;
		astats->ndalloc_small = 0;
		astats->nrequests_small = 0;
		memset(astats->bstats, 0, NBINS * sizeof(malloc_bin_stats_t));
		memset(astats->lstats, 0, nlclasses *
		    sizeof(malloc_large_stats_t));
		memset(astats->hstats, 0, nhclasses *
		    sizeof(malloc_huge_stats_t));
	}
}