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
struct radeon_ring {int dummy; } ;
struct radeon_device {int /*<<< orphan*/  ring_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  radeon_ring_commit (struct radeon_device*,struct radeon_ring*) ; 

void radeon_ring_unlock_commit(struct radeon_device *rdev, struct radeon_ring *ring)
{
	radeon_ring_commit(rdev, ring);
	mutex_unlock(&rdev->ring_lock);
}