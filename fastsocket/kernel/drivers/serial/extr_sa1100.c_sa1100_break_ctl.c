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
struct uart_port {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  lock; } ;
struct sa1100_port {TYPE_1__ port; } ;

/* Variables and functions */
 unsigned int UART_GET_UTCR3 (struct sa1100_port*) ; 
 int /*<<< orphan*/  UART_PUT_UTCR3 (struct sa1100_port*,unsigned int) ; 
 unsigned int UTCR3_BRK ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void sa1100_break_ctl(struct uart_port *port, int break_state)
{
	struct sa1100_port *sport = (struct sa1100_port *)port;
	unsigned long flags;
	unsigned int utcr3;

	spin_lock_irqsave(&sport->port.lock, flags);
	utcr3 = UART_GET_UTCR3(sport);
	if (break_state == -1)
		utcr3 |= UTCR3_BRK;
	else
		utcr3 &= ~UTCR3_BRK;
	UART_PUT_UTCR3(sport, utcr3);
	spin_unlock_irqrestore(&sport->port.lock, flags);
}