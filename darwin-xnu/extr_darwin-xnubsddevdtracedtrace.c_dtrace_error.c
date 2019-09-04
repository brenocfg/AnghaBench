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
typedef  scalar_t__ uint32_t ;

/* Variables and functions */
 scalar_t__ dtrace_cas32 (scalar_t__*,scalar_t__,scalar_t__) ; 

__attribute__((used)) static void
dtrace_error(uint32_t *counter)
{
	/*
	 * Most counters stored to in probe context are per-CPU counters.
	 * However, there are some error conditions that are sufficiently
	 * arcane that they don't merit per-CPU storage.  If these counters
	 * are incremented concurrently on different CPUs, scalability will be
	 * adversely affected -- but we don't expect them to be white-hot in a
	 * correctly constructed enabling...
	 */
	uint32_t oval, nval;

	do {
		oval = *counter;

		if ((nval = oval + 1) == 0) {
			/*
			 * If the counter would wrap, set it to 1 -- assuring
			 * that the counter is never zero when we have seen
			 * errors.  (The counter must be 32-bits because we
			 * aren't guaranteed a 64-bit compare&swap operation.)
			 * To save this code both the infamy of being fingered
			 * by a priggish news story and the indignity of being
			 * the target of a neo-puritan witch trial, we're
			 * carefully avoiding any colorful description of the
			 * likelihood of this condition -- but suffice it to
			 * say that it is only slightly more likely than the
			 * overflow of predicate cache IDs, as discussed in
			 * dtrace_predicate_create().
			 */
			nval = 1;
		}
	} while (dtrace_cas32(counter, oval, nval) != oval);
}