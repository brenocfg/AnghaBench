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
struct zfcp_erp_action {TYPE_1__* adapter; } ;
struct TYPE_2__ {int /*<<< orphan*/  stat_miss; } ;

/* Variables and functions */
 scalar_t__ ZFCP_ERP_FAILED ; 
 int ZFCP_ERP_SUCCEEDED ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 scalar_t__ zfcp_erp_adapter_strat_fsf_xconf (struct zfcp_erp_action*) ; 
 scalar_t__ zfcp_erp_adapter_strategy_open_fsf_xport (struct zfcp_erp_action*) ; 
 scalar_t__ zfcp_status_read_refill (TYPE_1__*) ; 

__attribute__((used)) static int zfcp_erp_adapter_strategy_open_fsf(struct zfcp_erp_action *act)
{
	if (zfcp_erp_adapter_strat_fsf_xconf(act) == ZFCP_ERP_FAILED)
		return ZFCP_ERP_FAILED;

	if (zfcp_erp_adapter_strategy_open_fsf_xport(act) == ZFCP_ERP_FAILED)
		return ZFCP_ERP_FAILED;

	atomic_set(&act->adapter->stat_miss, 16);
	if (zfcp_status_read_refill(act->adapter))
		return ZFCP_ERP_FAILED;

	return ZFCP_ERP_SUCCEEDED;
}