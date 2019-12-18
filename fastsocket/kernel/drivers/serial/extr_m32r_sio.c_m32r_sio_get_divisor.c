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
struct uart_port {int dummy; } ;

/* Variables and functions */
 unsigned int uart_get_divisor (struct uart_port*,unsigned int) ; 

__attribute__((used)) static unsigned int m32r_sio_get_divisor(struct uart_port *port,
	unsigned int baud)
{
	return uart_get_divisor(port, baud);
}