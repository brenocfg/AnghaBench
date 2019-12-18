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
struct uart_sunsab_port {TYPE_2__* regs; int /*<<< orphan*/  interrupt_mask1; } ;
struct uart_port {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  imr1; } ;
struct TYPE_4__ {TYPE_1__ w; } ;

/* Variables and functions */
 int /*<<< orphan*/  SAB82532_IMR1_XPR ; 
 int /*<<< orphan*/  writeb (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void sunsab_stop_tx(struct uart_port *port)
{
	struct uart_sunsab_port *up = (struct uart_sunsab_port *) port;

	up->interrupt_mask1 |= SAB82532_IMR1_XPR;
	writeb(up->interrupt_mask1, &up->regs->w.imr1);
}