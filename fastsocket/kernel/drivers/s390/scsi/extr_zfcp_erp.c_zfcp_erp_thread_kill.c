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
struct zfcp_adapter {int /*<<< orphan*/  erp_running_head; int /*<<< orphan*/  erp_ready_head; int /*<<< orphan*/ * erp_thread; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  kthread_stop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 

void zfcp_erp_thread_kill(struct zfcp_adapter *adapter)
{
	kthread_stop(adapter->erp_thread);
	adapter->erp_thread = NULL;
	WARN_ON(!list_empty(&adapter->erp_ready_head));
	WARN_ON(!list_empty(&adapter->erp_running_head));
}