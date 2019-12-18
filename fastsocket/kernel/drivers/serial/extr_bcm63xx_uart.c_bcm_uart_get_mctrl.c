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
 unsigned int TIOCM_CD ; 
 unsigned int TIOCM_CTS ; 
 unsigned int TIOCM_DSR ; 
 unsigned int TIOCM_RI ; 
 unsigned int UART_EXTINP_CTS_MASK ; 
 unsigned int UART_EXTINP_DCD_MASK ; 
 unsigned int UART_EXTINP_DSR_MASK ; 
 int /*<<< orphan*/  UART_EXTINP_REG ; 
 unsigned int UART_EXTINP_RI_MASK ; 
 unsigned int bcm_uart_readl (struct uart_port*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned int bcm_uart_get_mctrl(struct uart_port *port)
{
	unsigned int val, mctrl;

	mctrl = 0;
	val = bcm_uart_readl(port, UART_EXTINP_REG);
	if (val & UART_EXTINP_RI_MASK)
		mctrl |= TIOCM_RI;
	if (val & UART_EXTINP_CTS_MASK)
		mctrl |= TIOCM_CTS;
	if (val & UART_EXTINP_DCD_MASK)
		mctrl |= TIOCM_CD;
	if (val & UART_EXTINP_DSR_MASK)
		mctrl |= TIOCM_DSR;
	return mctrl;
}