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
typedef  void* u32 ;
struct mlx4_ib_sriov {int /*<<< orphan*/  id_map_lock; int /*<<< orphan*/  cm_list; int /*<<< orphan*/  pv_id_table; } ;
struct id_map_entry {int slave_id; int /*<<< orphan*/  list; void* pv_cm_id; int /*<<< orphan*/  timeout; TYPE_1__* dev; scalar_t__ scheduled_delete; void* sl_cm_id; } ;
struct ib_device {int dummy; } ;
struct TYPE_2__ {struct mlx4_ib_sriov sriov; } ;

/* Variables and functions */
 int EAGAIN ; 
 int /*<<< orphan*/  ENOMEM ; 
 struct id_map_entry* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 unsigned int MAX_ID_MASK ; 
 int /*<<< orphan*/  id_map_ent_timeout ; 
 int idr_get_new_above (int /*<<< orphan*/ *,struct id_map_entry*,int,int*) ; 
 scalar_t__ idr_pre_get (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct id_map_entry*) ; 
 struct id_map_entry* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlx4_ib_warn (struct ib_device*,char*,...) ; 
 int /*<<< orphan*/  sl_id_map_add (struct ib_device*,struct id_map_entry*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 TYPE_1__* to_mdev (struct ib_device*) ; 

__attribute__((used)) static struct id_map_entry *
id_map_alloc(struct ib_device *ibdev, int slave_id, u32 sl_cm_id)
{
	int ret, id;
	static int next_id;
	struct id_map_entry *ent;
	struct mlx4_ib_sriov *sriov = &to_mdev(ibdev)->sriov;

	ent = kmalloc(sizeof (struct id_map_entry), GFP_KERNEL);
	if (!ent) {
		mlx4_ib_warn(ibdev, "Couldn't allocate id cache entry - out of memory\n");
		return ERR_PTR(-ENOMEM);
	}

	ent->sl_cm_id = sl_cm_id;
	ent->slave_id = slave_id;
	ent->scheduled_delete = 0;
	ent->dev = to_mdev(ibdev);
	INIT_DELAYED_WORK(&ent->timeout, id_map_ent_timeout);

	do {
		spin_lock(&to_mdev(ibdev)->sriov.id_map_lock);
		ret = idr_get_new_above(&sriov->pv_id_table, ent,
					next_id, &id);
		if (!ret) {
			next_id = ((unsigned) id + 1) & MAX_ID_MASK;
			ent->pv_cm_id = (u32)id;
			sl_id_map_add(ibdev, ent);
		}

		spin_unlock(&sriov->id_map_lock);
	} while (ret == -EAGAIN && idr_pre_get(&sriov->pv_id_table, GFP_KERNEL));
	/*the function idr_get_new_above can return -ENOSPC, so don't insert in that case.*/
	if (!ret) {
		spin_lock(&sriov->id_map_lock);
		list_add_tail(&ent->list, &sriov->cm_list);
		spin_unlock(&sriov->id_map_lock);
		return ent;
	}
	/*error flow*/
	kfree(ent);
	mlx4_ib_warn(ibdev, "No more space in the idr (err:0x%x)\n", ret);
	return ERR_PTR(-ENOMEM);
}