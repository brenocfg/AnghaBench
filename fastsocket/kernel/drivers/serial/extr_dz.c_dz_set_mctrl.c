#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u16 ;
struct uart_port {int dummy; } ;
struct TYPE_2__ {scalar_t__ line; } ;
struct dz_port {TYPE_1__ port; } ;

/* Variables and functions */
 scalar_t__ DZ_MODEM ; 
 int /*<<< orphan*/  DZ_MODEM_DTR ; 
 int /*<<< orphan*/  DZ_TCR ; 
 unsigned int TIOCM_DTR ; 
 int /*<<< orphan*/  dz_in (struct dz_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dz_out (struct dz_port*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct dz_port* to_dport (struct uart_port*) ; 

__attribute__((used)) static void dz_set_mctrl(struct uart_port *uport, unsigned int mctrl)
{
	/*
	 * FIXME: Handle the 3100/5000 as appropriate. --macro
	 */
	struct dz_port *dport = to_dport(uport);
	u16 tmp;

	if (dport->port.line == DZ_MODEM) {
		tmp = dz_in(dport, DZ_TCR);
		if (mctrl & TIOCM_DTR)
			tmp &= ~DZ_MODEM_DTR;
		else
			tmp |= DZ_MODEM_DTR;
		dz_out(dport, DZ_TCR, tmp);
	}
}