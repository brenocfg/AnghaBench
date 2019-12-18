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
typedef  int /*<<< orphan*/  phys_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  LOONGSON_UART_BASE ; 
 int /*<<< orphan*/  UART_LSR ; 
 int UART_LSR_THRE ; 
 int /*<<< orphan*/  UART_TX ; 
 int /*<<< orphan*/  ioremap_nocache (int /*<<< orphan*/ ,int) ; 
 int serial_in (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  serial_out (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char) ; 

void prom_putchar(char c)
{
	phys_addr_t uart_base =
		(phys_addr_t) ioremap_nocache(LOONGSON_UART_BASE, 8);

	while ((serial_in(uart_base, UART_LSR) & UART_LSR_THRE) == 0)
		;

	serial_out(uart_base, UART_TX, c);
}