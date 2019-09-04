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
typedef  int /*<<< orphan*/  tcache_t ;
struct TYPE_3__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  tcache_ql; } ;
typedef  TYPE_1__ arena_t ;

/* Variables and functions */
 scalar_t__ config_stats ; 
 int /*<<< orphan*/  link ; 
 int /*<<< orphan*/  malloc_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  malloc_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ql_elm_new (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ql_tail_insert (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void
tcache_arena_associate(tcache_t *tcache, arena_t *arena)
{

	if (config_stats) {
		/* Link into list of extant tcaches. */
		malloc_mutex_lock(&arena->lock);
		ql_elm_new(tcache, link);
		ql_tail_insert(&arena->tcache_ql, tcache, link);
		malloc_mutex_unlock(&arena->lock);
	}
}