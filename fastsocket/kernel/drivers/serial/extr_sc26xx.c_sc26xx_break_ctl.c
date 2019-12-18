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
 int /*<<< orphan*/  CR ; 
 int /*<<< orphan*/  CR_STOP_BRK ; 
 int /*<<< orphan*/  CR_STRT_BRK ; 
 int /*<<< orphan*/  WRITE_SC_PORT (struct uart_port*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sc26xx_break_ctl(struct uart_port *port, int break_state)
{
	if (break_state == -1)
		WRITE_SC_PORT(port, CR, CR_STRT_BRK);
	else
		WRITE_SC_PORT(port, CR, CR_STOP_BRK);
}