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
struct ql_adapter {int /*<<< orphan*/  asic_reset_work; int /*<<< orphan*/  workqueue; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  QL_ADAPTER_UP ; 
 int /*<<< orphan*/  QL_ASIC_RECOVERY ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ql_disable_interrupts (struct ql_adapter*) ; 
 int /*<<< orphan*/  ql_link_off (struct ql_adapter*) ; 
 int /*<<< orphan*/  queue_delayed_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void ql_queue_asic_error(struct ql_adapter *qdev)
{
	ql_link_off(qdev);
	ql_disable_interrupts(qdev);
	/* Clear adapter up bit to signal the recovery
	 * process that it shouldn't kill the reset worker
	 * thread
	 */
	clear_bit(QL_ADAPTER_UP, &qdev->flags);
	/* Set asic recovery bit to indicate reset process that we are
	 * in fatal error recovery process rather than normal close
	 */
	set_bit(QL_ASIC_RECOVERY, &qdev->flags);
	queue_delayed_work(qdev->workqueue, &qdev->asic_reset_work, 0);
}