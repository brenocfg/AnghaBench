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
struct tty_struct {int index; struct rfcomm_dev* driver_data; } ;
struct rfcomm_dlc {scalar_t__ state; } ;
struct rfcomm_dev {int err; struct rfcomm_dlc* dlc; int /*<<< orphan*/  tty_dev; int /*<<< orphan*/  wait; int /*<<< orphan*/  channel; int /*<<< orphan*/  dst; int /*<<< orphan*/  src; int /*<<< orphan*/  flags; struct tty_struct* tty; int /*<<< orphan*/  opened; } ;
struct file {int dummy; } ;

/* Variables and functions */
 scalar_t__ BT_CLOSED ; 
 scalar_t__ BT_CONNECTED ; 
 int /*<<< orphan*/  BT_DBG (char*,...) ; 
 int /*<<< orphan*/  DECLARE_WAITQUEUE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DPM_ORDER_DEV_AFTER_PARENT ; 
 int EINTR ; 
 int ENODEV ; 
 int /*<<< orphan*/  RFCOMM_TTY_ATTACHED ; 
 int /*<<< orphan*/  TASK_INTERRUPTIBLE ; 
 int /*<<< orphan*/  TASK_RUNNING ; 
 int /*<<< orphan*/  add_wait_queue (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int atomic_inc_return (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  batostr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  device_move (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  remove_wait_queue (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct rfcomm_dev* rfcomm_dev_get (int) ; 
 int /*<<< orphan*/  rfcomm_dlc_lock (struct rfcomm_dlc*) ; 
 int rfcomm_dlc_open (struct rfcomm_dlc*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rfcomm_dlc_unlock (struct rfcomm_dlc*) ; 
 int /*<<< orphan*/  rfcomm_dlc_unthrottle (struct rfcomm_dlc*) ; 
 int /*<<< orphan*/  rfcomm_get_device (struct rfcomm_dev*) ; 
 int /*<<< orphan*/  rfcomm_tty_copy_pending (struct rfcomm_dev*) ; 
 int /*<<< orphan*/  schedule () ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_current_state (int /*<<< orphan*/ ) ; 
 scalar_t__ signal_pending (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wait ; 

__attribute__((used)) static int rfcomm_tty_open(struct tty_struct *tty, struct file *filp)
{
	DECLARE_WAITQUEUE(wait, current);
	struct rfcomm_dev *dev;
	struct rfcomm_dlc *dlc;
	int err, id;

	id = tty->index;

	BT_DBG("tty %p id %d", tty, id);

	/* We don't leak this refcount. For reasons which are not entirely
	   clear, the TTY layer will call our ->close() method even if the
	   open fails. We decrease the refcount there, and decreasing it
	   here too would cause breakage. */
	dev = rfcomm_dev_get(id);
	if (!dev)
		return -ENODEV;

	BT_DBG("dev %p dst %s channel %d opened %d", dev, batostr(&dev->dst),
				dev->channel, atomic_read(&dev->opened));

	if (atomic_inc_return(&dev->opened) > 1)
		return 0;

	dlc = dev->dlc;

	/* Attach TTY and open DLC */

	rfcomm_dlc_lock(dlc);
	tty->driver_data = dev;
	dev->tty = tty;
	rfcomm_dlc_unlock(dlc);
	set_bit(RFCOMM_TTY_ATTACHED, &dev->flags);

	err = rfcomm_dlc_open(dlc, &dev->src, &dev->dst, dev->channel);
	if (err < 0)
		return err;

	/* Wait for DLC to connect */
	add_wait_queue(&dev->wait, &wait);
	while (1) {
		set_current_state(TASK_INTERRUPTIBLE);

		if (dlc->state == BT_CLOSED) {
			err = -dev->err;
			break;
		}

		if (dlc->state == BT_CONNECTED)
			break;

		if (signal_pending(current)) {
			err = -EINTR;
			break;
		}

		schedule();
	}
	set_current_state(TASK_RUNNING);
	remove_wait_queue(&dev->wait, &wait);

	if (err == 0)
		device_move(dev->tty_dev, rfcomm_get_device(dev),
			    DPM_ORDER_DEV_AFTER_PARENT);

	rfcomm_tty_copy_pending(dev);

	rfcomm_dlc_unthrottle(dev->dlc);

	return err;
}