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
struct e1000_adapter {int flags; int /*<<< orphan*/ * ptp_clock; int /*<<< orphan*/  systim_overflow_work; } ;

/* Variables and functions */
 int FLAG_HAS_HW_TIMESTAMP ; 
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  e_info (char*) ; 
 int /*<<< orphan*/  ptp_clock_unregister (int /*<<< orphan*/ *) ; 

void e1000e_ptp_remove(struct e1000_adapter *adapter)
{
	if (!(adapter->flags & FLAG_HAS_HW_TIMESTAMP))
		return;

	cancel_delayed_work_sync(&adapter->systim_overflow_work);

	if (adapter->ptp_clock) {
		ptp_clock_unregister(adapter->ptp_clock);
		adapter->ptp_clock = NULL;
		e_info("removed PHC\n");
	}
}