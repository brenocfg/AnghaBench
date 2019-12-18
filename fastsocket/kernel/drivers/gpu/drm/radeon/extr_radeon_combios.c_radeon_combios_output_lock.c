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
typedef  int /*<<< orphan*/  uint32_t ;
struct radeon_device {int dummy; } ;
struct drm_encoder {struct drm_device* dev; } ;
struct drm_device {struct radeon_device* dev_private; } ;

/* Variables and functions */
 int /*<<< orphan*/  RADEON_BIOS_6_SCRATCH ; 
 int /*<<< orphan*/  RADEON_DRIVER_CRITICAL ; 
 int /*<<< orphan*/  RREG32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WREG32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void radeon_combios_output_lock(struct drm_encoder *encoder, bool lock)
{
	struct drm_device *dev = encoder->dev;
	struct radeon_device *rdev = dev->dev_private;
	uint32_t bios_6_scratch;

	bios_6_scratch = RREG32(RADEON_BIOS_6_SCRATCH);

	if (lock)
		bios_6_scratch |= RADEON_DRIVER_CRITICAL;
	else
		bios_6_scratch &= ~RADEON_DRIVER_CRITICAL;

	WREG32(RADEON_BIOS_6_SCRATCH, bios_6_scratch);
}