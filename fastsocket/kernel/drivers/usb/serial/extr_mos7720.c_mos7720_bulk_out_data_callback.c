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
struct urb {int status; struct moschip_port* context; } ;
struct tty_struct {int dummy; } ;
struct moschip_port {scalar_t__ open; TYPE_1__* port; } ;
struct TYPE_2__ {int /*<<< orphan*/  port; } ;

/* Variables and functions */
 int /*<<< orphan*/  dbg (char*,...) ; 
 int /*<<< orphan*/  tty_kref_put (struct tty_struct*) ; 
 struct tty_struct* tty_port_tty_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tty_wakeup (struct tty_struct*) ; 

__attribute__((used)) static void mos7720_bulk_out_data_callback(struct urb *urb)
{
	struct moschip_port *mos7720_port;
	struct tty_struct *tty;
	int status = urb->status;

	if (status) {
		dbg("nonzero write bulk status received:%d", status);
		return;
	}

	mos7720_port = urb->context;
	if (!mos7720_port) {
		dbg("NULL mos7720_port pointer");
		return ;
	}

	dbg("Entering .........");

	tty = tty_port_tty_get(&mos7720_port->port->port);

	if (tty && mos7720_port->open)
		tty_wakeup(tty);
	tty_kref_put(tty);
}