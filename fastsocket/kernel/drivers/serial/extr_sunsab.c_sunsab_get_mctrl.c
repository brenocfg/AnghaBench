#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct uart_sunsab_port {unsigned char pvr_dsr_bit; TYPE_1__* regs; } ;
struct uart_port {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  star; int /*<<< orphan*/  vstr; int /*<<< orphan*/  pvr; } ;
struct TYPE_3__ {TYPE_2__ r; } ;

/* Variables and functions */
 unsigned char SAB82532_STAR_CTS ; 
 unsigned char SAB82532_VSTR_CD ; 
 unsigned int TIOCM_CAR ; 
 unsigned int TIOCM_CTS ; 
 unsigned int TIOCM_DSR ; 
 unsigned char readb (int /*<<< orphan*/ *) ; 

__attribute__((used)) static unsigned int sunsab_get_mctrl(struct uart_port *port)
{
	struct uart_sunsab_port *up = (struct uart_sunsab_port *) port;
	unsigned char val;
	unsigned int result;

	result = 0;

	val = readb(&up->regs->r.pvr);
	result |= (val & up->pvr_dsr_bit) ? 0 : TIOCM_DSR;

	val = readb(&up->regs->r.vstr);
	result |= (val & SAB82532_VSTR_CD) ? 0 : TIOCM_CAR;

	val = readb(&up->regs->r.star);
	result |= (val & SAB82532_STAR_CTS) ? TIOCM_CTS : 0;

	return result;
}