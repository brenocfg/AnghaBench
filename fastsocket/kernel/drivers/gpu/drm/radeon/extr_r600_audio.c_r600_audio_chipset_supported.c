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
struct radeon_device {scalar_t__ family; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASIC_IS_DCE6 (struct radeon_device*) ; 
 scalar_t__ CHIP_R600 ; 
 scalar_t__ CHIP_RS600 ; 
 scalar_t__ CHIP_RS690 ; 
 scalar_t__ CHIP_RS740 ; 

__attribute__((used)) static int r600_audio_chipset_supported(struct radeon_device *rdev)
{
	return (rdev->family >= CHIP_R600 && !ASIC_IS_DCE6(rdev))
		|| rdev->family == CHIP_RS600
		|| rdev->family == CHIP_RS690
		|| rdev->family == CHIP_RS740;
}