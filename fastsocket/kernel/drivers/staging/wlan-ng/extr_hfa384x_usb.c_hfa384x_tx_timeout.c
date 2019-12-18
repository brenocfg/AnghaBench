#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {TYPE_4__* priv; } ;
typedef  TYPE_3__ wlandevice_t ;
struct TYPE_6__ {int /*<<< orphan*/  lock; } ;
struct TYPE_9__ {TYPE_1__ ctlxq; int /*<<< orphan*/  usb_work; int /*<<< orphan*/  usb_flags; TYPE_2__* wlandev; } ;
typedef  TYPE_4__ hfa384x_t ;
struct TYPE_7__ {int /*<<< orphan*/  hwremoved; } ;

/* Variables and functions */
 int /*<<< orphan*/  WORK_RX_HALT ; 
 int /*<<< orphan*/  WORK_TX_HALT ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void hfa384x_tx_timeout(wlandevice_t *wlandev)
{
	hfa384x_t *hw = wlandev->priv;
	unsigned long flags;

	spin_lock_irqsave(&hw->ctlxq.lock, flags);

	if (!hw->wlandev->hwremoved &&
	    /* Note the bitwise OR, not the logical OR. */
	    (!test_and_set_bit(WORK_TX_HALT, &hw->usb_flags) |
	     !test_and_set_bit(WORK_RX_HALT, &hw->usb_flags))) {
		schedule_work(&hw->usb_work);
	}

	spin_unlock_irqrestore(&hw->ctlxq.lock, flags);
}