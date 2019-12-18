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
struct uart_sunsab_port {int cached_mode; int /*<<< orphan*/  irqflags; int /*<<< orphan*/  pvr_dtr_bit; int /*<<< orphan*/  cached_pvr; } ;
struct uart_port {int dummy; } ;

/* Variables and functions */
 int SAB82532_MODE_FRTS ; 
 int SAB82532_MODE_RTS ; 
 int /*<<< orphan*/  SAB82532_REGS_PENDING ; 
 int /*<<< orphan*/  SAB82532_XPR ; 
 unsigned int TIOCM_DTR ; 
 unsigned int TIOCM_RTS ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sunsab_tx_idle (struct uart_sunsab_port*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void sunsab_set_mctrl(struct uart_port *port, unsigned int mctrl)
{
	struct uart_sunsab_port *up = (struct uart_sunsab_port *) port;

	if (mctrl & TIOCM_RTS) {
		up->cached_mode &= ~SAB82532_MODE_FRTS;
		up->cached_mode |= SAB82532_MODE_RTS;
	} else {
		up->cached_mode |= (SAB82532_MODE_FRTS |
				    SAB82532_MODE_RTS);
	}
	if (mctrl & TIOCM_DTR) {
		up->cached_pvr &= ~(up->pvr_dtr_bit);
	} else {
		up->cached_pvr |= up->pvr_dtr_bit;
	}

	set_bit(SAB82532_REGS_PENDING, &up->irqflags);
	if (test_bit(SAB82532_XPR, &up->irqflags))
		sunsab_tx_idle(up);
}