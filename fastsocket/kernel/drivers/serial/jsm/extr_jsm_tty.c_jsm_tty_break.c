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
struct jsm_channel {TYPE_2__* ch_bd; } ;
struct TYPE_4__ {TYPE_1__* bd_ops; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* clear_break ) (struct jsm_channel*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* send_break ) (struct jsm_channel*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stub1 (struct jsm_channel*) ; 
 int /*<<< orphan*/  stub2 (struct jsm_channel*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void jsm_tty_break(struct uart_port *port, int break_state)
{
	unsigned long lock_flags;
	struct jsm_channel *channel = (struct jsm_channel *)port;

	spin_lock_irqsave(&port->lock, lock_flags);
	if (break_state == -1)
		channel->ch_bd->bd_ops->send_break(channel);
	else
		channel->ch_bd->bd_ops->clear_break(channel, 0);

	spin_unlock_irqrestore(&port->lock, lock_flags);
}