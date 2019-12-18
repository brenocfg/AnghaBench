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
struct uart_port {TYPE_2__* state; } ;
struct tty_struct {int dummy; } ;
struct TYPE_6__ {scalar_t__ (* receive_chars ) (struct uart_port*,struct tty_struct*) ;} ;
struct TYPE_4__ {struct tty_struct* tty; } ;
struct TYPE_5__ {TYPE_1__ port; } ;

/* Variables and functions */
 scalar_t__ stub1 (struct uart_port*,struct tty_struct*) ; 
 int /*<<< orphan*/  sun_do_break () ; 
 TYPE_3__* sunhv_ops ; 

__attribute__((used)) static struct tty_struct *receive_chars(struct uart_port *port)
{
	struct tty_struct *tty = NULL;

	if (port->state != NULL)		/* Unopened serial console */
		tty = port->state->port.tty;

	if (sunhv_ops->receive_chars(port, tty))
		sun_do_break();

	return tty;
}