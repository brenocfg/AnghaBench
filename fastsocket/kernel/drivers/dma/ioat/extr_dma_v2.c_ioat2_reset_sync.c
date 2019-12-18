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
struct ioat_chan_common {int dummy; } ;

/* Variables and functions */
 int ETIMEDOUT ; 
 int /*<<< orphan*/  cpu_relax () ; 
 int /*<<< orphan*/  ioat_reset (struct ioat_chan_common*) ; 
 scalar_t__ ioat_reset_pending (struct ioat_chan_common*) ; 
 unsigned long jiffies ; 
 scalar_t__ time_after (unsigned long,unsigned long) ; 

int ioat2_reset_sync(struct ioat_chan_common *chan, unsigned long tmo)
{
	unsigned long end = jiffies + tmo;
	int err = 0;

	ioat_reset(chan);
	while (ioat_reset_pending(chan)) {
		if (end && time_after(jiffies, end)) {
			err = -ETIMEDOUT;
			break;
		}
		cpu_relax();
	}

	return err;
}