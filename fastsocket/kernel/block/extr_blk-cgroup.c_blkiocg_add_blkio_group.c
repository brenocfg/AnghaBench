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
struct blkio_group {int plid; int /*<<< orphan*/  dev; int /*<<< orphan*/  path; int /*<<< orphan*/  blkcg_node; int /*<<< orphan*/  blkcg_id; int /*<<< orphan*/  key; int /*<<< orphan*/  stats_lock; } ;
struct TYPE_2__ {int /*<<< orphan*/  cgroup; } ;
struct blkio_cgroup {TYPE_1__ css; int /*<<< orphan*/  lock; int /*<<< orphan*/  blkg_list; } ;
typedef  enum blkio_policy_id { ____Placeholder_blkio_policy_id } blkio_policy_id ;
typedef  int /*<<< orphan*/  dev_t ;

/* Variables and functions */
 int /*<<< orphan*/  cgroup_path (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  css_id (TYPE_1__*) ; 
 int /*<<< orphan*/  hlist_add_head_rcu (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rcu_assign_pointer (int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void blkiocg_add_blkio_group(struct blkio_cgroup *blkcg,
		struct blkio_group *blkg, void *key, dev_t dev,
		enum blkio_policy_id plid)
{
	unsigned long flags;

	spin_lock_irqsave(&blkcg->lock, flags);
	spin_lock_init(&blkg->stats_lock);
	rcu_assign_pointer(blkg->key, key);
	blkg->blkcg_id = css_id(&blkcg->css);
	hlist_add_head_rcu(&blkg->blkcg_node, &blkcg->blkg_list);
	blkg->plid = plid;
	spin_unlock_irqrestore(&blkcg->lock, flags);
	/* Need to take css reference ? */
	cgroup_path(blkcg->css.cgroup, blkg->path, sizeof(blkg->path));
	blkg->dev = dev;
}