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
struct zfcp_erp_action {int action; } ;

/* Variables and functions */
#define  ZFCP_ERP_ACTION_REOPEN_ADAPTER 131 
#define  ZFCP_ERP_ACTION_REOPEN_PORT 130 
#define  ZFCP_ERP_ACTION_REOPEN_PORT_FORCED 129 
#define  ZFCP_ERP_ACTION_REOPEN_UNIT 128 
 int ZFCP_ERP_FAILED ; 
 int zfcp_erp_adapter_strategy (struct zfcp_erp_action*) ; 
 int zfcp_erp_port_forced_strategy (struct zfcp_erp_action*) ; 
 int zfcp_erp_port_strategy (struct zfcp_erp_action*) ; 
 int zfcp_erp_unit_strategy (struct zfcp_erp_action*) ; 

__attribute__((used)) static int zfcp_erp_strategy_do_action(struct zfcp_erp_action *erp_action)
{
	switch (erp_action->action) {
	case ZFCP_ERP_ACTION_REOPEN_ADAPTER:
		return zfcp_erp_adapter_strategy(erp_action);
	case ZFCP_ERP_ACTION_REOPEN_PORT_FORCED:
		return zfcp_erp_port_forced_strategy(erp_action);
	case ZFCP_ERP_ACTION_REOPEN_PORT:
		return zfcp_erp_port_strategy(erp_action);
	case ZFCP_ERP_ACTION_REOPEN_UNIT:
		return zfcp_erp_unit_strategy(erp_action);
	}
	return ZFCP_ERP_FAILED;
}