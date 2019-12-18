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
struct TYPE_4__ {int flags; int /*<<< orphan*/  tty; int /*<<< orphan*/  open_wait; int /*<<< orphan*/  delta_msr_wait; } ;
struct TYPE_3__ {int /*<<< orphan*/  cts; int /*<<< orphan*/  dcd; int /*<<< orphan*/  dsr; int /*<<< orphan*/  rng; } ;
struct esp_struct {TYPE_2__ port; int /*<<< orphan*/  line; TYPE_1__ icount; } ;

/* Variables and functions */
 int ASYNC_CHECK_CD ; 
 int /*<<< orphan*/  ESI_GET_UART_STAT ; 
 int /*<<< orphan*/  UART_ESI_CMD1 ; 
 int /*<<< orphan*/  UART_ESI_STAT2 ; 
 int UART_MSR_ANY_DELTA ; 
 int UART_MSR_DCD ; 
 int UART_MSR_DCTS ; 
 int UART_MSR_DDCD ; 
 int UART_MSR_DDSR ; 
 int UART_MSR_TERI ; 
 int /*<<< orphan*/  printk (char*,...) ; 
 int serial_in (struct esp_struct*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  serial_out (struct esp_struct*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tty_hangup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void check_modem_status(struct esp_struct *info)
{
	int	status;

	serial_out(info, UART_ESI_CMD1, ESI_GET_UART_STAT);
	status = serial_in(info, UART_ESI_STAT2);

	if (status & UART_MSR_ANY_DELTA) {
		/* update input line counters */
		if (status & UART_MSR_TERI)
			info->icount.rng++;
		if (status & UART_MSR_DDSR)
			info->icount.dsr++;
		if (status & UART_MSR_DDCD)
			info->icount.dcd++;
		if (status & UART_MSR_DCTS)
			info->icount.cts++;
		wake_up_interruptible(&info->port.delta_msr_wait);
	}

	if ((info->port.flags & ASYNC_CHECK_CD) && (status & UART_MSR_DDCD)) {
#if (defined(SERIAL_DEBUG_OPEN) || defined(SERIAL_DEBUG_INTR))
		printk("ttys%d CD now %s...", info->line,
		       (status & UART_MSR_DCD) ? "on" : "off");
#endif
		if (status & UART_MSR_DCD)
			wake_up_interruptible(&info->port.open_wait);
		else {
#ifdef SERIAL_DEBUG_OPEN
			printk("scheduling hangup...");
#endif
			tty_hangup(info->port.tty);
		}
	}
}