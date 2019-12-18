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
struct ipw_tty {unsigned int control_lines; } ;

/* Variables and functions */
 unsigned int IPW_CONTROL_LINE_CTS ; 
 unsigned int IPW_CONTROL_LINE_DCD ; 
 unsigned int IPW_CONTROL_LINE_DSR ; 
 unsigned int IPW_CONTROL_LINE_DTR ; 
 unsigned int IPW_CONTROL_LINE_RTS ; 
 unsigned int TIOCM_CD ; 
 unsigned int TIOCM_CTS ; 
 unsigned int TIOCM_DSR ; 
 unsigned int TIOCM_DTR ; 
 unsigned int TIOCM_RTS ; 

__attribute__((used)) static int get_control_lines(struct ipw_tty *tty)
{
	unsigned int my = tty->control_lines;
	unsigned int out = 0;

	if (my & IPW_CONTROL_LINE_RTS)
		out |= TIOCM_RTS;
	if (my & IPW_CONTROL_LINE_DTR)
		out |= TIOCM_DTR;
	if (my & IPW_CONTROL_LINE_CTS)
		out |= TIOCM_CTS;
	if (my & IPW_CONTROL_LINE_DSR)
		out |= TIOCM_DSR;
	if (my & IPW_CONTROL_LINE_DCD)
		out |= TIOCM_CD;

	return out;
}