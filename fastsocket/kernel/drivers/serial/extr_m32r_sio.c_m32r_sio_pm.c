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
struct uart_sio_port {int /*<<< orphan*/  (* pm ) (struct uart_port*,unsigned int,unsigned int) ;} ;
struct uart_port {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct uart_port*,unsigned int,unsigned int) ; 

__attribute__((used)) static void m32r_sio_pm(struct uart_port *port, unsigned int state,
	unsigned int oldstate)
{
	struct uart_sio_port *up = (struct uart_sio_port *)port;

	if (up->pm)
		up->pm(port, state, oldstate);
}