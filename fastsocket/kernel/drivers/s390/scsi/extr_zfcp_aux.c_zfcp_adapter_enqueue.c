#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  seq_print; } ;
struct TYPE_4__ {int /*<<< orphan*/  list_lock; int /*<<< orphan*/  work; int /*<<< orphan*/  list; } ;
struct zfcp_adapter {int /*<<< orphan*/  qdio; struct zfcp_adapter* req_list; int /*<<< orphan*/  dbf; int /*<<< orphan*/  status; TYPE_2__ service_level; int /*<<< orphan*/  scan_work; int /*<<< orphan*/  stat_work; int /*<<< orphan*/  abort_lock; int /*<<< orphan*/  erp_lock; int /*<<< orphan*/  req_list_lock; TYPE_1__ events; int /*<<< orphan*/  erp_running_head; int /*<<< orphan*/  erp_ready_head; int /*<<< orphan*/  port_list_head; int /*<<< orphan*/  erp_done_wqh; int /*<<< orphan*/  erp_ready_wq; int /*<<< orphan*/  remove_wq; int /*<<< orphan*/  refcount; struct ccw_device* ccw_device; } ;
struct TYPE_6__ {int /*<<< orphan*/  kobj; } ;
struct ccw_device {TYPE_3__ dev; int /*<<< orphan*/ * handler; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZFCP_STATUS_COMMON_REMOVE ; 
 int /*<<< orphan*/  _zfcp_status_read_scheduler ; 
 int /*<<< orphan*/  atomic_clear_mask (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic_set_mask (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_set_drvdata (TYPE_3__*,struct zfcp_adapter*) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct zfcp_adapter*) ; 
 struct zfcp_adapter* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rwlock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 scalar_t__ sysfs_create_group (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfcp_adapter_scsi_register (struct zfcp_adapter*) ; 
 scalar_t__ zfcp_allocate_low_mem_buffers (struct zfcp_adapter*) ; 
 scalar_t__ zfcp_dbf_adapter_register (struct zfcp_adapter*) ; 
 int /*<<< orphan*/  zfcp_dbf_adapter_unregister (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfcp_destroy_adapter_work_queue (struct zfcp_adapter*) ; 
 int /*<<< orphan*/  zfcp_erp_thread_kill (struct zfcp_adapter*) ; 
 scalar_t__ zfcp_erp_thread_setup (struct zfcp_adapter*) ; 
 int /*<<< orphan*/  zfcp_fc_gs_destroy (struct zfcp_adapter*) ; 
 scalar_t__ zfcp_fc_gs_setup (struct zfcp_adapter*) ; 
 int /*<<< orphan*/  zfcp_fc_post_event ; 
 int /*<<< orphan*/  zfcp_fc_scan_ports ; 
 int /*<<< orphan*/  zfcp_free_low_mem_buffers (struct zfcp_adapter*) ; 
 int /*<<< orphan*/  zfcp_print_sl ; 
 int /*<<< orphan*/  zfcp_qdio_destroy (int /*<<< orphan*/ ) ; 
 scalar_t__ zfcp_qdio_setup (struct zfcp_adapter*) ; 
 scalar_t__ zfcp_reqlist_alloc (struct zfcp_adapter*) ; 
 scalar_t__ zfcp_setup_adapter_work_queue (struct zfcp_adapter*) ; 
 int /*<<< orphan*/  zfcp_sysfs_adapter_attrs ; 

int zfcp_adapter_enqueue(struct ccw_device *ccw_device)
{
	struct zfcp_adapter *adapter;

	/*
	 * Note: It is safe to release the list_lock, as any list changes
	 * are protected by the config_mutex, which must be held to get here
	 */

	adapter = kzalloc(sizeof(struct zfcp_adapter), GFP_KERNEL);
	if (!adapter)
		return -ENOMEM;

	ccw_device->handler = NULL;
	adapter->ccw_device = ccw_device;
	atomic_set(&adapter->refcount, 0);

	if (zfcp_qdio_setup(adapter))
		goto qdio_failed;

	if (zfcp_allocate_low_mem_buffers(adapter))
		goto low_mem_buffers_failed;

	if (zfcp_reqlist_alloc(adapter))
		goto low_mem_buffers_failed;

	if (zfcp_dbf_adapter_register(adapter))
		goto debug_register_failed;

	if (zfcp_setup_adapter_work_queue(adapter))
		goto work_queue_failed;

	if (zfcp_fc_gs_setup(adapter))
		goto generic_services_failed;

	init_waitqueue_head(&adapter->remove_wq);
	init_waitqueue_head(&adapter->erp_ready_wq);
	init_waitqueue_head(&adapter->erp_done_wqh);

	INIT_LIST_HEAD(&adapter->port_list_head);
	INIT_LIST_HEAD(&adapter->erp_ready_head);
	INIT_LIST_HEAD(&adapter->erp_running_head);
	INIT_LIST_HEAD(&adapter->events.list);

	INIT_WORK(&adapter->events.work, zfcp_fc_post_event);
	spin_lock_init(&adapter->events.list_lock);

	spin_lock_init(&adapter->req_list_lock);

	rwlock_init(&adapter->erp_lock);
	rwlock_init(&adapter->abort_lock);

	if (zfcp_erp_thread_setup(adapter))
		goto erp_thread_failed;

	INIT_WORK(&adapter->stat_work, _zfcp_status_read_scheduler);
	INIT_WORK(&adapter->scan_work, zfcp_fc_scan_ports);

	adapter->service_level.seq_print = zfcp_print_sl;

	/* mark adapter unusable as long as sysfs registration is not complete */
	atomic_set_mask(ZFCP_STATUS_COMMON_REMOVE, &adapter->status);

	dev_set_drvdata(&ccw_device->dev, adapter);

	if (sysfs_create_group(&ccw_device->dev.kobj,
			       &zfcp_sysfs_adapter_attrs))
		goto sysfs_failed;

	atomic_clear_mask(ZFCP_STATUS_COMMON_REMOVE, &adapter->status);

	if (!zfcp_adapter_scsi_register(adapter))
		return 0;

sysfs_failed:
	zfcp_erp_thread_kill(adapter);
erp_thread_failed:
	zfcp_fc_gs_destroy(adapter);
generic_services_failed:
	zfcp_destroy_adapter_work_queue(adapter);
work_queue_failed:
	zfcp_dbf_adapter_unregister(adapter->dbf);
debug_register_failed:
	dev_set_drvdata(&ccw_device->dev, NULL);
	kfree(adapter->req_list);
low_mem_buffers_failed:
	zfcp_free_low_mem_buffers(adapter);
qdio_failed:
	zfcp_qdio_destroy(adapter->qdio);
	kfree(adapter);
	return -ENOMEM;
}