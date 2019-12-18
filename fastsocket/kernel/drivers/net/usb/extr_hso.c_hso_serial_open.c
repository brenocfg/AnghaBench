#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct tty_struct {int low_latency; struct hso_serial* driver_data; int /*<<< orphan*/  index; } ;
struct hso_serial {scalar_t__ magic; int open_count; TYPE_1__* parent; int /*<<< orphan*/  retry_unthrottle_workqueue; int /*<<< orphan*/  unthrottle_tasklet; int /*<<< orphan*/  rx_state; int /*<<< orphan*/  serial_lock; int /*<<< orphan*/  tty; int /*<<< orphan*/  minor; } ;
struct file {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  mutex; int /*<<< orphan*/  interface; int /*<<< orphan*/  ref; } ;

/* Variables and functions */
 int /*<<< orphan*/  D1 (char*,...) ; 
 int ENODEV ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ HSO_SERIAL_MAGIC ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RX_IDLE ; 
 int TIOCM_DTR ; 
 int TIOCM_RTS ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  _hso_serial_set_termios (struct tty_struct*,int /*<<< orphan*/ *) ; 
 struct hso_serial* get_serial_by_index (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hso_serial_ref_free ; 
 int /*<<< orphan*/  hso_serial_tiocmset (struct tty_struct*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int hso_start_serial_device (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hso_stop_serial_device (TYPE_1__*) ; 
 scalar_t__ hso_unthrottle_tasklet ; 
 int /*<<< orphan*/  hso_unthrottle_workfunc ; 
 int /*<<< orphan*/  kref_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kref_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tasklet_init (int /*<<< orphan*/ *,void (*) (unsigned long),unsigned long) ; 
 int /*<<< orphan*/  tty_kref_get (struct tty_struct*) ; 
 int /*<<< orphan*/  tty_kref_put (int /*<<< orphan*/ ) ; 
 int usb_autopm_get_interface (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_autopm_put_interface (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hso_serial_open(struct tty_struct *tty, struct file *filp)
{
	struct hso_serial *serial = get_serial_by_index(tty->index);
	int result;

	/* sanity check */
	if (serial == NULL || serial->magic != HSO_SERIAL_MAGIC) {
		WARN_ON(1);
		tty->driver_data = NULL;
		D1("Failed to open port");
		return -ENODEV;
	}

	mutex_lock(&serial->parent->mutex);
	result = usb_autopm_get_interface(serial->parent->interface);
	if (result < 0)
		goto err_out;

	D1("Opening %d", serial->minor);
	kref_get(&serial->parent->ref);

	/* setup */
	spin_lock_irq(&serial->serial_lock);
	tty->driver_data = serial;
	tty_kref_put(serial->tty);
	serial->tty = tty_kref_get(tty);
	spin_unlock_irq(&serial->serial_lock);

	/* check for port already opened, if not set the termios */
	serial->open_count++;
	if (serial->open_count == 1) {
		tty->low_latency = 1;
		serial->rx_state = RX_IDLE;
		/* Force default termio settings */
		_hso_serial_set_termios(tty, NULL);
		tasklet_init(&serial->unthrottle_tasklet,
			     (void (*)(unsigned long))hso_unthrottle_tasklet,
			     (unsigned long)serial);
		INIT_WORK(&serial->retry_unthrottle_workqueue,
			  hso_unthrottle_workfunc);
		result = hso_start_serial_device(serial->parent, GFP_KERNEL);
		if (result) {
			hso_stop_serial_device(serial->parent);
			serial->open_count--;
			kref_put(&serial->parent->ref, hso_serial_ref_free);
		}
	} else {
		D1("Port was already open");
	}

	usb_autopm_put_interface(serial->parent->interface);

	/* done */
	if (result)
		hso_serial_tiocmset(tty, NULL, TIOCM_RTS | TIOCM_DTR, 0);
err_out:
	mutex_unlock(&serial->parent->mutex);
	return result;
}