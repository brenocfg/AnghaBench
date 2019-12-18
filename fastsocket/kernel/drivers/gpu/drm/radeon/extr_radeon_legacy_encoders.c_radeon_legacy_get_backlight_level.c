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
typedef  int u8 ;
struct TYPE_2__ {struct drm_device* dev; } ;
struct radeon_encoder {TYPE_1__ base; } ;
struct radeon_device {int dummy; } ;
struct drm_device {struct radeon_device* dev_private; } ;

/* Variables and functions */
 int RADEON_LVDS_BL_MOD_LEVEL_SHIFT ; 
 int /*<<< orphan*/  RADEON_LVDS_GEN_CNTL ; 
 int RREG32 (int /*<<< orphan*/ ) ; 

u8
radeon_legacy_get_backlight_level(struct radeon_encoder *radeon_encoder)
{
	struct drm_device *dev = radeon_encoder->base.dev;
	struct radeon_device *rdev = dev->dev_private;
	u8 backlight_level;

	backlight_level = (RREG32(RADEON_LVDS_GEN_CNTL) >>
			   RADEON_LVDS_BL_MOD_LEVEL_SHIFT) & 0xff;

	return backlight_level;
}