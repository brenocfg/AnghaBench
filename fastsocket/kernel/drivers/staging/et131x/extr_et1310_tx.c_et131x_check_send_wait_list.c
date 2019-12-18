#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct list_head {int dummy; } ;
struct TYPE_4__ {struct list_head* next; } ;
struct TYPE_3__ {int /*<<< orphan*/  nWaitSend; TYPE_2__ SendWaitQueue; } ;
struct et131x_adapter {int /*<<< orphan*/  SendWaitLock; TYPE_1__ TxRing; } ;

/* Variables and functions */
 scalar_t__ MP_TCB_RESOURCES_AVAILABLE (struct et131x_adapter*) ; 
 int /*<<< orphan*/  list_empty (TYPE_2__*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void et131x_check_send_wait_list(struct et131x_adapter *etdev)
{
	unsigned long flags;

	spin_lock_irqsave(&etdev->SendWaitLock, flags);

	while (!list_empty(&etdev->TxRing.SendWaitQueue) &&
				MP_TCB_RESOURCES_AVAILABLE(etdev)) {
		struct list_head *entry;

		entry = etdev->TxRing.SendWaitQueue.next;

		etdev->TxRing.nWaitSend--;
	}

	spin_unlock_irqrestore(&etdev->SendWaitLock, flags);
}