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
struct pvclock_shadow_time {int /*<<< orphan*/  tsc_shift; int /*<<< orphan*/  tsc_to_nsec_mul; scalar_t__ tsc_timestamp; } ;

/* Variables and functions */
 scalar_t__ native_read_tsc () ; 
 scalar_t__ pvclock_scale_delta (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u64 pvclock_get_nsec_offset(struct pvclock_shadow_time *shadow)
{
	u64 delta = native_read_tsc() - shadow->tsc_timestamp;
	return pvclock_scale_delta(delta, shadow->tsc_to_nsec_mul,
				   shadow->tsc_shift);
}