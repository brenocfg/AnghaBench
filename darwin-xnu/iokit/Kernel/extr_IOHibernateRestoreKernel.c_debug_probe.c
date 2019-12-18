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
 scalar_t__ UART_SCR ; 
 int inb (scalar_t__) ; 
 int /*<<< orphan*/  outb (scalar_t__,int) ; 
 int /*<<< orphan*/  uart_putc (char) ; 

__attribute__((used)) static int debug_probe( void )
{
    /* Verify that the Scratch Register is accessible */
    outb(COM1_PORT_ADDR + UART_SCR, 0x5a);
    if (inb(COM1_PORT_ADDR + UART_SCR) != 0x5a) return false;
    outb(COM1_PORT_ADDR + UART_SCR, 0xa5);
    if (inb(COM1_PORT_ADDR + UART_SCR) != 0xa5) return false;
    uart_putc('\n');
    return true;
}