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
 unsigned int CTS ; 
 unsigned int DCD ; 
 unsigned int DSR ; 
 unsigned int TIOCM_CAR ; 
 unsigned int TIOCM_CTS ; 
 unsigned int TIOCM_DSR ; 
 int /*<<< orphan*/  UART_R_STATUS ; 
 unsigned int UR (struct uart_port*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned int lh7a40xuart_get_mctrl (struct uart_port* port)
{
	unsigned int result = 0;
	unsigned int status = UR (port, UART_R_STATUS);

	if (status & DCD)
		result |= TIOCM_CAR;
	if (status & DSR)
		result |= TIOCM_DSR;
	if (status & CTS)
		result |= TIOCM_CTS;

	return result;
}