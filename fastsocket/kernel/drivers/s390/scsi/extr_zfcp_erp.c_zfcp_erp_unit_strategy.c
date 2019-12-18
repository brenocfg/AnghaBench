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
struct zfcp_unit {int /*<<< orphan*/  status; } ;
struct zfcp_erp_action {int step; int status; struct zfcp_unit* unit; } ;

/* Variables and functions */
 int ZFCP_ERP_EXIT ; 
 int ZFCP_ERP_FAILED ; 
#define  ZFCP_ERP_STEP_UNINITIALIZED 130 
#define  ZFCP_ERP_STEP_UNIT_CLOSING 129 
#define  ZFCP_ERP_STEP_UNIT_OPENING 128 
 int ZFCP_ERP_SUCCEEDED ; 
 int ZFCP_STATUS_COMMON_OPEN ; 
 int ZFCP_STATUS_ERP_CLOSE_ONLY ; 
 int atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfcp_erp_unit_strategy_clearstati (struct zfcp_unit*) ; 
 int zfcp_erp_unit_strategy_close (struct zfcp_erp_action*) ; 
 int zfcp_erp_unit_strategy_open (struct zfcp_erp_action*) ; 

__attribute__((used)) static int zfcp_erp_unit_strategy(struct zfcp_erp_action *erp_action)
{
	struct zfcp_unit *unit = erp_action->unit;

	switch (erp_action->step) {
	case ZFCP_ERP_STEP_UNINITIALIZED:
		zfcp_erp_unit_strategy_clearstati(unit);
		if (atomic_read(&unit->status) & ZFCP_STATUS_COMMON_OPEN)
			return zfcp_erp_unit_strategy_close(erp_action);
		/* already closed, fall through */
	case ZFCP_ERP_STEP_UNIT_CLOSING:
		if (atomic_read(&unit->status) & ZFCP_STATUS_COMMON_OPEN)
			return ZFCP_ERP_FAILED;
		if (erp_action->status & ZFCP_STATUS_ERP_CLOSE_ONLY)
			return ZFCP_ERP_EXIT;
		return zfcp_erp_unit_strategy_open(erp_action);

	case ZFCP_ERP_STEP_UNIT_OPENING:
		if (atomic_read(&unit->status) & ZFCP_STATUS_COMMON_OPEN)
			return ZFCP_ERP_SUCCEEDED;
	}
	return ZFCP_ERP_FAILED;
}