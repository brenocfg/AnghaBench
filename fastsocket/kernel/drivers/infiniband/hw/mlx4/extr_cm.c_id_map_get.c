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
struct mlx4_ib_sriov {int /*<<< orphan*/  id_map_lock; int /*<<< orphan*/  pv_id_table; } ;
struct id_map_entry {scalar_t__ pv_cm_id; } ;
struct ib_device {int dummy; } ;
struct TYPE_2__ {struct mlx4_ib_sriov sriov; } ;

/* Variables and functions */
 struct id_map_entry* id_map_find_by_sl_id (struct ib_device*,int,int) ; 
 scalar_t__ idr_find (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 TYPE_1__* to_mdev (struct ib_device*) ; 

__attribute__((used)) static struct id_map_entry *
id_map_get(struct ib_device *ibdev, int *pv_cm_id, int sl_cm_id, int slave_id)
{
	struct id_map_entry *ent;
	struct mlx4_ib_sriov *sriov = &to_mdev(ibdev)->sriov;

	spin_lock(&sriov->id_map_lock);
	if (*pv_cm_id == -1) {
		ent = id_map_find_by_sl_id(ibdev, sl_cm_id, slave_id);
		if (ent)
			*pv_cm_id = (int) ent->pv_cm_id;
	} else
		ent = (struct id_map_entry *)idr_find(&sriov->pv_id_table, *pv_cm_id);
	spin_unlock(&sriov->id_map_lock);

	return ent;
}