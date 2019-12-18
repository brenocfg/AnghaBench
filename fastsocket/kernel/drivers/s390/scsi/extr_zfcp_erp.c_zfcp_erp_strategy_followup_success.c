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
struct zfcp_erp_action {int action; int /*<<< orphan*/  port; int /*<<< orphan*/  adapter; } ;

/* Variables and functions */
#define  ZFCP_ERP_ACTION_REOPEN_ADAPTER 130 
#define  ZFCP_ERP_ACTION_REOPEN_PORT 129 
#define  ZFCP_ERP_ACTION_REOPEN_PORT_FORCED 128 
 int /*<<< orphan*/  _zfcp_erp_port_reopen (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _zfcp_erp_port_reopen_all (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _zfcp_erp_unit_reopen_all (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void zfcp_erp_strategy_followup_success(struct zfcp_erp_action *act)
{
	switch (act->action) {
	case ZFCP_ERP_ACTION_REOPEN_ADAPTER:
		_zfcp_erp_port_reopen_all(act->adapter, 0, "ersfs_1", NULL);
		break;
	case ZFCP_ERP_ACTION_REOPEN_PORT_FORCED:
		_zfcp_erp_port_reopen(act->port, 0, "ersfs_2", NULL);
		break;
	case ZFCP_ERP_ACTION_REOPEN_PORT:
		_zfcp_erp_unit_reopen_all(act->port, 0, "ersfs_3", NULL);
		break;
	}
}