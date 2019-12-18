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
struct io_context {scalar_t__ cgroup_changed; int /*<<< orphan*/ * ioc_data; int /*<<< orphan*/  cic_list; int /*<<< orphan*/  radix_root; int /*<<< orphan*/ * aic; scalar_t__ nr_batch_requests; int /*<<< orphan*/  last_waited; scalar_t__ ioprio; scalar_t__ ioprio_changed; int /*<<< orphan*/  lock; int /*<<< orphan*/  nr_tasks; int /*<<< orphan*/  refcount; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int GFP_ATOMIC ; 
 int /*<<< orphan*/  INIT_HLIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INIT_RADIX_TREE (int /*<<< orphan*/ *,int) ; 
 int __GFP_HIGH ; 
 int /*<<< orphan*/  atomic_long_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  iocontext_cachep ; 
 int /*<<< orphan*/  jiffies ; 
 struct io_context* kmem_cache_alloc_node (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

struct io_context *alloc_io_context(gfp_t gfp_flags, int node)
{
	struct io_context *ret;

	ret = kmem_cache_alloc_node(iocontext_cachep, gfp_flags, node);
	if (ret) {
		atomic_long_set(&ret->refcount, 1);
		atomic_set(&ret->nr_tasks, 1);
		spin_lock_init(&ret->lock);
		ret->ioprio_changed = 0;
		ret->ioprio = 0;
		ret->last_waited = jiffies; /* doesn't matter... */
		ret->nr_batch_requests = 0; /* because this is 0 */
		ret->aic = NULL;
		INIT_RADIX_TREE(&ret->radix_root, GFP_ATOMIC | __GFP_HIGH);
		INIT_HLIST_HEAD(&ret->cic_list);
		ret->ioc_data = NULL;
#if defined(CONFIG_BLK_CGROUP) || defined(CONFIG_BLK_CGROUP_MODULE)
		ret->cgroup_changed = 0;
#endif
	}

	return ret;
}