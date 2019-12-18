#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct tty_struct {int /*<<< orphan*/ * driver_data; } ;
struct rfcomm_dev {int /*<<< orphan*/  list; int /*<<< orphan*/  flags; int /*<<< orphan*/  dlc; int /*<<< orphan*/ * tty; int /*<<< orphan*/  wakeup_task; TYPE_1__* tty_dev; int /*<<< orphan*/  opened; } ;
struct file {int dummy; } ;
struct TYPE_2__ {scalar_t__ parent; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*,struct tty_struct*,struct rfcomm_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DPM_ORDER_DEV_LAST ; 
 int /*<<< orphan*/  RFCOMM_TTY_ATTACHED ; 
 int /*<<< orphan*/  RFCOMM_TTY_RELEASED ; 
 scalar_t__ atomic_dec_and_test (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_move (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rfcomm_dev_lock ; 
 int /*<<< orphan*/  rfcomm_dev_put (struct rfcomm_dev*) ; 
 int /*<<< orphan*/  rfcomm_dlc_close (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rfcomm_dlc_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rfcomm_dlc_unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tasklet_kill (int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void rfcomm_tty_close(struct tty_struct *tty, struct file *filp)
{
	struct rfcomm_dev *dev = (struct rfcomm_dev *) tty->driver_data;
	if (!dev)
		return;

	BT_DBG("tty %p dev %p dlc %p opened %d", tty, dev, dev->dlc,
						atomic_read(&dev->opened));

	if (atomic_dec_and_test(&dev->opened)) {
		if (dev->tty_dev->parent)
			device_move(dev->tty_dev, NULL, DPM_ORDER_DEV_LAST);

		/* Close DLC and dettach TTY */
		rfcomm_dlc_close(dev->dlc, 0);

		clear_bit(RFCOMM_TTY_ATTACHED, &dev->flags);
		tasklet_kill(&dev->wakeup_task);

		rfcomm_dlc_lock(dev->dlc);
		tty->driver_data = NULL;
		dev->tty = NULL;
		rfcomm_dlc_unlock(dev->dlc);

		if (test_bit(RFCOMM_TTY_RELEASED, &dev->flags)) {
			write_lock_bh(&rfcomm_dev_lock);
			list_del_init(&dev->list);
			write_unlock_bh(&rfcomm_dev_lock);

			rfcomm_dev_put(dev);
		}
	}

	rfcomm_dev_put(dev);
}