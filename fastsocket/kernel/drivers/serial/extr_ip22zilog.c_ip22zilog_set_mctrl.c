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
struct zilog_channel {int dummy; } ;
struct uart_port {int dummy; } ;
struct uart_ip22zilog_port {unsigned char* curregs; } ;

/* Variables and functions */
 unsigned char DTR ; 
 size_t R5 ; 
 unsigned char RTS ; 
 unsigned int TIOCM_DTR ; 
 unsigned int TIOCM_RTS ; 
 struct zilog_channel* ZILOG_CHANNEL_FROM_PORT (struct uart_port*) ; 
 int /*<<< orphan*/  write_zsreg (struct zilog_channel*,size_t,unsigned char) ; 

__attribute__((used)) static void ip22zilog_set_mctrl(struct uart_port *port, unsigned int mctrl)
{
	struct uart_ip22zilog_port *up = (struct uart_ip22zilog_port *) port;
	struct zilog_channel *channel = ZILOG_CHANNEL_FROM_PORT(port);
	unsigned char set_bits, clear_bits;

	set_bits = clear_bits = 0;

	if (mctrl & TIOCM_RTS)
		set_bits |= RTS;
	else
		clear_bits |= RTS;
	if (mctrl & TIOCM_DTR)
		set_bits |= DTR;
	else
		clear_bits |= DTR;

	/* NOTE: Not subject to 'transmitter active' rule.  */
	up->curregs[R5] |= set_bits;
	up->curregs[R5] &= ~clear_bits;
	write_zsreg(channel, R5, up->curregs[R5]);
}