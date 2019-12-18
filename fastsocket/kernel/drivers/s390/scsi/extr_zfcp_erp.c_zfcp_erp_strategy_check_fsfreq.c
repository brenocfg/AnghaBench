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
struct zfcp_erp_action {int status; TYPE_1__* fsf_req; struct zfcp_adapter* adapter; } ;
struct zfcp_adapter {int /*<<< orphan*/  req_list_lock; } ;
struct TYPE_2__ {int status; struct zfcp_erp_action* erp_action; } ;

/* Variables and functions */
 int ZFCP_STATUS_ERP_DISMISSED ; 
 int ZFCP_STATUS_ERP_TIMEDOUT ; 
 int ZFCP_STATUS_FSFREQ_DISMISSED ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfcp_dbf_rec_action (char*,struct zfcp_erp_action*) ; 
 scalar_t__ zfcp_reqlist_find_safe (struct zfcp_adapter*,TYPE_1__*) ; 

__attribute__((used)) static void zfcp_erp_strategy_check_fsfreq(struct zfcp_erp_action *act)
{
	struct zfcp_adapter *adapter = act->adapter;

	if (!act->fsf_req)
		return;

	spin_lock(&adapter->req_list_lock);
	if (zfcp_reqlist_find_safe(adapter, act->fsf_req) &&
	    act->fsf_req->erp_action == act) {
		if (act->status & (ZFCP_STATUS_ERP_DISMISSED |
				   ZFCP_STATUS_ERP_TIMEDOUT)) {
			act->fsf_req->status |= ZFCP_STATUS_FSFREQ_DISMISSED;
			zfcp_dbf_rec_action("erscf_1", act);
			act->fsf_req->erp_action = NULL;
		}
		if (act->status & ZFCP_STATUS_ERP_TIMEDOUT)
			zfcp_dbf_rec_action("erscf_2", act);
		if (act->fsf_req->status & ZFCP_STATUS_FSFREQ_DISMISSED)
			act->fsf_req = NULL;
	} else
		act->fsf_req = NULL;
	spin_unlock(&adapter->req_list_lock);
}