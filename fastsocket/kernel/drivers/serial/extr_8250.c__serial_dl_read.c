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
struct uart_8250_port {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  UART_DLL ; 
 int /*<<< orphan*/  UART_DLM ; 
 int serial_inp (struct uart_8250_port*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int _serial_dl_read(struct uart_8250_port *up)
{
	return serial_inp(up, UART_DLL) | serial_inp(up, UART_DLM) << 8;
}