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
struct debug_obj {int /*<<< orphan*/  node; } ;
typedef  int gfp_t ;

/* Variables and functions */
 int GFP_ATOMIC ; 
 scalar_t__ ODEBUG_POOL_MIN_LEVEL ; 
 int __GFP_NORETRY ; 
 int __GFP_NOWARN ; 
 int /*<<< orphan*/  hlist_add_head (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct debug_obj* kmem_cache_zalloc (int /*<<< orphan*/ ,int) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  obj_cache ; 
 int /*<<< orphan*/  obj_pool ; 
 scalar_t__ obj_pool_free ; 
 int /*<<< orphan*/  pool_lock ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int fill_pool(void)
{
	gfp_t gfp = GFP_ATOMIC | __GFP_NORETRY | __GFP_NOWARN;
	struct debug_obj *new;
	unsigned long flags;

	if (likely(obj_pool_free >= ODEBUG_POOL_MIN_LEVEL))
		return obj_pool_free;

	if (unlikely(!obj_cache))
		return obj_pool_free;

	while (obj_pool_free < ODEBUG_POOL_MIN_LEVEL) {

		new = kmem_cache_zalloc(obj_cache, gfp);
		if (!new)
			return obj_pool_free;

		spin_lock_irqsave(&pool_lock, flags);
		hlist_add_head(&new->node, &obj_pool);
		obj_pool_free++;
		spin_unlock_irqrestore(&pool_lock, flags);
	}
	return obj_pool_free;
}