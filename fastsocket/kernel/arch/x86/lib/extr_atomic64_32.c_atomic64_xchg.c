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
typedef  scalar_t__ u64 ;
typedef  int /*<<< orphan*/  atomic64_t ;

/* Variables and functions */
 scalar_t__ atomic64_cmpxchg (int /*<<< orphan*/ *,scalar_t__,scalar_t__) ; 

u64 atomic64_xchg(atomic64_t *ptr, u64 new_val)
{
	/*
	 * Try first with a (possibly incorrect) assumption about
	 * what we have there. We'll do two loops most likely,
	 * but we'll get an ownership MESI transaction straight away
	 * instead of a read transaction followed by a
	 * flush-for-ownership transaction:
	 */
	u64 old_val, real_val = 0;

	do {
		old_val = real_val;

		real_val = atomic64_cmpxchg(ptr, old_val, new_val);

	} while (real_val != old_val);

	return old_val;
}