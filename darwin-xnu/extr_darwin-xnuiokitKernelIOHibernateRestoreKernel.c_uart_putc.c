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

/* Variables and functions */
 scalar_t__ COM1_PORT_ADDR ; 
 scalar_t__ UART_LSR ; 
 int UART_LSR_THRE ; 
 scalar_t__ UART_THR ; 
 int inb (scalar_t__) ; 
 int /*<<< orphan*/  outb (scalar_t__,char) ; 

__attribute__((used)) static void uart_putc(char c)
{
    while (!(inb(COM1_PORT_ADDR + UART_LSR) & UART_LSR_THRE))
	{}
    outb(COM1_PORT_ADDR + UART_THR, c);
}