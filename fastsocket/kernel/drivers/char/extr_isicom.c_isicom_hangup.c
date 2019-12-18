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
struct tty_struct {int /*<<< orphan*/  name; struct isi_port* driver_data; } ;
struct isi_port {int /*<<< orphan*/  port; TYPE_1__* card; } ;
struct TYPE_2__ {int /*<<< orphan*/  card_lock; } ;

/* Variables and functions */
 scalar_t__ isicom_paranoia_check (struct isi_port*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  isicom_shutdown_port (struct isi_port*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  tty_port_hangup (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void isicom_hangup(struct tty_struct *tty)
{
	struct isi_port *port = tty->driver_data;
	unsigned long flags;

	if (isicom_paranoia_check(port, tty->name, "isicom_hangup"))
		return;

	spin_lock_irqsave(&port->card->card_lock, flags);
	isicom_shutdown_port(port);
	spin_unlock_irqrestore(&port->card->card_lock, flags);

	tty_port_hangup(&port->port);
}