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
typedef  int uint32_t ;
struct drm_device {TYPE_1__* dev_private; } ;
struct TYPE_2__ {int idle_fault; scalar_t__ chipset; int /*<<< orphan*/ * mmio; } ;
typedef  TYPE_1__ drm_sis_private_t ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int DRM_HZ ; 
 scalar_t__ SIS_CHIP_315 ; 
 int SIS_READ (int) ; 
 int jiffies ; 
 int /*<<< orphan*/ * sis_reg_init (struct drm_device*) ; 
 scalar_t__ time_after_eq (int,unsigned long) ; 

int sis_idle(struct drm_device *dev)
{
	drm_sis_private_t *dev_priv = dev->dev_private;
	uint32_t idle_reg;
	unsigned long end;
	int i;

	if (dev_priv->idle_fault)
		return 0;

	if (dev_priv->mmio == NULL) {
		dev_priv->mmio = sis_reg_init(dev);
		if (dev_priv->mmio == NULL) {
			DRM_ERROR("Could not find register map.\n");
			return 0;
		}
	}

	/*
	 * Implement a device switch here if needed
	 */

	if (dev_priv->chipset != SIS_CHIP_315)
		return 0;

	/*
	 * Timeout after 3 seconds. We cannot use DRM_WAIT_ON here
	 * because its polling frequency is too low.
	 */

	end = jiffies + (DRM_HZ * 3);

	for (i = 0; i < 4; ++i) {
		do {
			idle_reg = SIS_READ(0x85cc);
		} while (!time_after_eq(jiffies, end) &&
			  ((idle_reg & 0x80000000) != 0x80000000));
	}

	if (time_after_eq(jiffies, end)) {
		DRM_ERROR("Graphics engine idle timeout. "
			  "Disabling idle check\n");
		dev_priv->idle_fault = 1;
	}

	/*
	 * The caller never sees an error code. It gets trapped
	 * in libdrm.
	 */

	return 0;
}