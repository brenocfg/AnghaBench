#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct t3cdev {TYPE_2__* lldev; } ;
struct t3c_data {int /*<<< orphan*/  tid_release_lock; int /*<<< orphan*/  tid_release_task; } ;
struct adapter {int /*<<< orphan*/  open_device_map; } ;
struct TYPE_3__ {int /*<<< orphan*/  kobj; } ;
struct TYPE_4__ {TYPE_1__ dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  OFFLOAD_DEVMAP_BIT ; 
 struct t3c_data* T3C_DATA (struct t3cdev*) ; 
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cxgb3_offload_deactivate (struct adapter*) ; 
 int /*<<< orphan*/  cxgb3_remove_clients (struct t3cdev*) ; 
 int /*<<< orphan*/  cxgb3_set_dummy_ops (struct t3cdev*) ; 
 int /*<<< orphan*/  cxgb_down (struct adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  flush_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  offload_attr_group ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sysfs_remove_group (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  t3_tp_set_offload_mode (struct adapter*,int /*<<< orphan*/ ) ; 
 struct adapter* tdev2adap (struct t3cdev*) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int offload_close(struct t3cdev *tdev)
{
	struct adapter *adapter = tdev2adap(tdev);
	struct t3c_data *td = T3C_DATA(tdev);

	if (!test_bit(OFFLOAD_DEVMAP_BIT, &adapter->open_device_map))
		return 0;

	/* Call back all registered clients */
	cxgb3_remove_clients(tdev);

	sysfs_remove_group(&tdev->lldev->dev.kobj, &offload_attr_group);

	/* Flush work scheduled while releasing TIDs */
	spin_lock_bh(&td->tid_release_lock);
	flush_work(&td->tid_release_task);
	cancel_work_sync(&td->tid_release_task);
	spin_unlock_bh(&td->tid_release_lock);

	tdev->lldev = NULL;
	cxgb3_set_dummy_ops(tdev);
	t3_tp_set_offload_mode(adapter, 0);
	clear_bit(OFFLOAD_DEVMAP_BIT, &adapter->open_device_map);

	if (!adapter->open_device_map)
		cxgb_down(adapter, 0);

	cxgb3_offload_deactivate(adapter);
	return 0;
}