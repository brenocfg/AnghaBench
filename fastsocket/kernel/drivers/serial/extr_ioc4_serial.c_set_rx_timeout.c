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
struct ioc4_port {int ip_rx_timeout; int ip_baud; int ip_sscr; TYPE_1__* ip_serial_regs; } ;
struct TYPE_2__ {int /*<<< orphan*/  srtr; int /*<<< orphan*/  sscr; } ;

/* Variables and functions */
 int IOC4_SRTR_CNT ; 
 int IOC4_SRTR_HZ ; 
 int IOC4_SSCR_RX_THRESHOLD ; 
 int /*<<< orphan*/  writel (int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline int set_rx_timeout(struct ioc4_port *port, int timeout)
{
	int threshold;

	port->ip_rx_timeout = timeout;

	/* Timeout is in ticks.  Let's figure out how many chars we
	 * can receive at the current baud rate in that interval
	 * and set the rx threshold to that amount.  There are 4 chars
	 * per ring entry, so we'll divide the number of chars that will
	 * arrive in timeout by 4.
	 * So .... timeout * baud / 10 / HZ / 4, with HZ = 100.
	 */
	threshold = timeout * port->ip_baud / 4000;
	if (threshold == 0)
		threshold = 1;	/* otherwise we'll intr all the time! */

	if ((unsigned)threshold > (unsigned)IOC4_SSCR_RX_THRESHOLD)
		return 1;

	port->ip_sscr &= ~IOC4_SSCR_RX_THRESHOLD;
	port->ip_sscr |= threshold;

	writel(port->ip_sscr, &port->ip_serial_regs->sscr);

	/* Now set the rx timeout to the given value
	 * again timeout * IOC4_SRTR_HZ / HZ
	 */
	timeout = timeout * IOC4_SRTR_HZ / 100;
	if (timeout > IOC4_SRTR_CNT)
		timeout = IOC4_SRTR_CNT;

	writel(timeout, &port->ip_serial_regs->srtr);
	return 0;
}