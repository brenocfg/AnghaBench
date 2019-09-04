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
typedef  int /*<<< orphan*/  tsd_t ;
typedef  int /*<<< orphan*/  tcache_t ;
typedef  int /*<<< orphan*/  arena_t ;

/* Variables and functions */
 int /*<<< orphan*/ * arena_choose (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * tcache_create (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tcache_enabled_get () ; 
 int /*<<< orphan*/  tcache_enabled_set (int) ; 
 scalar_t__ tsd_nominal (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

tcache_t *
tcache_get_hard(tsd_t *tsd)
{
	arena_t *arena;

	if (!tcache_enabled_get()) {
		if (tsd_nominal(tsd))
			tcache_enabled_set(false); /* Memoize. */
		return (NULL);
	}
	arena = arena_choose(tsd, NULL);
	if (unlikely(arena == NULL))
		return (NULL);
	return (tcache_create(tsd, arena));
}