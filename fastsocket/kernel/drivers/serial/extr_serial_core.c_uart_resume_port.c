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
struct tty_port {int flags; int /*<<< orphan*/  mutex; TYPE_1__* tty; } ;
struct uart_state {struct tty_port port; } ;
struct uart_port {int line; int /*<<< orphan*/  lock; int /*<<< orphan*/  mctrl; struct uart_ops* ops; TYPE_2__* cons; scalar_t__ suspended; int /*<<< orphan*/  irq; int /*<<< orphan*/  dev; } ;
struct uart_ops {int (* startup ) (struct uart_port*) ;int /*<<< orphan*/  (* start_tx ) (struct uart_port*) ;int /*<<< orphan*/  (* set_mctrl ) (struct uart_port*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* set_termios ) (struct uart_port*,struct ktermios*,int /*<<< orphan*/ *) ;} ;
struct uart_match {struct uart_driver* member_1; struct uart_port* member_0; } ;
struct uart_driver {struct uart_state* state; } ;
struct ktermios {scalar_t__ c_cflag; int /*<<< orphan*/  c_ospeed; int /*<<< orphan*/  c_ispeed; } ;
struct device {int dummy; } ;
struct TYPE_4__ {scalar_t__ cflag; } ;
struct TYPE_3__ {struct ktermios* termios; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASYNCB_INITIALIZED ; 
 int /*<<< orphan*/  ASYNCB_SUSPENDED ; 
 int ASYNC_SUSPENDED ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  console_start (TYPE_2__*) ; 
 int /*<<< orphan*/  console_suspend_enabled ; 
 struct device* device_find_child (int /*<<< orphan*/ ,struct uart_match*,int /*<<< orphan*/ ) ; 
 scalar_t__ device_may_wakeup (struct device*) ; 
 int /*<<< orphan*/  disable_irq_wake (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct ktermios*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  serial_match_port ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct uart_port*,struct ktermios*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub2 (struct uart_port*,struct ktermios*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub3 (struct uart_port*,int /*<<< orphan*/ ) ; 
 int stub4 (struct uart_port*) ; 
 int /*<<< orphan*/  stub5 (struct uart_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub6 (struct uart_port*) ; 
 int /*<<< orphan*/  tty_termios_baud_rate (struct ktermios*) ; 
 int /*<<< orphan*/  tty_termios_input_baud_rate (struct ktermios*) ; 
 int /*<<< orphan*/  uart_change_pm (struct uart_state*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uart_change_speed (struct uart_state*,int /*<<< orphan*/ *) ; 
 scalar_t__ uart_console (struct uart_port*) ; 
 int /*<<< orphan*/  uart_shutdown (struct uart_state*) ; 

int uart_resume_port(struct uart_driver *drv, struct uart_port *uport)
{
	struct uart_state *state = drv->state + uport->line;
	struct tty_port *port = &state->port;
	struct device *tty_dev;
	struct uart_match match = {uport, drv};
	struct ktermios termios;

	mutex_lock(&port->mutex);

	if (!console_suspend_enabled && uart_console(uport)) {
		/* no need to resume serial console, it wasn't suspended */
		/*
		 * First try to use the console cflag setting.
		 */
		memset(&termios, 0, sizeof(struct ktermios));
		termios.c_cflag = uport->cons->cflag;
		/*
		 * If that's unset, use the tty termios setting.
		 */
		if (termios.c_cflag == 0)
			termios = *state->port.tty->termios;
		else {
			termios.c_ispeed = termios.c_ospeed =
				tty_termios_input_baud_rate(&termios);
			termios.c_ispeed = termios.c_ospeed =
				tty_termios_baud_rate(&termios);
		}
		uport->ops->set_termios(uport, &termios, NULL);
		mutex_unlock(&port->mutex);
		return 0;
	}

	tty_dev = device_find_child(uport->dev, &match, serial_match_port);
	if (!uport->suspended && device_may_wakeup(tty_dev)) {
		disable_irq_wake(uport->irq);
		mutex_unlock(&port->mutex);
		return 0;
	}
	uport->suspended = 0;

	/*
	 * Re-enable the console device after suspending.
	 */
	if (uart_console(uport)) {
		uart_change_pm(state, 0);
		uport->ops->set_termios(uport, &termios, NULL);
		console_start(uport->cons);
	}

	if (port->flags & ASYNC_SUSPENDED) {
		const struct uart_ops *ops = uport->ops;
		int ret;

		uart_change_pm(state, 0);
		spin_lock_irq(&uport->lock);
		ops->set_mctrl(uport, 0);
		spin_unlock_irq(&uport->lock);
		ret = ops->startup(uport);
		if (ret == 0) {
			uart_change_speed(state, NULL);
			spin_lock_irq(&uport->lock);
			ops->set_mctrl(uport, uport->mctrl);
			ops->start_tx(uport);
			spin_unlock_irq(&uport->lock);
			set_bit(ASYNCB_INITIALIZED, &port->flags);
		} else {
			/*
			 * Failed to resume - maybe hardware went away?
			 * Clear the "initialized" flag so we won't try
			 * to call the low level drivers shutdown method.
			 */
			uart_shutdown(state);
		}

		clear_bit(ASYNCB_SUSPENDED, &port->flags);
	}

	mutex_unlock(&port->mutex);

	return 0;
}