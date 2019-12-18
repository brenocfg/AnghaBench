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
struct parport {int dummy; } ;

/* Variables and functions */
 int ECR_F_EMPTY ; 
 int /*<<< orphan*/  current ; 
 unsigned long jiffies ; 
 int /*<<< orphan*/  msleep_interruptible (unsigned int) ; 
 int parport_ip32_read_econtrol (struct parport*) ; 
 scalar_t__ signal_pending (int /*<<< orphan*/ ) ; 
 scalar_t__ time_after (unsigned long,unsigned long) ; 
 scalar_t__ time_after_eq (unsigned long,unsigned long) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static unsigned int parport_ip32_drain_fifo(struct parport *p,
					    unsigned long timeout)
{
	unsigned long expire = jiffies + timeout;
	unsigned int polling_interval;
	unsigned int counter;

	/* Busy wait for approx. 200us */
	for (counter = 0; counter < 40; counter++) {
		if (parport_ip32_read_econtrol(p) & ECR_F_EMPTY)
			break;
		if (time_after(jiffies, expire))
			break;
		if (signal_pending(current))
			break;
		udelay(5);
	}
	/* Poll slowly.  Polling interval starts with 1 millisecond, and is
	 * increased exponentially until 128.  */
	polling_interval = 1; /* msecs */
	while (!(parport_ip32_read_econtrol(p) & ECR_F_EMPTY)) {
		if (time_after_eq(jiffies, expire))
			break;
		msleep_interruptible(polling_interval);
		if (signal_pending(current))
			break;
		if (polling_interval < 128)
			polling_interval *= 2;
	}

	return !!(parport_ip32_read_econtrol(p) & ECR_F_EMPTY);
}