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
struct zfcp_unit {int /*<<< orphan*/  status; TYPE_3__* port; scalar_t__ fcp_lun; int /*<<< orphan*/  erp_counter; } ;
struct TYPE_6__ {scalar_t__ wwpn; TYPE_2__* adapter; } ;
struct TYPE_5__ {TYPE_1__* ccw_device; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ZFCP_ERP_EXIT ; 
#define  ZFCP_ERP_FAILED 129 
#define  ZFCP_ERP_SUCCEEDED 128 
 int ZFCP_MAX_ERPS ; 
 int ZFCP_STATUS_COMMON_ERP_FAILED ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,unsigned long long,unsigned long long) ; 
 int /*<<< orphan*/  zfcp_erp_unit_block (struct zfcp_unit*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfcp_erp_unit_failed (struct zfcp_unit*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfcp_erp_unit_unblock (struct zfcp_unit*) ; 

__attribute__((used)) static int zfcp_erp_strategy_check_unit(struct zfcp_unit *unit, int result)
{
	switch (result) {
	case ZFCP_ERP_SUCCEEDED :
		atomic_set(&unit->erp_counter, 0);
		zfcp_erp_unit_unblock(unit);
		break;
	case ZFCP_ERP_FAILED :
		atomic_inc(&unit->erp_counter);
		if (atomic_read(&unit->erp_counter) > ZFCP_MAX_ERPS) {
			dev_err(&unit->port->adapter->ccw_device->dev,
				"ERP failed for unit 0x%016Lx on "
				"port 0x%016Lx\n",
				(unsigned long long)unit->fcp_lun,
				(unsigned long long)unit->port->wwpn);
			zfcp_erp_unit_failed(unit, "erusck1", NULL);
		}
		break;
	}

	if (atomic_read(&unit->status) & ZFCP_STATUS_COMMON_ERP_FAILED) {
		zfcp_erp_unit_block(unit, 0);
		result = ZFCP_ERP_EXIT;
	}
	return result;
}