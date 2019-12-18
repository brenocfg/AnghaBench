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
struct radeon_ib {struct radeon_fence** sync_to; } ;
struct radeon_fence {size_t ring; } ;

/* Variables and functions */
 struct radeon_fence* radeon_fence_later (struct radeon_fence*,struct radeon_fence*) ; 

void radeon_ib_sync_to(struct radeon_ib *ib, struct radeon_fence *fence)
{
	struct radeon_fence *other;

	if (!fence)
		return;

	other = ib->sync_to[fence->ring];
	ib->sync_to[fence->ring] = radeon_fence_later(fence, other);
}