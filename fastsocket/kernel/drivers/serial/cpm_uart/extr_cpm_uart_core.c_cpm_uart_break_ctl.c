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
struct uart_port {int /*<<< orphan*/  line; } ;
struct uart_cpm_port {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPM_CR_RESTART_TX ; 
 int /*<<< orphan*/  CPM_CR_STOP_TX ; 
 int /*<<< orphan*/  cpm_line_cr_cmd (struct uart_cpm_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void cpm_uart_break_ctl(struct uart_port *port, int break_state)
{
	struct uart_cpm_port *pinfo = (struct uart_cpm_port *)port;

	pr_debug("CPM uart[%d]:break ctrl, break_state: %d\n", port->line,
		break_state);

	if (break_state)
		cpm_line_cr_cmd(pinfo, CPM_CR_STOP_TX);
	else
		cpm_line_cr_cmd(pinfo, CPM_CR_RESTART_TX);
}