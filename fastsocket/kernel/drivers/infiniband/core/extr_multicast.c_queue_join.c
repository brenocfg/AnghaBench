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
struct mcast_member {int /*<<< orphan*/  list; struct mcast_group* group; } ;
struct mcast_group {scalar_t__ state; int /*<<< orphan*/  lock; int /*<<< orphan*/  work; int /*<<< orphan*/  refcount; int /*<<< orphan*/  pending_list; } ;

/* Variables and functions */
 scalar_t__ MCAST_BUSY ; 
 scalar_t__ MCAST_IDLE ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mcast_wq ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void queue_join(struct mcast_member *member)
{
	struct mcast_group *group = member->group;
	unsigned long flags;

	spin_lock_irqsave(&group->lock, flags);
	list_add_tail(&member->list, &group->pending_list);
	if (group->state == MCAST_IDLE) {
		group->state = MCAST_BUSY;
		atomic_inc(&group->refcount);
		queue_work(mcast_wq, &group->work);
	}
	spin_unlock_irqrestore(&group->lock, flags);
}