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
struct zfcp_adapter {int dummy; } ;

/* Variables and functions */
#define  ZFCP_ERP_ACTION_REOPEN_ADAPTER 131 
#define  ZFCP_ERP_ACTION_REOPEN_PORT 130 
#define  ZFCP_ERP_ACTION_REOPEN_PORT_FORCED 129 
#define  ZFCP_ERP_ACTION_REOPEN_UNIT 128 
 int zfcp_erp_strategy_check_adapter (struct zfcp_adapter*,int) ; 
 int zfcp_erp_strategy_check_port (struct zfcp_port*,int) ; 
 int zfcp_erp_strategy_check_unit (struct zfcp_unit*,int) ; 

__attribute__((used)) static int zfcp_erp_strategy_check_target(struct zfcp_erp_action *erp_action,
					  int result)
{
	struct zfcp_adapter *adapter = erp_action->adapter;
	struct zfcp_port *port = erp_action->port;
	struct zfcp_unit *unit = erp_action->unit;

	switch (erp_action->action) {

	case ZFCP_ERP_ACTION_REOPEN_UNIT:
		result = zfcp_erp_strategy_check_unit(unit, result);
		break;

	case ZFCP_ERP_ACTION_REOPEN_PORT_FORCED:
	case ZFCP_ERP_ACTION_REOPEN_PORT:
		result = zfcp_erp_strategy_check_port(port, result);
		break;

	case ZFCP_ERP_ACTION_REOPEN_ADAPTER:
		result = zfcp_erp_strategy_check_adapter(adapter, result);
		break;
	}
	return result;
}