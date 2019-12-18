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
struct zfcp_unit {int dummy; } ;
struct zfcp_port {int dummy; } ;
struct zfcp_erp_action {int action; struct zfcp_unit* unit; struct zfcp_port* port; struct zfcp_adapter* adapter; } ;
struct zfcp_adapter {int /*<<< orphan*/  service_level; } ;

/* Variables and functions */
#define  ZFCP_ERP_ACTION_REOPEN_ADAPTER 131 
#define  ZFCP_ERP_ACTION_REOPEN_PORT 130 
#define  ZFCP_ERP_ACTION_REOPEN_PORT_FORCED 129 
#define  ZFCP_ERP_ACTION_REOPEN_UNIT 128 
 int ZFCP_ERP_SUCCEEDED ; 
 int /*<<< orphan*/  register_service_level (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unregister_service_level (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfcp_adapter_put (struct zfcp_adapter*) ; 
 int /*<<< orphan*/  zfcp_fc_conditional_port_scan (struct zfcp_adapter*) ; 
 int /*<<< orphan*/  zfcp_port_put (struct zfcp_port*) ; 
 int /*<<< orphan*/  zfcp_scsi_schedule_rport_register (struct zfcp_port*) ; 
 int /*<<< orphan*/  zfcp_unit_put (struct zfcp_unit*) ; 

__attribute__((used)) static void zfcp_erp_action_cleanup(struct zfcp_erp_action *act, int result)
{
	struct zfcp_adapter *adapter = act->adapter;
	struct zfcp_port *port = act->port;
	struct zfcp_unit *unit = act->unit;

	switch (act->action) {
	case ZFCP_ERP_ACTION_REOPEN_UNIT:
		zfcp_unit_put(unit);
		break;

	case ZFCP_ERP_ACTION_REOPEN_PORT:
		if (result == ZFCP_ERP_SUCCEEDED)
			zfcp_scsi_schedule_rport_register(port);
		/* fall through */
	case ZFCP_ERP_ACTION_REOPEN_PORT_FORCED:
		zfcp_port_put(port);
		break;

	case ZFCP_ERP_ACTION_REOPEN_ADAPTER:
		if (result == ZFCP_ERP_SUCCEEDED) {
			register_service_level(&adapter->service_level);
			zfcp_fc_conditional_port_scan(adapter);
		} else
			unregister_service_level(&adapter->service_level);
		zfcp_adapter_put(adapter);
		break;
	}
}