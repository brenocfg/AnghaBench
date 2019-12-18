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
struct zfcp_adapter {int /*<<< orphan*/  erp_lock; int /*<<< orphan*/  erp_done_wqh; int /*<<< orphan*/  status; int /*<<< orphan*/  erp_running_head; int /*<<< orphan*/  erp_ready_head; } ;
struct TYPE_2__ {int /*<<< orphan*/  config_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  ZFCP_STATUS_ADAPTER_ERP_PENDING ; 
 int /*<<< orphan*/  atomic_clear_mask (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  read_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 
 TYPE_1__ zfcp_data ; 

__attribute__((used)) static void zfcp_erp_wakeup(struct zfcp_adapter *adapter)
{
	unsigned long flags;

	read_lock_irqsave(&zfcp_data.config_lock, flags);
	read_lock(&adapter->erp_lock);
	if (list_empty(&adapter->erp_ready_head) &&
	    list_empty(&adapter->erp_running_head)) {
			atomic_clear_mask(ZFCP_STATUS_ADAPTER_ERP_PENDING,
					  &adapter->status);
			wake_up(&adapter->erp_done_wqh);
	}
	read_unlock(&adapter->erp_lock);
	read_unlock_irqrestore(&zfcp_data.config_lock, flags);
}