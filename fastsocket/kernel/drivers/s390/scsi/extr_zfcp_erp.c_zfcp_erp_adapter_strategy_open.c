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
struct zfcp_erp_action {struct zfcp_adapter* adapter; } ;
struct zfcp_adapter {int /*<<< orphan*/  status; } ;

/* Variables and functions */
 int ZFCP_ERP_FAILED ; 
 int ZFCP_ERP_SUCCEEDED ; 
 int ZFCP_STATUS_ADAPTER_LINK_UNPLUGGED ; 
 int ZFCP_STATUS_ADAPTER_XCONFIG_OK ; 
 int /*<<< orphan*/  ZFCP_STATUS_COMMON_OPEN ; 
 int /*<<< orphan*/  atomic_clear_mask (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_set_mask (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfcp_erp_adapter_strategy_close (struct zfcp_erp_action*) ; 
 scalar_t__ zfcp_erp_adapter_strategy_open_fsf (struct zfcp_erp_action*) ; 
 scalar_t__ zfcp_erp_adapter_strategy_open_qdio (struct zfcp_erp_action*) ; 

__attribute__((used)) static int zfcp_erp_adapter_strategy_open(struct zfcp_erp_action *act)
{
	struct zfcp_adapter *adapter = act->adapter;

	if (zfcp_erp_adapter_strategy_open_qdio(act)) {
		atomic_clear_mask(ZFCP_STATUS_ADAPTER_XCONFIG_OK |
				  ZFCP_STATUS_ADAPTER_LINK_UNPLUGGED,
				  &adapter->status);
		return ZFCP_ERP_FAILED;
	}

	if (zfcp_erp_adapter_strategy_open_fsf(act)) {
		zfcp_erp_adapter_strategy_close(act);
		return ZFCP_ERP_FAILED;
	}

	atomic_set_mask(ZFCP_STATUS_COMMON_OPEN, &adapter->status);

	return ZFCP_ERP_SUCCEEDED;
}