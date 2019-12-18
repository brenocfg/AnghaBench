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
struct pvclock_vcpu_time_info {unsigned int version; } ;
struct pvclock_shadow_time {scalar_t__ system_timestamp; int flags; } ;
typedef  scalar_t__ cycle_t ;

/* Variables and functions */
 int PVCLOCK_TSC_STABLE_BIT ; 
 scalar_t__ atomic64_cmpxchg (int /*<<< orphan*/ *,scalar_t__,scalar_t__) ; 
 scalar_t__ atomic64_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  barrier () ; 
 int /*<<< orphan*/  last_value ; 
 scalar_t__ pvclock_get_nsec_offset (struct pvclock_shadow_time*) ; 
 unsigned int pvclock_get_time_values (struct pvclock_shadow_time*,struct pvclock_vcpu_time_info*) ; 
 scalar_t__ unlikely (int) ; 
 int valid_flags ; 

cycle_t pvclock_clocksource_read(struct pvclock_vcpu_time_info *src)
{
	struct pvclock_shadow_time shadow;
	unsigned version;
	cycle_t ret, offset;
	u64 last;

	do {
		version = pvclock_get_time_values(&shadow, src);
		barrier();
		offset = pvclock_get_nsec_offset(&shadow);
		ret = shadow.system_timestamp + offset;
		barrier();
	} while (version != src->version);

	if ((valid_flags & PVCLOCK_TSC_STABLE_BIT) &&
		(shadow.flags & PVCLOCK_TSC_STABLE_BIT))
		return ret;

	/*
	 * Assumption here is that last_value, a global accumulator, always goes
	 * forward. If we are less than that, we should not be much smaller.
	 * We assume there is an error marging we're inside, and then the correction
	 * does not sacrifice accuracy.
	 *
	 * For reads: global may have changed between test and return,
	 * but this means someone else updated poked the clock at a later time.
	 * We just need to make sure we are not seeing a backwards event.
	 *
	 * For updates: last_value = ret is not enough, since two vcpus could be
	 * updating at the same time, and one of them could be slightly behind,
	 * making the assumption that last_value always go forward fail to hold.
	 */
	last = atomic64_read(&last_value);
	do {
		if (ret < last)
			return last;
		last = atomic64_cmpxchg(&last_value, last, ret);
	} while (unlikely(last != ret));

	return ret;
}