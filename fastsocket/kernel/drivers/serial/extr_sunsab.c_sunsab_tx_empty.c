#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct uart_sunsab_port {int /*<<< orphan*/  irqflags; } ;
struct uart_port {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SAB82532_ALLS ; 
 int TIOCSER_TEMT ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static unsigned int sunsab_tx_empty(struct uart_port *port)
{
	struct uart_sunsab_port *up = (struct uart_sunsab_port *) port;
	int ret;

	/* Do not need a lock for a state test like this.  */
	if (test_bit(SAB82532_ALLS, &up->irqflags))
		ret = TIOCSER_TEMT;
	else
		ret = 0;

	return ret;
}