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
struct stripe_head {int /*<<< orphan*/  count; } ;
struct r5conf {int /*<<< orphan*/  active_stripes; int /*<<< orphan*/  slab_cache; int /*<<< orphan*/  device_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 struct stripe_head* get_free_stripe (struct r5conf*) ; 
 int /*<<< orphan*/  kmem_cache_free (int /*<<< orphan*/ ,struct stripe_head*) ; 
 int /*<<< orphan*/  shrink_buffers (struct stripe_head*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int drop_one_stripe(struct r5conf *conf)
{
	struct stripe_head *sh;

	spin_lock_irq(&conf->device_lock);
	sh = get_free_stripe(conf);
	spin_unlock_irq(&conf->device_lock);
	if (!sh)
		return 0;
	BUG_ON(atomic_read(&sh->count));
	shrink_buffers(sh);
	kmem_cache_free(conf->slab_cache, sh);
	atomic_dec(&conf->active_stripes);
	return 1;
}