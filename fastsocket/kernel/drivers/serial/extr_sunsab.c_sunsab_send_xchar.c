#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  lock; } ;
struct uart_sunsab_port {TYPE_3__ port; TYPE_2__* regs; } ;
struct uart_port {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  tic; } ;
struct TYPE_5__ {TYPE_1__ w; } ;

/* Variables and functions */
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  sunsab_tec_wait (struct uart_sunsab_port*) ; 
 int /*<<< orphan*/  writeb (char,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void sunsab_send_xchar(struct uart_port *port, char ch)
{
	struct uart_sunsab_port *up = (struct uart_sunsab_port *) port;
	unsigned long flags;

	spin_lock_irqsave(&up->port.lock, flags);

	sunsab_tec_wait(up);
	writeb(ch, &up->regs->w.tic);

	spin_unlock_irqrestore(&up->port.lock, flags);
}