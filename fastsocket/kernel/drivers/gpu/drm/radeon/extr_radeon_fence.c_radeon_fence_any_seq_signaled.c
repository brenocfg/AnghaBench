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
struct radeon_device {int dummy; } ;

/* Variables and functions */
 unsigned int RADEON_NUM_RINGS ; 
 scalar_t__ radeon_fence_seq_signaled (struct radeon_device*,scalar_t__,unsigned int) ; 

__attribute__((used)) static bool radeon_fence_any_seq_signaled(struct radeon_device *rdev, u64 *seq)
{
	unsigned i;

	for (i = 0; i < RADEON_NUM_RINGS; ++i) {
		if (seq[i] && radeon_fence_seq_signaled(rdev, seq[i], i)) {
			return true;
		}
	}
	return false;
}