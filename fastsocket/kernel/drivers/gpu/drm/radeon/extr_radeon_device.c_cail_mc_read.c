#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct radeon_device {int /*<<< orphan*/  (* mc_rreg ) (struct radeon_device*,int /*<<< orphan*/ ) ;} ;
struct card_info {TYPE_1__* dev; } ;
struct TYPE_2__ {struct radeon_device* dev_private; } ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct radeon_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static uint32_t cail_mc_read(struct card_info *info, uint32_t reg)
{
	struct radeon_device *rdev = info->dev->dev_private;
	uint32_t r;

	r = rdev->mc_rreg(rdev, reg);
	return r;
}