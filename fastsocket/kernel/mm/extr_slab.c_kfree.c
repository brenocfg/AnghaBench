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
struct kmem_cache {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ZERO_OR_NULL_PTR (void const*) ; 
 int /*<<< orphan*/  _RET_IP_ ; 
 int /*<<< orphan*/  __cache_free (struct kmem_cache*,void*) ; 
 int /*<<< orphan*/  debug_check_no_locks_freed (void const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debug_check_no_obj_freed (void const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree_debugcheck (void const*) ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 int /*<<< orphan*/  obj_size (struct kmem_cache*) ; 
 int /*<<< orphan*/  trace_kfree (int /*<<< orphan*/ ,void const*) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 struct kmem_cache* virt_to_cache (void const*) ; 

void kfree(const void *objp)
{
	struct kmem_cache *c;
	unsigned long flags;

	trace_kfree(_RET_IP_, objp);

	if (unlikely(ZERO_OR_NULL_PTR(objp)))
		return;
	local_irq_save(flags);
	kfree_debugcheck(objp);
	c = virt_to_cache(objp);
	debug_check_no_locks_freed(objp, obj_size(c));
	debug_check_no_obj_freed(objp, obj_size(c));
	__cache_free(c, (void *)objp);
	local_irq_restore(flags);
}