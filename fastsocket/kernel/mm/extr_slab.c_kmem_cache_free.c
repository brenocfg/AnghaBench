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
struct kmem_cache {int flags; } ;

/* Variables and functions */
 int SLAB_DEBUG_OBJECTS ; 
 int /*<<< orphan*/  _RET_IP_ ; 
 int /*<<< orphan*/  __cache_free (struct kmem_cache*,void*) ; 
 int /*<<< orphan*/  debug_check_no_locks_freed (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debug_check_no_obj_freed (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 int /*<<< orphan*/  obj_size (struct kmem_cache*) ; 
 int /*<<< orphan*/  trace_kmem_cache_free (int /*<<< orphan*/ ,void*) ; 

void kmem_cache_free(struct kmem_cache *cachep, void *objp)
{
	unsigned long flags;

	local_irq_save(flags);
	debug_check_no_locks_freed(objp, obj_size(cachep));
	if (!(cachep->flags & SLAB_DEBUG_OBJECTS))
		debug_check_no_obj_freed(objp, obj_size(cachep));
	__cache_free(cachep, objp);
	local_irq_restore(flags);

	trace_kmem_cache_free(_RET_IP_, objp);
}