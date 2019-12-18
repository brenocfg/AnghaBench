#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  hfa384x_usbctlx_t ;
struct TYPE_6__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  active; } ;
struct TYPE_7__ {int resp_timer_done; TYPE_1__ ctlxq; } ;
typedef  TYPE_2__ hfa384x_t ;

/* Variables and functions */
 int /*<<< orphan*/ * get_active_ctlx (TYPE_2__*) ; 
 int /*<<< orphan*/  hfa384x_usbctlxq_run (TYPE_2__*) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ unlocked_usbctlx_cancel_async (TYPE_2__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void hfa384x_usbctlx_resptimerfn(unsigned long data)
{
	hfa384x_t *hw = (hfa384x_t *) data;
	unsigned long flags;

	spin_lock_irqsave(&hw->ctlxq.lock, flags);

	hw->resp_timer_done = 1;

	/* The active list will be empty if the
	 * adapter has been unplugged ...
	 */
	if (!list_empty(&hw->ctlxq.active)) {
		hfa384x_usbctlx_t *ctlx = get_active_ctlx(hw);

		if (unlocked_usbctlx_cancel_async(hw, ctlx) == 0) {
			spin_unlock_irqrestore(&hw->ctlxq.lock, flags);
			hfa384x_usbctlxq_run(hw);
			goto done;
		}
	}

	spin_unlock_irqrestore(&hw->ctlxq.lock, flags);

done:
	;

}