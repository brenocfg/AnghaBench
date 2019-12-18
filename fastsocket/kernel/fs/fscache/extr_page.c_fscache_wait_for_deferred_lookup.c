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
struct fscache_cookie {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int ERESTARTSYS ; 
 int /*<<< orphan*/  FSCACHE_COOKIE_LOOKING_UP ; 
 int /*<<< orphan*/  TASK_INTERRUPTIBLE ; 
 int /*<<< orphan*/  _enter (char*) ; 
 int /*<<< orphan*/  _leave (char*) ; 
 int /*<<< orphan*/  fscache_hist (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  fscache_n_retrievals_intr ; 
 int /*<<< orphan*/  fscache_n_retrievals_wait ; 
 int /*<<< orphan*/  fscache_retrieval_delay_histogram ; 
 int /*<<< orphan*/  fscache_stat (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fscache_wait_bit_interruptible ; 
 unsigned long jiffies ; 
 int /*<<< orphan*/  smp_rmb () ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ wait_on_bit (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int fscache_wait_for_deferred_lookup(struct fscache_cookie *cookie)
{
	unsigned long jif;

	_enter("");

	if (!test_bit(FSCACHE_COOKIE_LOOKING_UP, &cookie->flags)) {
		_leave(" = 0 [imm]");
		return 0;
	}

	fscache_stat(&fscache_n_retrievals_wait);

	jif = jiffies;
	if (wait_on_bit(&cookie->flags, FSCACHE_COOKIE_LOOKING_UP,
			fscache_wait_bit_interruptible,
			TASK_INTERRUPTIBLE) != 0) {
		fscache_stat(&fscache_n_retrievals_intr);
		_leave(" = -ERESTARTSYS");
		return -ERESTARTSYS;
	}

	ASSERT(!test_bit(FSCACHE_COOKIE_LOOKING_UP, &cookie->flags));

	smp_rmb();
	fscache_hist(fscache_retrieval_delay_histogram, jif);
	_leave(" = 0 [dly]");
	return 0;
}