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
struct inet_timewait_death_row {scalar_t__ tw_count; int slot; int thread_slots; int /*<<< orphan*/  death_lock; scalar_t__ period; int /*<<< orphan*/  tw_timer; int /*<<< orphan*/  twkill_work; } ;

/* Variables and functions */
 int INET_TWDR_TWKILL_SLOTS ; 
 scalar_t__ inet_twdr_do_twkill_work (struct inet_timewait_death_row*,int) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

void inet_twdr_hangman(unsigned long data)
{
	struct inet_timewait_death_row *twdr;
	int unsigned need_timer;

	twdr = (struct inet_timewait_death_row *)data;
	spin_lock(&twdr->death_lock);

	if (twdr->tw_count == 0)
		goto out;

	need_timer = 0;
	if (inet_twdr_do_twkill_work(twdr, twdr->slot)) {
		twdr->thread_slots |= (1 << twdr->slot);
		schedule_work(&twdr->twkill_work);
		need_timer = 1;
	} else {
		/* We purged the entire slot, anything left?  */
		if (twdr->tw_count)
			need_timer = 1;
		twdr->slot = ((twdr->slot + 1) & (INET_TWDR_TWKILL_SLOTS - 1));
	}
	if (need_timer)
		mod_timer(&twdr->tw_timer, jiffies + twdr->period);
out:
	spin_unlock(&twdr->death_lock);
}