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
struct bnx2x {int /*<<< orphan*/  sp_task; int /*<<< orphan*/  interrupt_occurred; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  bnx2x_wq ; 
 int queue_delayed_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smp_wmb () ; 

__attribute__((used)) static int bnx2x_schedule_sp_task(struct bnx2x *bp)
{
	/* Set the interrupt occurred bit for the sp-task to recognize it
	 * must ack the interrupt and transition according to the IGU
	 * state machine.
	 */
	atomic_set(&bp->interrupt_occurred, 1);

	/* The sp_task must execute only after this bit
	 * is set, otherwise we will get out of sync and miss all
	 * further interrupts. Hence, the barrier.
	 */
	smp_wmb();

	/* schedule sp_task to workqueue */
	return queue_delayed_work(bnx2x_wq, &bp->sp_task, 0);
}