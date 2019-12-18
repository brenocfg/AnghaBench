#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct uart_port {int /*<<< orphan*/  lock; TYPE_3__* state; } ;
struct ktermios {char* c_cc; } ;
struct jsm_channel {TYPE_5__* ch_bd; } ;
struct TYPE_10__ {TYPE_4__* bd_ops; } ;
struct TYPE_9__ {int /*<<< orphan*/  (* send_stop_character ) (struct jsm_channel*) ;int /*<<< orphan*/  (* send_start_character ) (struct jsm_channel*) ;} ;
struct TYPE_7__ {TYPE_1__* tty; } ;
struct TYPE_8__ {TYPE_2__ port; } ;
struct TYPE_6__ {struct ktermios* termios; } ;

/* Variables and functions */
 size_t VSTART ; 
 size_t VSTOP ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stub1 (struct jsm_channel*) ; 
 int /*<<< orphan*/  stub2 (struct jsm_channel*) ; 

__attribute__((used)) static void jsm_tty_send_xchar(struct uart_port *port, char ch)
{
	unsigned long lock_flags;
	struct jsm_channel *channel = (struct jsm_channel *)port;
	struct ktermios *termios;

	spin_lock_irqsave(&port->lock, lock_flags);
	termios = port->state->port.tty->termios;
	if (ch == termios->c_cc[VSTART])
		channel->ch_bd->bd_ops->send_start_character(channel);

	if (ch == termios->c_cc[VSTOP])
		channel->ch_bd->bd_ops->send_stop_character(channel);
	spin_unlock_irqrestore(&port->lock, lock_flags);
}