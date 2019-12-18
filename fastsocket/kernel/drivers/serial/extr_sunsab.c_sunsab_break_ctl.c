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
struct TYPE_2__ {int /*<<< orphan*/  lock; } ;
struct uart_sunsab_port {unsigned char cached_dafo; TYPE_1__ port; int /*<<< orphan*/  irqflags; } ;
struct uart_port {int dummy; } ;

/* Variables and functions */
 unsigned char SAB82532_DAFO_XBRK ; 
 int /*<<< orphan*/  SAB82532_REGS_PENDING ; 
 int /*<<< orphan*/  SAB82532_XPR ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  sunsab_tx_idle (struct uart_sunsab_port*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void sunsab_break_ctl(struct uart_port *port, int break_state)
{
	struct uart_sunsab_port *up = (struct uart_sunsab_port *) port;
	unsigned long flags;
	unsigned char val;

	spin_lock_irqsave(&up->port.lock, flags);

	val = up->cached_dafo;
	if (break_state)
		val |= SAB82532_DAFO_XBRK;
	else
		val &= ~SAB82532_DAFO_XBRK;
	up->cached_dafo = val;

	set_bit(SAB82532_REGS_PENDING, &up->irqflags);
	if (test_bit(SAB82532_XPR, &up->irqflags))
		sunsab_tx_idle(up);

	spin_unlock_irqrestore(&up->port.lock, flags);
}