#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  pdirty; int /*<<< orphan*/  pactive; scalar_t__ nthreads; } ;
typedef  TYPE_1__ ctl_arena_stats_t ;
struct TYPE_11__ {scalar_t__ ndirty; scalar_t__ nactive; } ;
typedef  TYPE_2__ arena_t ;
struct TYPE_12__ {size_t narenas; TYPE_1__* arenas; } ;

/* Variables and functions */
 scalar_t__ config_stats ; 
 int /*<<< orphan*/  ctl_arena_clear (TYPE_1__*) ; 
 int /*<<< orphan*/  ctl_arena_stats_amerge (TYPE_1__*,TYPE_2__*) ; 
 int /*<<< orphan*/  ctl_arena_stats_smerge (TYPE_1__*,TYPE_1__*) ; 
 TYPE_3__ ctl_stats ; 

__attribute__((used)) static void
ctl_arena_refresh(arena_t *arena, unsigned i)
{
	ctl_arena_stats_t *astats = &ctl_stats.arenas[i];
	ctl_arena_stats_t *sstats = &ctl_stats.arenas[ctl_stats.narenas];

	ctl_arena_clear(astats);

	sstats->nthreads += astats->nthreads;
	if (config_stats) {
		ctl_arena_stats_amerge(astats, arena);
		/* Merge into sum stats as well. */
		ctl_arena_stats_smerge(sstats, astats);
	} else {
		astats->pactive += arena->nactive;
		astats->pdirty += arena->ndirty;
		/* Merge into sum stats as well. */
		sstats->pactive += arena->nactive;
		sstats->pdirty += arena->ndirty;
	}
}