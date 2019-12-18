#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ gtt_base_align; } ;
struct radeon_device {int flags; TYPE_1__ mc; } ;

/* Variables and functions */
 int RADEON_IS_AGP ; 
 int /*<<< orphan*/  r100_vram_init_sizes (struct radeon_device*) ; 
 int /*<<< orphan*/  r520_vram_get_type (struct radeon_device*) ; 
 int /*<<< orphan*/  radeon_gtt_location (struct radeon_device*,TYPE_1__*) ; 
 int /*<<< orphan*/  radeon_update_bandwidth_info (struct radeon_device*) ; 
 int /*<<< orphan*/  radeon_vram_location (struct radeon_device*,TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void r520_mc_init(struct radeon_device *rdev)
{

	r520_vram_get_type(rdev);
	r100_vram_init_sizes(rdev);
	radeon_vram_location(rdev, &rdev->mc, 0);
	rdev->mc.gtt_base_align = 0;
	if (!(rdev->flags & RADEON_IS_AGP))
		radeon_gtt_location(rdev, &rdev->mc);
	radeon_update_bandwidth_info(rdev);
}