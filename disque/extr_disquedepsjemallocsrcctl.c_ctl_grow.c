#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ctl_arena_stats_t ;
struct TYPE_2__ {int narenas; int /*<<< orphan*/ * arenas; } ;

/* Variables and functions */
 int /*<<< orphan*/  a0dalloc (int /*<<< orphan*/ *) ; 
 scalar_t__ a0malloc (int) ; 
 int /*<<< orphan*/ * arena_init (int) ; 
 scalar_t__ ctl_arena_init (int /*<<< orphan*/ *) ; 
 TYPE_1__ ctl_stats ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static bool
ctl_grow(void)
{
	ctl_arena_stats_t *astats;

	/* Initialize new arena. */
	if (arena_init(ctl_stats.narenas) == NULL)
		return (true);

	/* Allocate extended arena stats. */
	astats = (ctl_arena_stats_t *)a0malloc((ctl_stats.narenas + 2) *
	    sizeof(ctl_arena_stats_t));
	if (astats == NULL)
		return (true);

	/* Initialize the new astats element. */
	memcpy(astats, ctl_stats.arenas, (ctl_stats.narenas + 1) *
	    sizeof(ctl_arena_stats_t));
	memset(&astats[ctl_stats.narenas + 1], 0, sizeof(ctl_arena_stats_t));
	if (ctl_arena_init(&astats[ctl_stats.narenas + 1])) {
		a0dalloc(astats);
		return (true);
	}
	/* Swap merged stats to their new location. */
	{
		ctl_arena_stats_t tstats;
		memcpy(&tstats, &astats[ctl_stats.narenas],
		    sizeof(ctl_arena_stats_t));
		memcpy(&astats[ctl_stats.narenas],
		    &astats[ctl_stats.narenas + 1], sizeof(ctl_arena_stats_t));
		memcpy(&astats[ctl_stats.narenas + 1], &tstats,
		    sizeof(ctl_arena_stats_t));
	}
	a0dalloc(ctl_stats.arenas);
	ctl_stats.arenas = astats;
	ctl_stats.narenas++;

	return (false);
}