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
typedef  int /*<<< orphan*/  u32 ;
struct ioat_chan_common {int dummy; } ;

/* Variables and functions */
 int ETIMEDOUT ; 
 int /*<<< orphan*/  cpu_relax () ; 
 int /*<<< orphan*/  ioat_chansts (struct ioat_chan_common*) ; 
 int /*<<< orphan*/  ioat_suspend (struct ioat_chan_common*) ; 
 scalar_t__ is_ioat_active (int /*<<< orphan*/ ) ; 
 scalar_t__ is_ioat_idle (int /*<<< orphan*/ ) ; 
 unsigned long jiffies ; 
 scalar_t__ time_after (unsigned long,unsigned long) ; 

int ioat2_quiesce(struct ioat_chan_common *chan, unsigned long tmo)
{
	unsigned long end = jiffies + tmo;
	int err = 0;
	u32 status;

	status = ioat_chansts(chan);
	if (is_ioat_active(status) || is_ioat_idle(status))
		ioat_suspend(chan);
	while (is_ioat_active(status) || is_ioat_idle(status)) {
		if (tmo && time_after(jiffies, end)) {
			err = -ETIMEDOUT;
			break;
		}
		status = ioat_chansts(chan);
		cpu_relax();
	}

	return err;
}