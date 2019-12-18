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
struct radeon_device {int dummy; } ;
struct drm_device {struct radeon_device* dev_private; } ;

/* Variables and functions */
 int RADEON_PPLL_ATOMIC_UPDATE_R ; 
 int /*<<< orphan*/  RADEON_PPLL_REF_DIV ; 
 int RREG32_PLL (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void radeon_pll_wait_for_read_update_complete(struct drm_device *dev)
{
	struct radeon_device *rdev = dev->dev_private;
	int i = 0;

	/* FIXME: Certain revisions of R300 can't recover here.  Not sure of
	   the cause yet, but this workaround will mask the problem for now.
	   Other chips usually will pass at the very first test, so the
	   workaround shouldn't have any effect on them. */
	for (i = 0;
	     (i < 10000 &&
	      RREG32_PLL(RADEON_PPLL_REF_DIV) & RADEON_PPLL_ATOMIC_UPDATE_R);
	     i++);
}