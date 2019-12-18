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
struct zfcp_adapter {int /*<<< orphan*/  scan_work; int /*<<< orphan*/  work_queue; } ;

/* Variables and functions */
 scalar_t__ no_auto_port_rescan ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void zfcp_fc_conditional_port_scan(struct zfcp_adapter *adapter)
{
	if (no_auto_port_rescan)
		return;

	queue_work(adapter->work_queue, &adapter->scan_work);
}