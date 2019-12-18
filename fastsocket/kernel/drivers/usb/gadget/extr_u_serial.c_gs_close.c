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
struct tty_struct {struct gs_port* driver_data; } ;
struct gserial {int /*<<< orphan*/  (* disconnect ) (struct gserial*) ;} ;
struct gs_port {int open_count; int openclose; int /*<<< orphan*/  port_lock; int /*<<< orphan*/  close_wait; int /*<<< orphan*/  port_num; int /*<<< orphan*/ * port_tty; int /*<<< orphan*/  port_write_buf; struct gserial* port_usb; int /*<<< orphan*/  drain_wait; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int GS_CLOSE_TIMEOUT ; 
 int HZ ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  gs_buf_clear (int /*<<< orphan*/ *) ; 
 scalar_t__ gs_buf_data_avail (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gs_buf_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gs_writes_finished (struct gs_port*) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,struct tty_struct*,struct file*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct gserial*) ; 
 int /*<<< orphan*/  wait_event_interruptible_timeout (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void gs_close(struct tty_struct *tty, struct file *file)
{
	struct gs_port *port = tty->driver_data;
	struct gserial	*gser;

	spin_lock_irq(&port->port_lock);

	if (port->open_count != 1) {
		if (port->open_count == 0)
			WARN_ON(1);
		else
			--port->open_count;
		goto exit;
	}

	pr_debug("gs_close: ttyGS%d (%p,%p) ...\n", port->port_num, tty, file);

	/* mark port as closing but in use; we can drop port lock
	 * and sleep if necessary
	 */
	port->openclose = true;
	port->open_count = 0;

	gser = port->port_usb;
	if (gser && gser->disconnect)
		gser->disconnect(gser);

	/* wait for circular write buffer to drain, disconnect, or at
	 * most GS_CLOSE_TIMEOUT seconds; then discard the rest
	 */
	if (gs_buf_data_avail(&port->port_write_buf) > 0 && gser) {
		spin_unlock_irq(&port->port_lock);
		wait_event_interruptible_timeout(port->drain_wait,
					gs_writes_finished(port),
					GS_CLOSE_TIMEOUT * HZ);
		spin_lock_irq(&port->port_lock);
		gser = port->port_usb;
	}

	/* Iff we're disconnected, there can be no I/O in flight so it's
	 * ok to free the circular buffer; else just scrub it.  And don't
	 * let the push tasklet fire again until we're re-opened.
	 */
	if (gser == NULL)
		gs_buf_free(&port->port_write_buf);
	else
		gs_buf_clear(&port->port_write_buf);

	tty->driver_data = NULL;
	port->port_tty = NULL;

	port->openclose = false;

	pr_debug("gs_close: ttyGS%d (%p,%p) done!\n",
			port->port_num, tty, file);

	wake_up_interruptible(&port->close_wait);
exit:
	spin_unlock_irq(&port->port_lock);
}