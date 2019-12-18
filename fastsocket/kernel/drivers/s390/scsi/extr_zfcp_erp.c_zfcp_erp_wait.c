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
struct zfcp_adapter {int /*<<< orphan*/  status; int /*<<< orphan*/  erp_done_wqh; } ;

/* Variables and functions */
 int ZFCP_STATUS_ADAPTER_ERP_PENDING ; 
 int atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wait_event (int /*<<< orphan*/ ,int) ; 

void zfcp_erp_wait(struct zfcp_adapter *adapter)
{
	wait_event(adapter->erp_done_wqh,
		   !(atomic_read(&adapter->status) &
			ZFCP_STATUS_ADAPTER_ERP_PENDING));
}