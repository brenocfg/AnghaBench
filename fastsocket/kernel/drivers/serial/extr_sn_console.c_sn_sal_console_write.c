#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  lock; TYPE_2__* state; } ;
struct sn_cons_port {TYPE_4__* sc_ops; TYPE_3__ sc_port; int /*<<< orphan*/  sc_is_asynch; } ;
struct console {int dummy; } ;
struct TYPE_8__ {int /*<<< orphan*/  sal_puts_raw; } ;
struct TYPE_5__ {int head; int tail; } ;
struct TYPE_6__ {TYPE_1__ xmit; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int /*<<< orphan*/  puts_raw_fixed (int /*<<< orphan*/ ,char const*,unsigned int) ; 
 struct sn_cons_port sal_console_port ; 
 int /*<<< orphan*/  sn_transmit_chars (struct sn_cons_port*,int) ; 
 scalar_t__ spin_is_locked (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void
sn_sal_console_write(struct console *co, const char *s, unsigned count)
{
	unsigned long flags = 0;
	struct sn_cons_port *port = &sal_console_port;
	static int stole_lock = 0;

	BUG_ON(!port->sc_is_asynch);

	/* We can't look at the xmit buffer if we're not registered with serial core
	 *  yet.  So only do the fancy recovery after registering
	 */
	if (!port->sc_port.state) {
		/* Not yet registered with serial core - simple case */
		puts_raw_fixed(port->sc_ops->sal_puts_raw, s, count);
		return;
	}

	/* somebody really wants this output, might be an
	 * oops, kdb, panic, etc.  make sure they get it. */
	if (spin_is_locked(&port->sc_port.lock)) {
		int lhead = port->sc_port.state->xmit.head;
		int ltail = port->sc_port.state->xmit.tail;
		int counter, got_lock = 0;

		/*
		 * We attempt to determine if someone has died with the
		 * lock. We wait ~20 secs after the head and tail ptrs
		 * stop moving and assume the lock holder is not functional
		 * and plow ahead. If the lock is freed within the time out
		 * period we re-get the lock and go ahead normally. We also
		 * remember if we have plowed ahead so that we don't have
		 * to wait out the time out period again - the asumption
		 * is that we will time out again.
		 */

		for (counter = 0; counter < 150; mdelay(125), counter++) {
			if (!spin_is_locked(&port->sc_port.lock)
			    || stole_lock) {
				if (!stole_lock) {
					spin_lock_irqsave(&port->sc_port.lock,
							  flags);
					got_lock = 1;
				}
				break;
			} else {
				/* still locked */
				if ((lhead != port->sc_port.state->xmit.head)
				    || (ltail !=
					port->sc_port.state->xmit.tail)) {
					lhead =
						port->sc_port.state->xmit.head;
					ltail =
						port->sc_port.state->xmit.tail;
					counter = 0;
				}
			}
		}
		/* flush anything in the serial core xmit buffer, raw */
		sn_transmit_chars(port, 1);
		if (got_lock) {
			spin_unlock_irqrestore(&port->sc_port.lock, flags);
			stole_lock = 0;
		} else {
			/* fell thru */
			stole_lock = 1;
		}
		puts_raw_fixed(port->sc_ops->sal_puts_raw, s, count);
	} else {
		stole_lock = 0;
		spin_lock_irqsave(&port->sc_port.lock, flags);
		sn_transmit_chars(port, 1);
		spin_unlock_irqrestore(&port->sc_port.lock, flags);

		puts_raw_fixed(port->sc_ops->sal_puts_raw, s, count);
	}
}