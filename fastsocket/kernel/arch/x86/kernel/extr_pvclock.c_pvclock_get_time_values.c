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
struct pvclock_vcpu_time_info {int version; int /*<<< orphan*/  flags; int /*<<< orphan*/  tsc_shift; int /*<<< orphan*/  tsc_to_system_mul; int /*<<< orphan*/  system_time; int /*<<< orphan*/  tsc_timestamp; } ;
struct pvclock_shadow_time {int version; int /*<<< orphan*/  flags; int /*<<< orphan*/  tsc_shift; int /*<<< orphan*/  tsc_to_nsec_mul; int /*<<< orphan*/  system_timestamp; int /*<<< orphan*/  tsc_timestamp; } ;

/* Variables and functions */
 int /*<<< orphan*/  rmb () ; 

__attribute__((used)) static unsigned pvclock_get_time_values(struct pvclock_shadow_time *dst,
					struct pvclock_vcpu_time_info *src)
{
	do {
		dst->version = src->version;
		rmb();		/* fetch version before data */
		dst->tsc_timestamp     = src->tsc_timestamp;
		dst->system_timestamp  = src->system_time;
		dst->tsc_to_nsec_mul   = src->tsc_to_system_mul;
		dst->tsc_shift         = src->tsc_shift;
		dst->flags             = src->flags;
		rmb();		/* test version after fetching data */
	} while ((src->version & 1) || (dst->version != src->version));

	return dst->version;
}