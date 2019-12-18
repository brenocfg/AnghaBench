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
typedef  int /*<<< orphan*/  u8 ;
struct tty_struct {struct hso_serial* driver_data; } ;
struct hso_serial {scalar_t__ open_count; TYPE_1__* parent; int /*<<< orphan*/  retry_unthrottle_workqueue; int /*<<< orphan*/  unthrottle_tasklet; int /*<<< orphan*/  serial_lock; struct tty_struct* tty; } ;
struct file {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  ref; int /*<<< orphan*/  mutex; int /*<<< orphan*/  interface; int /*<<< orphan*/  usb_gone; } ;

/* Variables and functions */
 int /*<<< orphan*/  D1 (char*) ; 
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hso_serial_ref_free ; 
 int /*<<< orphan*/  hso_stop_serial_device (TYPE_1__*) ; 
 int /*<<< orphan*/  kref_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tasklet_kill (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tty_kref_put (struct tty_struct*) ; 
 int /*<<< orphan*/  usb_autopm_get_interface (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_autopm_put_interface (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void hso_serial_close(struct tty_struct *tty, struct file *filp)
{
	struct hso_serial *serial = tty->driver_data;
	u8 usb_gone;

	D1("Closing serial port");

	/* Open failed, no close cleanup required */
	if (serial == NULL)
		return;

	mutex_lock(&serial->parent->mutex);
	usb_gone = serial->parent->usb_gone;

	if (!usb_gone)
		usb_autopm_get_interface(serial->parent->interface);

	/* reset the rts and dtr */
	/* do the actual close */
	serial->open_count--;

	if (serial->open_count <= 0) {
		serial->open_count = 0;
		spin_lock_irq(&serial->serial_lock);
		if (serial->tty == tty) {
			serial->tty->driver_data = NULL;
			serial->tty = NULL;
			tty_kref_put(tty);
		}
		spin_unlock_irq(&serial->serial_lock);
		if (!usb_gone)
			hso_stop_serial_device(serial->parent);
		tasklet_kill(&serial->unthrottle_tasklet);
		cancel_work_sync(&serial->retry_unthrottle_workqueue);
	}

	if (!usb_gone)
		usb_autopm_put_interface(serial->parent->interface);

	mutex_unlock(&serial->parent->mutex);

	kref_put(&serial->parent->ref, hso_serial_ref_free);
}