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
struct controller {int dummy; } ;

/* Variables and functions */
 scalar_t__ atomic_dec_and_test (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  destroy_workqueue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct controller*) ; 
 int /*<<< orphan*/  pcie_cleanup_slot (struct controller*) ; 
 int /*<<< orphan*/  pcie_shutdown_notification (struct controller*) ; 
 int /*<<< orphan*/  pciehp_num_controllers ; 
 int /*<<< orphan*/  pciehp_wq ; 

void pciehp_release_ctrl(struct controller *ctrl)
{
	pcie_shutdown_notification(ctrl);
	pcie_cleanup_slot(ctrl);
	/*
	 * If this is the last controller to be released, destroy the
	 * pciehp work queue
	 */
	if (atomic_dec_and_test(&pciehp_num_controllers))
		destroy_workqueue(pciehp_wq);
	kfree(ctrl);
}