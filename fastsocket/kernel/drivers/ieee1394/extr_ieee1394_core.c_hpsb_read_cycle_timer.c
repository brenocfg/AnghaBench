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
typedef  scalar_t__ u64 ;
typedef  int u32 ;
struct timeval {unsigned long long tv_sec; scalar_t__ tv_usec; } ;
struct hpsb_host {TYPE_1__* driver; } ;
struct TYPE_2__ {int (* devctl ) (struct hpsb_host*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int EINVAL ; 
 int EIO ; 
 int /*<<< orphan*/  GET_CYCLE_COUNTER ; 
 int /*<<< orphan*/  do_gettimeofday (struct timeval*) ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 int /*<<< orphan*/  preempt_disable () ; 
 int /*<<< orphan*/  preempt_enable () ; 
 int stub1 (struct hpsb_host*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int hpsb_read_cycle_timer(struct hpsb_host *host, u32 *cycle_timer,
			  u64 *local_time)
{
	int ctr;
	struct timeval tv;
	unsigned long flags;

	if (!host || !cycle_timer || !local_time)
		return -EINVAL;

	preempt_disable();
	local_irq_save(flags);

	ctr = host->driver->devctl(host, GET_CYCLE_COUNTER, 0);
	if (ctr)
		do_gettimeofday(&tv);

	local_irq_restore(flags);
	preempt_enable();

	if (!ctr)
		return -EIO;
	*cycle_timer = ctr;
	*local_time = tv.tv_sec * 1000000ULL + tv.tv_usec;
	return 0;
}