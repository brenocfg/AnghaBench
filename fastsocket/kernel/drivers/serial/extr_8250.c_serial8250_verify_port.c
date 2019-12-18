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
struct serial_struct {scalar_t__ irq; int baud_base; scalar_t__ type; } ;

/* Variables and functions */
 scalar_t__ ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 scalar_t__ PORT_CIRRUS ; 
 scalar_t__ PORT_STARTECH ; 
 scalar_t__ PORT_UNKNOWN ; 
 scalar_t__ nr_irqs ; 
 int /*<<< orphan*/  uart_config ; 

__attribute__((used)) static int
serial8250_verify_port(struct uart_port *port, struct serial_struct *ser)
{
	if (ser->irq >= nr_irqs || ser->irq < 0 ||
	    ser->baud_base < 9600 || ser->type < PORT_UNKNOWN ||
	    ser->type >= ARRAY_SIZE(uart_config) || ser->type == PORT_CIRRUS ||
	    ser->type == PORT_STARTECH)
		return -EINVAL;
	return 0;
}