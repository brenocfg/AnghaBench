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
struct drm_device {int /*<<< orphan*/ * dev_private; } ;
typedef  int /*<<< orphan*/  drm_radeon_private_t ;

/* Variables and functions */
 int /*<<< orphan*/  RADEON_CLOCK_CNTL_DATA ; 
 int /*<<< orphan*/  RADEON_CLOCK_CNTL_INDEX ; 
 int RADEON_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RADEON_WRITE8 (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int RADEON_READ_PLL(struct drm_device * dev, int addr)
{
	drm_radeon_private_t *dev_priv = dev->dev_private;

	RADEON_WRITE8(RADEON_CLOCK_CNTL_INDEX, addr & 0x1f);
	return RADEON_READ(RADEON_CLOCK_CNTL_DATA);
}