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
struct stripe_head {int /*<<< orphan*/  lru; int /*<<< orphan*/  count; int /*<<< orphan*/  stripe_lock; int /*<<< orphan*/  lock; struct r5conf* raid_conf; } ;
struct r5conf {int /*<<< orphan*/  active_stripes; int /*<<< orphan*/  slab_cache; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 scalar_t__ grow_buffers (struct stripe_head*) ; 
 int /*<<< orphan*/  kmem_cache_free (int /*<<< orphan*/ ,struct stripe_head*) ; 
 struct stripe_head* kmem_cache_zalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  release_stripe (struct stripe_head*) ; 
 int /*<<< orphan*/  shrink_buffers (struct stripe_head*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int grow_one_stripe(struct r5conf *conf)
{
	struct stripe_head *sh;
	sh = kmem_cache_zalloc(conf->slab_cache, GFP_KERNEL);
	if (!sh)
		return 0;

	sh->raid_conf = conf;

	spin_lock_init(&sh->lock);
	spin_lock_init(&sh->stripe_lock);

	if (grow_buffers(sh)) {
		shrink_buffers(sh);
		kmem_cache_free(conf->slab_cache, sh);
		return 0;
	}
	/* we just created an active stripe so... */
	atomic_set(&sh->count, 1);
	atomic_inc(&conf->active_stripes);
	INIT_LIST_HEAD(&sh->lru);
	release_stripe(sh);
	return 1;
}