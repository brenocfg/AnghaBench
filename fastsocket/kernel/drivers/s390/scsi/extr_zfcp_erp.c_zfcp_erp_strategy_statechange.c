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
typedef  int /*<<< orphan*/  u32 ;
struct zfcp_unit {int /*<<< orphan*/  status; } ;
struct zfcp_port {int /*<<< orphan*/  status; } ;
struct zfcp_erp_action {int action; int /*<<< orphan*/  status; struct zfcp_unit* unit; struct zfcp_port* port; struct zfcp_adapter* adapter; } ;
struct zfcp_adapter {int /*<<< orphan*/  status; } ;

/* Variables and functions */
#define  ZFCP_ERP_ACTION_REOPEN_ADAPTER 131 
#define  ZFCP_ERP_ACTION_REOPEN_PORT 130 
#define  ZFCP_ERP_ACTION_REOPEN_PORT_FORCED 129 
#define  ZFCP_ERP_ACTION_REOPEN_UNIT 128 
 int ZFCP_ERP_EXIT ; 
 int /*<<< orphan*/  ZFCP_STATUS_COMMON_ERP_FAILED ; 
 int /*<<< orphan*/  _zfcp_erp_adapter_reopen (struct zfcp_adapter*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _zfcp_erp_port_reopen (struct zfcp_port*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _zfcp_erp_unit_reopen (struct zfcp_unit*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfcp_erp_strat_change_det (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int zfcp_erp_strategy_statechange(struct zfcp_erp_action *act, int ret)
{
	int action = act->action;
	struct zfcp_adapter *adapter = act->adapter;
	struct zfcp_port *port = act->port;
	struct zfcp_unit *unit = act->unit;
	u32 erp_status = act->status;

	switch (action) {
	case ZFCP_ERP_ACTION_REOPEN_ADAPTER:
		if (zfcp_erp_strat_change_det(&adapter->status, erp_status)) {
			_zfcp_erp_adapter_reopen(adapter,
						 ZFCP_STATUS_COMMON_ERP_FAILED,
						 "ersscg1", NULL);
			return ZFCP_ERP_EXIT;
		}
		break;

	case ZFCP_ERP_ACTION_REOPEN_PORT_FORCED:
	case ZFCP_ERP_ACTION_REOPEN_PORT:
		if (zfcp_erp_strat_change_det(&port->status, erp_status)) {
			_zfcp_erp_port_reopen(port,
					      ZFCP_STATUS_COMMON_ERP_FAILED,
					      "ersscg2", NULL);
			return ZFCP_ERP_EXIT;
		}
		break;

	case ZFCP_ERP_ACTION_REOPEN_UNIT:
		if (zfcp_erp_strat_change_det(&unit->status, erp_status)) {
			_zfcp_erp_unit_reopen(unit,
					      ZFCP_STATUS_COMMON_ERP_FAILED,
					      "ersscg3", NULL);
			return ZFCP_ERP_EXIT;
		}
		break;
	}
	return ret;
}