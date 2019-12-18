#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {unsigned long expires; } ;

/* Variables and functions */
 int /*<<< orphan*/  add_timer (TYPE_1__*) ; 
 scalar_t__ del_timer (TYPE_1__*) ; 
 unsigned long dn_rt_deadline ; 
 int /*<<< orphan*/  dn_rt_flush_lock ; 
 TYPE_1__ dn_rt_flush_timer ; 
 long dn_rt_max_delay ; 
 long dn_rt_min_delay ; 
 int /*<<< orphan*/  dn_run_flush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  in_interrupt () ; 
 unsigned long jiffies ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

void dn_rt_cache_flush(int delay)
{
	unsigned long now = jiffies;
	int user_mode = !in_interrupt();

	if (delay < 0)
		delay = dn_rt_min_delay;

	spin_lock_bh(&dn_rt_flush_lock);

	if (del_timer(&dn_rt_flush_timer) && delay > 0 && dn_rt_deadline) {
		long tmo = (long)(dn_rt_deadline - now);

		if (user_mode && tmo < dn_rt_max_delay - dn_rt_min_delay)
			tmo = 0;

		if (delay > tmo)
			delay = tmo;
	}

	if (delay <= 0) {
		spin_unlock_bh(&dn_rt_flush_lock);
		dn_run_flush(0);
		return;
	}

	if (dn_rt_deadline == 0)
		dn_rt_deadline = now + dn_rt_max_delay;

	dn_rt_flush_timer.expires = now + delay;
	add_timer(&dn_rt_flush_timer);
	spin_unlock_bh(&dn_rt_flush_lock);
}