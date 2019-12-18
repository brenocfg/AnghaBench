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
struct zfcp_erp_action {int /*<<< orphan*/  list; } ;
struct zfcp_adapter {int /*<<< orphan*/  dbf; int /*<<< orphan*/  erp_ready_wq; int /*<<< orphan*/  erp_ready_head; int /*<<< orphan*/  erp_total_count; int /*<<< orphan*/  status; int /*<<< orphan*/  erp_thread; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  ZFCP_STATUS_ADAPTER_ERP_PENDING ; 
 int /*<<< orphan*/  atomic_set_mask (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfcp_dbf_rec_thread (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfcp_dbf_rec_trigger (char*,void*,int,int,struct zfcp_erp_action*,struct zfcp_adapter*,struct zfcp_port*,struct zfcp_unit*) ; 
 int zfcp_erp_required_act (int,struct zfcp_adapter*,struct zfcp_port*,struct zfcp_unit*) ; 
 struct zfcp_erp_action* zfcp_erp_setup_act (int,struct zfcp_adapter*,struct zfcp_port*,struct zfcp_unit*) ; 

__attribute__((used)) static int zfcp_erp_action_enqueue(int want, struct zfcp_adapter *adapter,
				   struct zfcp_port *port,
				   struct zfcp_unit *unit, char *id, void *ref)
{
	int retval = 1, need;
	struct zfcp_erp_action *act = NULL;

	if (!adapter->erp_thread)
		return -EIO;

	need = zfcp_erp_required_act(want, adapter, port, unit);
	if (!need)
		goto out;

	atomic_set_mask(ZFCP_STATUS_ADAPTER_ERP_PENDING, &adapter->status);
	act = zfcp_erp_setup_act(need, adapter, port, unit);
	if (!act)
		goto out;
	++adapter->erp_total_count;
	list_add_tail(&act->list, &adapter->erp_ready_head);
	wake_up(&adapter->erp_ready_wq);
	zfcp_dbf_rec_thread("eracte1", adapter->dbf);
	retval = 0;
 out:
	zfcp_dbf_rec_trigger(id, ref, want, need, act, adapter, port, unit);
	return retval;
}