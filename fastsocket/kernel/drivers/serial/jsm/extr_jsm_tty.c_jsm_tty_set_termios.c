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
struct uart_port {int /*<<< orphan*/  lock; } ;
struct ktermios {int /*<<< orphan*/ * c_cc; int /*<<< orphan*/  c_lflag; int /*<<< orphan*/  c_oflag; int /*<<< orphan*/  c_iflag; int /*<<< orphan*/  c_cflag; } ;
struct jsm_channel {TYPE_2__* ch_bd; int /*<<< orphan*/  ch_stopc; int /*<<< orphan*/  ch_startc; int /*<<< orphan*/  ch_c_lflag; int /*<<< orphan*/  ch_c_oflag; int /*<<< orphan*/  ch_c_iflag; int /*<<< orphan*/  ch_c_cflag; } ;
struct TYPE_4__ {TYPE_1__* bd_ops; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* param ) (struct jsm_channel*) ;} ;

/* Variables and functions */
 size_t VSTART ; 
 size_t VSTOP ; 
 int /*<<< orphan*/  jsm_carrier (struct jsm_channel*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stub1 (struct jsm_channel*) ; 

__attribute__((used)) static void jsm_tty_set_termios(struct uart_port *port,
				 struct ktermios *termios,
				 struct ktermios *old_termios)
{
	unsigned long lock_flags;
	struct jsm_channel *channel = (struct jsm_channel *)port;

	spin_lock_irqsave(&port->lock, lock_flags);
	channel->ch_c_cflag	= termios->c_cflag;
	channel->ch_c_iflag	= termios->c_iflag;
	channel->ch_c_oflag	= termios->c_oflag;
	channel->ch_c_lflag	= termios->c_lflag;
	channel->ch_startc	= termios->c_cc[VSTART];
	channel->ch_stopc	= termios->c_cc[VSTOP];

	channel->ch_bd->bd_ops->param(channel);
	jsm_carrier(channel);
	spin_unlock_irqrestore(&port->lock, lock_flags);
}