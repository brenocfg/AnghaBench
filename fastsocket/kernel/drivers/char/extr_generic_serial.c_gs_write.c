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
struct tty_struct {int /*<<< orphan*/  hw_stopped; int /*<<< orphan*/  stopped; struct gs_port* driver_data; } ;
struct TYPE_3__ {int flags; } ;
struct gs_port {int xmit_head; int xmit_cnt; TYPE_2__* rd; TYPE_1__ port; int /*<<< orphan*/  port_write_mutex; scalar_t__ xmit_buf; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* enable_tx_interrupts ) (struct gs_port*) ;} ;

/* Variables and functions */
 int ASYNC_INITIALIZED ; 
 int /*<<< orphan*/  GS_DEBUG_WRITE ; 
 int GS_TX_INTEN ; 
 int SERIAL_XMIT_SIZE ; 
 int /*<<< orphan*/  func_enter () ; 
 int /*<<< orphan*/  func_exit () ; 
 int /*<<< orphan*/  gs_dprintk (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  memcpy (scalar_t__,unsigned char const*,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct gs_port*) ; 

int gs_write(struct tty_struct * tty, 
                    const unsigned char *buf, int count)
{
	struct gs_port *port;
	int c, total = 0;
	int t;

	func_enter ();

	port = tty->driver_data;

	if (!port) return 0;

	if (! (port->port.flags & ASYNC_INITIALIZED))
		return 0;

	/* get exclusive "write" access to this port (problem 3) */
	/* This is not a spinlock because we can have a disk access (page 
		 fault) in copy_from_user */
	mutex_lock(& port->port_write_mutex);

	while (1) {

		c = count;
 
		/* This is safe because we "OWN" the "head". Noone else can 
		   change the "head": we own the port_write_mutex. */
		/* Don't overrun the end of the buffer */
		t = SERIAL_XMIT_SIZE - port->xmit_head;
		if (t < c) c = t;
 
		/* This is safe because the xmit_cnt can only decrease. This 
		   would increase "t", so we might copy too little chars. */
		/* Don't copy past the "head" of the buffer */
		t = SERIAL_XMIT_SIZE - 1 - port->xmit_cnt;
		if (t < c) c = t;
 
		/* Can't copy more? break out! */
		if (c <= 0) break;

		memcpy (port->xmit_buf + port->xmit_head, buf, c);

		port -> xmit_cnt += c;
		port -> xmit_head = (port->xmit_head + c) & (SERIAL_XMIT_SIZE -1);
		buf += c;
		count -= c;
		total += c;
	}
	mutex_unlock(& port->port_write_mutex);

	gs_dprintk (GS_DEBUG_WRITE, "write: interrupts are %s\n", 
	            (port->port.flags & GS_TX_INTEN)?"enabled": "disabled");

	if (port->xmit_cnt && 
	    !tty->stopped && 
	    !tty->hw_stopped &&
	    !(port->port.flags & GS_TX_INTEN)) {
		port->port.flags |= GS_TX_INTEN;
		port->rd->enable_tx_interrupts (port);
	}
	func_exit ();
	return total;
}