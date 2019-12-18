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
struct rfcomm_dlc {scalar_t__ state; struct rfcomm_dev* owner; } ;
struct rfcomm_dev {int err; int /*<<< orphan*/  tty; int /*<<< orphan*/  id; int /*<<< orphan*/  flags; int /*<<< orphan*/  wait; } ;

/* Variables and functions */
 scalar_t__ BT_CLOSED ; 
 int /*<<< orphan*/  BT_DBG (char*,struct rfcomm_dlc*,struct rfcomm_dev*,int) ; 
 int /*<<< orphan*/  RFCOMM_RELEASE_ONHUP ; 
 int /*<<< orphan*/  rfcomm_dev_del (struct rfcomm_dev*) ; 
 int /*<<< orphan*/ * rfcomm_dev_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rfcomm_dev_put (struct rfcomm_dev*) ; 
 int /*<<< orphan*/  rfcomm_dlc_lock (struct rfcomm_dlc*) ; 
 int /*<<< orphan*/  rfcomm_dlc_unlock (struct rfcomm_dlc*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tty_hangup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void rfcomm_dev_state_change(struct rfcomm_dlc *dlc, int err)
{
	struct rfcomm_dev *dev = dlc->owner;
	if (!dev)
		return;

	BT_DBG("dlc %p dev %p err %d", dlc, dev, err);

	dev->err = err;
	wake_up_interruptible(&dev->wait);

	if (dlc->state == BT_CLOSED) {
		if (!dev->tty) {
			if (test_bit(RFCOMM_RELEASE_ONHUP, &dev->flags)) {
				/* Drop DLC lock here to avoid deadlock
				 * 1. rfcomm_dev_get will take rfcomm_dev_lock
				 *    but in rfcomm_dev_add there's lock order:
				 *    rfcomm_dev_lock -> dlc lock
				 * 2. rfcomm_dev_put will deadlock if it's
				 *    the last reference
				 */
				rfcomm_dlc_unlock(dlc);
				if (rfcomm_dev_get(dev->id) == NULL) {
					rfcomm_dlc_lock(dlc);
					return;
				}

				rfcomm_dev_del(dev);
				rfcomm_dev_put(dev);
				rfcomm_dlc_lock(dlc);
			}
		} else
			tty_hangup(dev->tty);
	}
}