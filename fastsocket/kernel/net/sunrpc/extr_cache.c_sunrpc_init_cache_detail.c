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
struct cache_detail {int last_warn; int /*<<< orphan*/  others; scalar_t__ last_close; int /*<<< orphan*/  readers; scalar_t__ entries; scalar_t__ nextcheck; int /*<<< orphan*/  queue; int /*<<< orphan*/  hash_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cache_cleaner ; 
 int /*<<< orphan*/  cache_list ; 
 int /*<<< orphan*/  cache_list_lock ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rwlock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  schedule_delayed_work (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void sunrpc_init_cache_detail(struct cache_detail *cd)
{
	rwlock_init(&cd->hash_lock);
	INIT_LIST_HEAD(&cd->queue);
	spin_lock(&cache_list_lock);
	cd->nextcheck = 0;
	cd->entries = 0;
	atomic_set(&cd->readers, 0);
	cd->last_close = 0;
	cd->last_warn = -1;
	list_add(&cd->others, &cache_list);
	spin_unlock(&cache_list_lock);

	/* start the cleaning process */
	schedule_delayed_work(&cache_cleaner, 0);
}