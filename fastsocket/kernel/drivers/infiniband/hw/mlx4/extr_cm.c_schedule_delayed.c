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
struct mlx4_ib_sriov {int /*<<< orphan*/  id_map_lock; int /*<<< orphan*/  going_down_lock; int /*<<< orphan*/  is_going_down; } ;
struct id_map_entry {int scheduled_delete; int /*<<< orphan*/  timeout; } ;
struct ib_device {int dummy; } ;
struct TYPE_2__ {struct mlx4_ib_sriov sriov; } ;

/* Variables and functions */
 int /*<<< orphan*/  CM_CLEANUP_CACHE_TIMEOUT ; 
 int /*<<< orphan*/  schedule_delayed_work (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 TYPE_1__* to_mdev (struct ib_device*) ; 

__attribute__((used)) static void schedule_delayed(struct ib_device *ibdev, struct id_map_entry *id)
{
	struct mlx4_ib_sriov *sriov = &to_mdev(ibdev)->sriov;
	unsigned long flags;

	spin_lock(&sriov->id_map_lock);
	spin_lock_irqsave(&sriov->going_down_lock, flags);
	/*make sure that there is no schedule inside the scheduled work.*/
	if (!sriov->is_going_down) {
		id->scheduled_delete = 1;
		schedule_delayed_work(&id->timeout, CM_CLEANUP_CACHE_TIMEOUT);
	}
	spin_unlock_irqrestore(&sriov->going_down_lock, flags);
	spin_unlock(&sriov->id_map_lock);
}