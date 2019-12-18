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
struct zfcp_adapter {struct zfcp_adapter* stats_reset_data; struct zfcp_adapter* fc_stats; struct zfcp_adapter* req_list; int /*<<< orphan*/  qdio; int /*<<< orphan*/  dbf; int /*<<< orphan*/  req_list_lock; TYPE_2__* ccw_device; } ;
struct TYPE_3__ {int /*<<< orphan*/  kobj; } ;
struct TYPE_4__ {TYPE_1__ dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct zfcp_adapter*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  sysfs_remove_group (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfcp_dbf_adapter_unregister (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfcp_erp_thread_kill (struct zfcp_adapter*) ; 
 int /*<<< orphan*/  zfcp_free_low_mem_buffers (struct zfcp_adapter*) ; 
 int /*<<< orphan*/  zfcp_qdio_destroy (int /*<<< orphan*/ ) ; 
 int zfcp_reqlist_isempty (struct zfcp_adapter*) ; 
 int /*<<< orphan*/  zfcp_sysfs_adapter_attrs ; 

void zfcp_adapter_dequeue(struct zfcp_adapter *adapter)
{
	int retval = 0;
	unsigned long flags;

	sysfs_remove_group(&adapter->ccw_device->dev.kobj,
			   &zfcp_sysfs_adapter_attrs);
	/* sanity check: no pending FSF requests */
	spin_lock_irqsave(&adapter->req_list_lock, flags);
	retval = zfcp_reqlist_isempty(adapter);
	spin_unlock_irqrestore(&adapter->req_list_lock, flags);
	if (!retval)
		return;

	zfcp_erp_thread_kill(adapter);
	zfcp_dbf_adapter_unregister(adapter->dbf);
	zfcp_free_low_mem_buffers(adapter);
	zfcp_qdio_destroy(adapter->qdio);
	kfree(adapter->req_list);
	kfree(adapter->fc_stats);
	kfree(adapter->stats_reset_data);
	kfree(adapter);
}