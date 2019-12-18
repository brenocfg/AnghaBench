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
typedef  int /*<<< orphan*/  u32 ;
struct radeon_device {int num_crtc; } ;

/* Variables and functions */
 scalar_t__ CRTC_STATUS_FRAME_COUNT ; 
 int /*<<< orphan*/  RREG32 (scalar_t__) ; 
 scalar_t__* crtc_offsets ; 

u32 evergreen_get_vblank_counter(struct radeon_device *rdev, int crtc)
{
	if (crtc >= rdev->num_crtc)
		return 0;
	else
		return RREG32(CRTC_STATUS_FRAME_COUNT + crtc_offsets[crtc]);
}