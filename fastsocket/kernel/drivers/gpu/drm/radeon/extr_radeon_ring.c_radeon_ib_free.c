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
struct radeon_ib {int /*<<< orphan*/  fence; int /*<<< orphan*/  sa_bo; int /*<<< orphan*/  semaphore; } ;
struct radeon_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  radeon_fence_unref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  radeon_sa_bo_free (struct radeon_device*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  radeon_semaphore_free (struct radeon_device*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void radeon_ib_free(struct radeon_device *rdev, struct radeon_ib *ib)
{
	radeon_semaphore_free(rdev, &ib->semaphore, ib->fence);
	radeon_sa_bo_free(rdev, &ib->sa_bo, ib->fence);
	radeon_fence_unref(&ib->fence);
}