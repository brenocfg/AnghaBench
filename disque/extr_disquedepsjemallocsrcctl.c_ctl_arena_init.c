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
struct TYPE_3__ {int /*<<< orphan*/ * hstats; int /*<<< orphan*/ * lstats; } ;
typedef  TYPE_1__ ctl_arena_stats_t ;

/* Variables and functions */
 scalar_t__ a0malloc (int) ; 
 int nhclasses ; 
 int nlclasses ; 

__attribute__((used)) static bool
ctl_arena_init(ctl_arena_stats_t *astats)
{

	if (astats->lstats == NULL) {
		astats->lstats = (malloc_large_stats_t *)a0malloc(nlclasses *
		    sizeof(malloc_large_stats_t));
		if (astats->lstats == NULL)
			return (true);
	}

	if (astats->hstats == NULL) {
		astats->hstats = (malloc_huge_stats_t *)a0malloc(nhclasses *
		    sizeof(malloc_huge_stats_t));
		if (astats->hstats == NULL)
			return (true);
	}

	return (false);
}