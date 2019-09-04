#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  chunk_split_t ;
typedef  int /*<<< orphan*/  chunk_purge_t ;
typedef  int /*<<< orphan*/  chunk_merge_t ;
struct TYPE_6__ {int /*<<< orphan*/ * merge; int /*<<< orphan*/ * split; int /*<<< orphan*/ * purge; int /*<<< orphan*/ * decommit; int /*<<< orphan*/ * commit; int /*<<< orphan*/ * dalloc; int /*<<< orphan*/ * alloc; } ;
typedef  TYPE_1__ chunk_hooks_t ;
typedef  int /*<<< orphan*/  chunk_decommit_t ;
typedef  int /*<<< orphan*/  chunk_dalloc_t ;
typedef  int /*<<< orphan*/  chunk_commit_t ;
typedef  int /*<<< orphan*/  chunk_alloc_t ;
struct TYPE_7__ {int /*<<< orphan*/  chunks_mtx; TYPE_1__ chunk_hooks; } ;
typedef  TYPE_2__ arena_t ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_write_p (void**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  malloc_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  malloc_mutex_unlock (int /*<<< orphan*/ *) ; 

chunk_hooks_t
chunk_hooks_set(arena_t *arena, const chunk_hooks_t *chunk_hooks)
{
	chunk_hooks_t old_chunk_hooks;

	malloc_mutex_lock(&arena->chunks_mtx);
	old_chunk_hooks = arena->chunk_hooks;
	/*
	 * Copy each field atomically so that it is impossible for readers to
	 * see partially updated pointers.  There are places where readers only
	 * need one hook function pointer (therefore no need to copy the
	 * entirety of arena->chunk_hooks), and stale reads do not affect
	 * correctness, so they perform unlocked reads.
	 */
#define	ATOMIC_COPY_HOOK(n) do {					\
	union {								\
		chunk_##n##_t	**n;					\
		void		**v;					\
	} u;								\
	u.n = &arena->chunk_hooks.n;					\
	atomic_write_p(u.v, chunk_hooks->n);				\
} while (0)
	ATOMIC_COPY_HOOK(alloc);
	ATOMIC_COPY_HOOK(dalloc);
	ATOMIC_COPY_HOOK(commit);
	ATOMIC_COPY_HOOK(decommit);
	ATOMIC_COPY_HOOK(purge);
	ATOMIC_COPY_HOOK(split);
	ATOMIC_COPY_HOOK(merge);
#undef ATOMIC_COPY_HOOK
	malloc_mutex_unlock(&arena->chunks_mtx);

	return (old_chunk_hooks);
}