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
struct usb_ep {int dummy; } ;
struct list_head {int dummy; } ;
struct gs_port {struct list_head write_pool; TYPE_1__* port_usb; int /*<<< orphan*/  port_tty; scalar_t__ n_read; struct list_head read_pool; } ;
struct TYPE_2__ {struct usb_ep* in; struct usb_ep* out; } ;

/* Variables and functions */
 int EIO ; 
 int gs_alloc_requests (struct usb_ep*,struct list_head*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gs_free_requests (struct usb_ep*,struct list_head*) ; 
 int /*<<< orphan*/  gs_read_complete ; 
 unsigned int gs_start_rx (struct gs_port*) ; 
 int /*<<< orphan*/  gs_write_complete ; 
 int /*<<< orphan*/  tty_wakeup (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int gs_start_io(struct gs_port *port)
{
	struct list_head	*head = &port->read_pool;
	struct usb_ep		*ep = port->port_usb->out;
	int			status;
	unsigned		started;

	/* Allocate RX and TX I/O buffers.  We can't easily do this much
	 * earlier (with GFP_KERNEL) because the requests are coupled to
	 * endpoints, as are the packet sizes we'll be using.  Different
	 * configurations may use different endpoints with a given port;
	 * and high speed vs full speed changes packet sizes too.
	 */
	status = gs_alloc_requests(ep, head, gs_read_complete);
	if (status)
		return status;

	status = gs_alloc_requests(port->port_usb->in, &port->write_pool,
			gs_write_complete);
	if (status) {
		gs_free_requests(ep, head);
		return status;
	}

	/* queue read requests */
	port->n_read = 0;
	started = gs_start_rx(port);

	/* unblock any pending writes into our circular buffer */
	if (started) {
		tty_wakeup(port->port_tty);
	} else {
		gs_free_requests(ep, head);
		gs_free_requests(port->port_usb->in, &port->write_pool);
		status = -EIO;
	}

	return status;
}