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
typedef  int /*<<< orphan*/  chunk_hooks_t ;
struct TYPE_4__ {int /*<<< orphan*/  chunks_mtx; } ;
typedef  TYPE_1__ arena_t ;

/* Variables and functions */
 int /*<<< orphan*/  chunk_hooks_get_locked (TYPE_1__*) ; 
 int /*<<< orphan*/  malloc_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  malloc_mutex_unlock (int /*<<< orphan*/ *) ; 

chunk_hooks_t
chunk_hooks_get(arena_t *arena)
{
	chunk_hooks_t chunk_hooks;

	malloc_mutex_lock(&arena->chunks_mtx);
	chunk_hooks = chunk_hooks_get_locked(arena);
	malloc_mutex_unlock(&arena->chunks_mtx);

	return (chunk_hooks);
}