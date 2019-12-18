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
struct mb_cache_entry {int /*<<< orphan*/  e_lru_list; scalar_t__ e_queued; scalar_t__ e_used; struct mb_cache* e_cache; } ;
struct TYPE_2__ {scalar_t__ (* free ) (struct mb_cache_entry*,int /*<<< orphan*/ ) ;} ;
struct mb_cache {int /*<<< orphan*/  c_entry_count; int /*<<< orphan*/  c_entry_cache; TYPE_1__ c_op; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kmem_cache_free (int /*<<< orphan*/ ,struct mb_cache_entry*) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mb_assert (int) ; 
 int /*<<< orphan*/  mb_cache_lru_list ; 
 int /*<<< orphan*/  mb_cache_spinlock ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ stub1 (struct mb_cache_entry*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
__mb_cache_entry_forget(struct mb_cache_entry *ce, gfp_t gfp_mask)
{
	struct mb_cache *cache = ce->e_cache;

	mb_assert(!(ce->e_used || ce->e_queued));
	if (cache->c_op.free && cache->c_op.free(ce, gfp_mask)) {
		/* free failed -- put back on the lru list
		   for freeing later. */
		spin_lock(&mb_cache_spinlock);
		list_add(&ce->e_lru_list, &mb_cache_lru_list);
		spin_unlock(&mb_cache_spinlock);
	} else {
		kmem_cache_free(cache->c_entry_cache, ce);
		atomic_dec(&cache->c_entry_count);
	}
}