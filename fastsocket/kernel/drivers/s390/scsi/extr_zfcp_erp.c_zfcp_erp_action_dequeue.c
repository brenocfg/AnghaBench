#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct zfcp_erp_action {int status; int action; struct zfcp_adapter* adapter; TYPE_2__* port; TYPE_1__* unit; int /*<<< orphan*/  list; } ;
struct zfcp_adapter {int /*<<< orphan*/  status; int /*<<< orphan*/  erp_low_mem_count; int /*<<< orphan*/  erp_total_count; } ;
struct TYPE_4__ {int /*<<< orphan*/  status; } ;
struct TYPE_3__ {int /*<<< orphan*/  status; } ;

/* Variables and functions */
#define  ZFCP_ERP_ACTION_REOPEN_ADAPTER 131 
#define  ZFCP_ERP_ACTION_REOPEN_PORT 130 
#define  ZFCP_ERP_ACTION_REOPEN_PORT_FORCED 129 
#define  ZFCP_ERP_ACTION_REOPEN_UNIT 128 
 int /*<<< orphan*/  ZFCP_STATUS_COMMON_ERP_INUSE ; 
 int ZFCP_STATUS_ERP_LOWMEM ; 
 int /*<<< orphan*/  atomic_clear_mask (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfcp_dbf_rec_action (char*,struct zfcp_erp_action*) ; 

__attribute__((used)) static void zfcp_erp_action_dequeue(struct zfcp_erp_action *erp_action)
{
	struct zfcp_adapter *adapter = erp_action->adapter;

	adapter->erp_total_count--;
	if (erp_action->status & ZFCP_STATUS_ERP_LOWMEM) {
		adapter->erp_low_mem_count--;
		erp_action->status &= ~ZFCP_STATUS_ERP_LOWMEM;
	}

	list_del(&erp_action->list);
	zfcp_dbf_rec_action("eractd1", erp_action);

	switch (erp_action->action) {
	case ZFCP_ERP_ACTION_REOPEN_UNIT:
		atomic_clear_mask(ZFCP_STATUS_COMMON_ERP_INUSE,
				  &erp_action->unit->status);
		break;

	case ZFCP_ERP_ACTION_REOPEN_PORT_FORCED:
	case ZFCP_ERP_ACTION_REOPEN_PORT:
		atomic_clear_mask(ZFCP_STATUS_COMMON_ERP_INUSE,
				  &erp_action->port->status);
		break;

	case ZFCP_ERP_ACTION_REOPEN_ADAPTER:
		atomic_clear_mask(ZFCP_STATUS_COMMON_ERP_INUSE,
				  &erp_action->adapter->status);
		break;
	}
}