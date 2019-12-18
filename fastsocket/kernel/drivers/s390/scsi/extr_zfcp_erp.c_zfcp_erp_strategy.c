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
struct zfcp_erp_action {int status; struct zfcp_adapter* adapter; } ;
struct zfcp_adapter {int /*<<< orphan*/  erp_lock; int /*<<< orphan*/  erp_low_mem_count; int /*<<< orphan*/  erp_total_count; } ;
struct TYPE_2__ {int /*<<< orphan*/  config_lock; } ;

/* Variables and functions */
#define  ZFCP_ERP_CONTINUES 129 
 int ZFCP_ERP_DISMISSED ; 
 int ZFCP_ERP_EXIT ; 
 int ZFCP_ERP_FAILED ; 
#define  ZFCP_ERP_NOMEM 128 
 int ZFCP_ERP_SUCCEEDED ; 
 int ZFCP_STATUS_ERP_DISMISSED ; 
 int ZFCP_STATUS_ERP_LOWMEM ; 
 int ZFCP_STATUS_ERP_TIMEDOUT ; 
 int /*<<< orphan*/  _zfcp_erp_adapter_reopen (struct zfcp_adapter*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  read_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  write_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_unlock (int /*<<< orphan*/ *) ; 
 TYPE_1__ zfcp_data ; 
 int /*<<< orphan*/  zfcp_erp_action_cleanup (struct zfcp_erp_action*,int) ; 
 int /*<<< orphan*/  zfcp_erp_action_dequeue (struct zfcp_erp_action*) ; 
 int /*<<< orphan*/  zfcp_erp_action_to_running (struct zfcp_erp_action*) ; 
 int /*<<< orphan*/  zfcp_erp_strategy_check_fsfreq (struct zfcp_erp_action*) ; 
 int zfcp_erp_strategy_check_target (struct zfcp_erp_action*,int) ; 
 int zfcp_erp_strategy_do_action (struct zfcp_erp_action*) ; 
 int /*<<< orphan*/  zfcp_erp_strategy_followup_failed (struct zfcp_erp_action*) ; 
 int /*<<< orphan*/  zfcp_erp_strategy_followup_success (struct zfcp_erp_action*) ; 
 int /*<<< orphan*/  zfcp_erp_strategy_memwait (struct zfcp_erp_action*) ; 
 int zfcp_erp_strategy_statechange (struct zfcp_erp_action*,int) ; 

__attribute__((used)) static int zfcp_erp_strategy(struct zfcp_erp_action *erp_action)
{
	int retval;
	struct zfcp_adapter *adapter = erp_action->adapter;
	unsigned long flags;

	read_lock_irqsave(&zfcp_data.config_lock, flags);
	write_lock(&adapter->erp_lock);

	zfcp_erp_strategy_check_fsfreq(erp_action);

	if (erp_action->status & ZFCP_STATUS_ERP_DISMISSED) {
		zfcp_erp_action_dequeue(erp_action);
		retval = ZFCP_ERP_DISMISSED;
		goto unlock;
	}

	if (erp_action->status & ZFCP_STATUS_ERP_TIMEDOUT) {
		retval = ZFCP_ERP_FAILED;
		goto check_target;
	}

	zfcp_erp_action_to_running(erp_action);

	/* no lock to allow for blocking operations */
	write_unlock(&adapter->erp_lock);
	read_unlock_irqrestore(&zfcp_data.config_lock, flags);
	retval = zfcp_erp_strategy_do_action(erp_action);
	read_lock_irqsave(&zfcp_data.config_lock, flags);
	write_lock(&adapter->erp_lock);

	if (erp_action->status & ZFCP_STATUS_ERP_DISMISSED)
		retval = ZFCP_ERP_CONTINUES;

	switch (retval) {
	case ZFCP_ERP_NOMEM:
		if (!(erp_action->status & ZFCP_STATUS_ERP_LOWMEM)) {
			++adapter->erp_low_mem_count;
			erp_action->status |= ZFCP_STATUS_ERP_LOWMEM;
		}
		if (adapter->erp_total_count == adapter->erp_low_mem_count)
			_zfcp_erp_adapter_reopen(adapter, 0, "erstgy1", NULL);
		else {
			zfcp_erp_strategy_memwait(erp_action);
			retval = ZFCP_ERP_CONTINUES;
		}
		goto unlock;

	case ZFCP_ERP_CONTINUES:
		if (erp_action->status & ZFCP_STATUS_ERP_LOWMEM) {
			--adapter->erp_low_mem_count;
			erp_action->status &= ~ZFCP_STATUS_ERP_LOWMEM;
		}
		goto unlock;
	}

check_target:
	retval = zfcp_erp_strategy_check_target(erp_action, retval);
	zfcp_erp_action_dequeue(erp_action);
	retval = zfcp_erp_strategy_statechange(erp_action, retval);
	if (retval == ZFCP_ERP_EXIT)
		goto unlock;
	if (retval == ZFCP_ERP_SUCCEEDED)
		zfcp_erp_strategy_followup_success(erp_action);
	if (retval == ZFCP_ERP_FAILED)
		zfcp_erp_strategy_followup_failed(erp_action);

 unlock:
	write_unlock(&adapter->erp_lock);
	read_unlock_irqrestore(&zfcp_data.config_lock, flags);

	if (retval != ZFCP_ERP_CONTINUES)
		zfcp_erp_action_cleanup(erp_action, retval);

	return retval;
}