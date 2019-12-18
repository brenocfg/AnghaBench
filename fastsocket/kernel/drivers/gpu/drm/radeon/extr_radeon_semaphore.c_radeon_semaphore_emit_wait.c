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
struct radeon_semaphore {int /*<<< orphan*/  waiters; } ;
struct radeon_device {int /*<<< orphan*/ * ring; } ;

/* Variables and functions */
 int /*<<< orphan*/  radeon_semaphore_ring_emit (struct radeon_device*,int,int /*<<< orphan*/ *,struct radeon_semaphore*,int) ; 

void radeon_semaphore_emit_wait(struct radeon_device *rdev, int ring,
			        struct radeon_semaphore *semaphore)
{
	++semaphore->waiters;
	radeon_semaphore_ring_emit(rdev, ring, &rdev->ring[ring], semaphore, true);
}