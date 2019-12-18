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
typedef  int uint64_t ;
struct TYPE_2__ {int gtt_size; } ;
struct radeon_device {int /*<<< orphan*/  dev; TYPE_1__ mc; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*,int) ; 
 int radeon_agpmode ; 
 int /*<<< orphan*/  radeon_check_pot_argument (int) ; 
 int radeon_gart_size ; 
 int radeon_vram_limit ; 

__attribute__((used)) static void radeon_check_arguments(struct radeon_device *rdev)
{
	/* vramlimit must be a power of two */
	if (!radeon_check_pot_argument(radeon_vram_limit)) {
		dev_warn(rdev->dev, "vram limit (%d) must be a power of 2\n",
				radeon_vram_limit);
		radeon_vram_limit = 0;
	}

	/* gtt size must be power of two and greater or equal to 32M */
	if (radeon_gart_size < 32) {
		dev_warn(rdev->dev, "gart size (%d) too small forcing to 512M\n",
				radeon_gart_size);
		radeon_gart_size = 512;

	} else if (!radeon_check_pot_argument(radeon_gart_size)) {
		dev_warn(rdev->dev, "gart size (%d) must be a power of 2\n",
				radeon_gart_size);
		radeon_gart_size = 512;
	}
	rdev->mc.gtt_size = (uint64_t)radeon_gart_size << 20;

	/* AGP mode can only be -1, 1, 2, 4, 8 */
	switch (radeon_agpmode) {
	case -1:
	case 0:
	case 1:
	case 2:
	case 4:
	case 8:
		break;
	default:
		dev_warn(rdev->dev, "invalid AGP mode %d (valid mode: "
				"-1, 0, 1, 2, 4, 8)\n", radeon_agpmode);
		radeon_agpmode = 0;
		break;
	}
}