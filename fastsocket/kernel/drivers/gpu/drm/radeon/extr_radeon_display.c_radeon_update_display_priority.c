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
struct radeon_device {scalar_t__ family; int flags; int disp_priority; } ;

/* Variables and functions */
 scalar_t__ ASIC_IS_R300 (struct radeon_device*) ; 
 scalar_t__ CHIP_RV515 ; 
 int RADEON_IS_IGP ; 
 int radeon_disp_priority ; 

void radeon_update_display_priority(struct radeon_device *rdev)
{
	/* adjustment options for the display watermarks */
	if ((radeon_disp_priority == 0) || (radeon_disp_priority > 2)) {
		/* set display priority to high for r3xx, rv515 chips
		 * this avoids flickering due to underflow to the
		 * display controllers during heavy acceleration.
		 * Don't force high on rs4xx igp chips as it seems to
		 * affect the sound card.  See kernel bug 15982.
		 */
		if ((ASIC_IS_R300(rdev) || (rdev->family == CHIP_RV515)) &&
		    !(rdev->flags & RADEON_IS_IGP))
			rdev->disp_priority = 2;
		else
			rdev->disp_priority = 0;
	} else
		rdev->disp_priority = radeon_disp_priority;

}