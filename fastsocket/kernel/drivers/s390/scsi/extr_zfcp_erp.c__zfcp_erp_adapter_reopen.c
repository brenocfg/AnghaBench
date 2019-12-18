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
struct zfcp_adapter {int /*<<< orphan*/  status; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  ZFCP_ERP_ACTION_REOPEN_ADAPTER ; 
 int ZFCP_STATUS_COMMON_ERP_FAILED ; 
 int atomic_read (int /*<<< orphan*/ *) ; 
 int zfcp_erp_action_enqueue (int /*<<< orphan*/ ,struct zfcp_adapter*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,void*) ; 
 int /*<<< orphan*/  zfcp_erp_adapter_block (struct zfcp_adapter*,int) ; 
 int /*<<< orphan*/  zfcp_erp_adapter_failed (struct zfcp_adapter*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfcp_scsi_schedule_rports_block (struct zfcp_adapter*) ; 

__attribute__((used)) static int _zfcp_erp_adapter_reopen(struct zfcp_adapter *adapter,
				    int clear_mask, char *id, void *ref)
{
	zfcp_erp_adapter_block(adapter, clear_mask);
	zfcp_scsi_schedule_rports_block(adapter);

	/* ensure propagation of failed status to new devices */
	if (atomic_read(&adapter->status) & ZFCP_STATUS_COMMON_ERP_FAILED) {
		zfcp_erp_adapter_failed(adapter, "erareo1", NULL);
		return -EIO;
	}
	return zfcp_erp_action_enqueue(ZFCP_ERP_ACTION_REOPEN_ADAPTER,
				       adapter, NULL, NULL, id, ref);
}