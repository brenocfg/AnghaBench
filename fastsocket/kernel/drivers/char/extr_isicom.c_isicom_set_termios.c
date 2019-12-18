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
struct tty_struct {scalar_t__ hw_stopped; TYPE_2__* termios; int /*<<< orphan*/  name; struct isi_port* driver_data; } ;
struct ktermios {int c_cflag; scalar_t__ c_iflag; } ;
struct isi_port {TYPE_1__* card; } ;
struct TYPE_4__ {int c_cflag; scalar_t__ c_iflag; } ;
struct TYPE_3__ {int /*<<< orphan*/  card_lock; } ;

/* Variables and functions */
 int CRTSCTS ; 
 int /*<<< orphan*/  isicom_config_port (struct tty_struct*) ; 
 scalar_t__ isicom_paranoia_check (struct isi_port*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  isicom_start (struct tty_struct*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void isicom_set_termios(struct tty_struct *tty,
	struct ktermios *old_termios)
{
	struct isi_port *port = tty->driver_data;
	unsigned long flags;

	if (isicom_paranoia_check(port, tty->name, "isicom_set_termios"))
		return;

	if (tty->termios->c_cflag == old_termios->c_cflag &&
			tty->termios->c_iflag == old_termios->c_iflag)
		return;

	spin_lock_irqsave(&port->card->card_lock, flags);
	isicom_config_port(tty);
	spin_unlock_irqrestore(&port->card->card_lock, flags);

	if ((old_termios->c_cflag & CRTSCTS) &&
			!(tty->termios->c_cflag & CRTSCTS)) {
		tty->hw_stopped = 0;
		isicom_start(tty);
	}
}