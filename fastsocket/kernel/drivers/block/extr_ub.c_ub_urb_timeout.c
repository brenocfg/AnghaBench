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
struct ub_dev {int /*<<< orphan*/  lock; int /*<<< orphan*/  work_urb; int /*<<< orphan*/  work_done; } ;

/* Variables and functions */
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  ub_is_completed (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_unlink_urb (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ub_urb_timeout(unsigned long arg)
{
	struct ub_dev *sc = (struct ub_dev *) arg;
	unsigned long flags;

	spin_lock_irqsave(sc->lock, flags);
	if (!ub_is_completed(&sc->work_done))
		usb_unlink_urb(&sc->work_urb);
	spin_unlock_irqrestore(sc->lock, flags);
}