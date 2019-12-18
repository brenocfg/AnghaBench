#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  dsr; } ;
struct TYPE_9__ {TYPE_3__* state; TYPE_1__ icount; } ;
struct uart_pmac_port {unsigned char prev_status; int /*<<< orphan*/  flags; TYPE_4__ port; } ;
struct TYPE_7__ {int /*<<< orphan*/  delta_msr_wait; } ;
struct TYPE_8__ {TYPE_2__ port; } ;

/* Variables and functions */
 unsigned char BRK_ABRT ; 
 unsigned char CTS ; 
 unsigned char DCD ; 
 int /*<<< orphan*/  PMACZILOG_FLAG_BREAK ; 
 int /*<<< orphan*/  R0 ; 
 int /*<<< orphan*/  RES_EXT_INT ; 
 unsigned char SYNC_HUNT ; 
 scalar_t__ ZS_IS_OPEN (struct uart_pmac_port*) ; 
 scalar_t__ ZS_WANTS_MODEM_STATUS (struct uart_pmac_port*) ; 
 unsigned char read_zsreg (struct uart_pmac_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uart_handle_cts_change (TYPE_4__*,int) ; 
 int /*<<< orphan*/  uart_handle_dcd_change (TYPE_4__*,unsigned char) ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_zsreg (struct uart_pmac_port*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zssync (struct uart_pmac_port*) ; 

__attribute__((used)) static void pmz_status_handle(struct uart_pmac_port *uap)
{
	unsigned char status;

	status = read_zsreg(uap, R0);
	write_zsreg(uap, R0, RES_EXT_INT);
	zssync(uap);

	if (ZS_IS_OPEN(uap) && ZS_WANTS_MODEM_STATUS(uap)) {
		if (status & SYNC_HUNT)
			uap->port.icount.dsr++;

		/* The Zilog just gives us an interrupt when DCD/CTS/etc. change.
		 * But it does not tell us which bit has changed, we have to keep
		 * track of this ourselves.
		 * The CTS input is inverted for some reason.  -- paulus
		 */
		if ((status ^ uap->prev_status) & DCD)
			uart_handle_dcd_change(&uap->port,
					       (status & DCD));
		if ((status ^ uap->prev_status) & CTS)
			uart_handle_cts_change(&uap->port,
					       !(status & CTS));

		wake_up_interruptible(&uap->port.state->port.delta_msr_wait);
	}

	if (status & BRK_ABRT)
		uap->flags |= PMACZILOG_FLAG_BREAK;

	uap->prev_status = status;
}