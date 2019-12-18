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
struct zfcp_adapter {int /*<<< orphan*/  status; TYPE_1__* ccw_device; int /*<<< orphan*/  erp_counter; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ZFCP_ERP_EXIT ; 
#define  ZFCP_ERP_FAILED 129 
#define  ZFCP_ERP_SUCCEEDED 128 
 int ZFCP_MAX_ERPS ; 
 int ZFCP_STATUS_COMMON_ERP_FAILED ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  zfcp_erp_adapter_block (struct zfcp_adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfcp_erp_adapter_failed (struct zfcp_adapter*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfcp_erp_adapter_unblock (struct zfcp_adapter*) ; 

__attribute__((used)) static int zfcp_erp_strategy_check_adapter(struct zfcp_adapter *adapter,
					   int result)
{
	switch (result) {
	case ZFCP_ERP_SUCCEEDED :
		atomic_set(&adapter->erp_counter, 0);
		zfcp_erp_adapter_unblock(adapter);
		break;

	case ZFCP_ERP_FAILED :
		atomic_inc(&adapter->erp_counter);
		if (atomic_read(&adapter->erp_counter) > ZFCP_MAX_ERPS) {
			dev_err(&adapter->ccw_device->dev,
				"ERP cannot recover an error "
				"on the FCP device\n");
			zfcp_erp_adapter_failed(adapter, "erasck1", NULL);
		}
		break;
	}

	if (atomic_read(&adapter->status) & ZFCP_STATUS_COMMON_ERP_FAILED) {
		zfcp_erp_adapter_block(adapter, 0);
		result = ZFCP_ERP_EXIT;
	}
	return result;
}