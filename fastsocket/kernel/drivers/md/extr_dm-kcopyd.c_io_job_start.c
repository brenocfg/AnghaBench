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
struct dm_kcopyd_throttle {unsigned int last_jiffies; unsigned int io_period; unsigned int total_period; scalar_t__ num_io_jobs; int /*<<< orphan*/  throttle; } ;

/* Variables and functions */
 unsigned int ACCESS_ONCE (int /*<<< orphan*/ ) ; 
 int ACCOUNT_INTERVAL_SHIFT ; 
 int MAX_SLEEPS ; 
 int /*<<< orphan*/  SLEEP_MSEC ; 
 int fls (int) ; 
 unsigned int jiffies ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  msleep (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  throttle_spinlock ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void io_job_start(struct dm_kcopyd_throttle *t)
{
	unsigned throttle, now, difference;
	int slept = 0, skew;

	if (unlikely(!t))
		return;

try_again:
	spin_lock_irq(&throttle_spinlock);

	throttle = ACCESS_ONCE(t->throttle);

	if (likely(throttle >= 100))
		goto skip_limit;

	now = jiffies;
	difference = now - t->last_jiffies;
	t->last_jiffies = now;
	if (t->num_io_jobs)
		t->io_period += difference;
	t->total_period += difference;

	/*
	 * Maintain sane values if we got a temporary overflow.
	 */
	if (unlikely(t->io_period > t->total_period))
		t->io_period = t->total_period;

	if (unlikely(t->total_period >= (1 << ACCOUNT_INTERVAL_SHIFT))) {
		int shift = fls(t->total_period >> ACCOUNT_INTERVAL_SHIFT);
		t->total_period >>= shift;
		t->io_period >>= shift;
	}

	skew = t->io_period - throttle * t->total_period / 100;

	if (unlikely(skew > 0) && slept < MAX_SLEEPS) {
		slept++;
		spin_unlock_irq(&throttle_spinlock);
		msleep(SLEEP_MSEC);
		goto try_again;
	}

skip_limit:
	t->num_io_jobs++;

	spin_unlock_irq(&throttle_spinlock);
}