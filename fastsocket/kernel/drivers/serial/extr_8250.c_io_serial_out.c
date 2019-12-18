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
struct uart_port {int regshift; scalar_t__ iobase; } ;

/* Variables and functions */
 int map_8250_out_reg (struct uart_port*,int) ; 
 int /*<<< orphan*/  outb (int,scalar_t__) ; 

__attribute__((used)) static void io_serial_out(struct uart_port *p, int offset, int value)
{
	offset = map_8250_out_reg(p, offset) << p->regshift;
	outb(value, p->iobase + offset);
}