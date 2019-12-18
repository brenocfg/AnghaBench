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
struct TYPE_2__ {void** saveSWF2; void** saveSWF1; void** saveSWF0; void* saveMI_ARB_STATE; void* saveCACHE_MODE_0; void* saveIMR; void* saveIER; void* savePCH_PORT_HOTPLUG; void* saveMCHBAR_RENDER_STANDBY; void* saveFDI_RXB_IMR; void* saveFDI_RXA_IMR; void* saveGTIMR; void* saveGTIER; void* saveDEIMR; void* saveDEIER; int /*<<< orphan*/  saveLBB; } ;
struct drm_i915_private {TYPE_1__ regfile; } ;
struct drm_device {int /*<<< orphan*/  struct_mutex; int /*<<< orphan*/  pdev; struct drm_i915_private* dev_private; } ;

/* Variables and functions */
 scalar_t__ CACHE_MODE_0 ; 
 scalar_t__ DEIER ; 
 scalar_t__ DEIMR ; 
 int /*<<< orphan*/  DRIVER_MODESET ; 
 scalar_t__ GTIER ; 
 scalar_t__ GTIMR ; 
 scalar_t__ HAS_PCH_SPLIT (struct drm_device*) ; 
 void* I915_READ (scalar_t__) ; 
 scalar_t__ IER ; 
 scalar_t__ IMR ; 
 int /*<<< orphan*/  LBB ; 
 scalar_t__ MI_ARB_STATE ; 
 scalar_t__ PCH_PORT_HOTPLUG ; 
 scalar_t__ RSTDBYCTL ; 
 scalar_t__ SWF00 ; 
 scalar_t__ SWF10 ; 
 scalar_t__ SWF30 ; 
 scalar_t__ _FDI_RXA_IMR ; 
 scalar_t__ _FDI_RXB_IMR ; 
 int /*<<< orphan*/  drm_core_check_feature (struct drm_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i915_save_display (struct drm_device*) ; 
 int /*<<< orphan*/  intel_disable_gt_powersave (struct drm_device*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_read_config_byte (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int i915_save_state(struct drm_device *dev)
{
	struct drm_i915_private *dev_priv = dev->dev_private;
	int i;

	pci_read_config_byte(dev->pdev, LBB, &dev_priv->regfile.saveLBB);

	mutex_lock(&dev->struct_mutex);

	i915_save_display(dev);

	if (!drm_core_check_feature(dev, DRIVER_MODESET)) {
		/* Interrupt state */
		if (HAS_PCH_SPLIT(dev)) {
			dev_priv->regfile.saveDEIER = I915_READ(DEIER);
			dev_priv->regfile.saveDEIMR = I915_READ(DEIMR);
			dev_priv->regfile.saveGTIER = I915_READ(GTIER);
			dev_priv->regfile.saveGTIMR = I915_READ(GTIMR);
			dev_priv->regfile.saveFDI_RXA_IMR = I915_READ(_FDI_RXA_IMR);
			dev_priv->regfile.saveFDI_RXB_IMR = I915_READ(_FDI_RXB_IMR);
			dev_priv->regfile.saveMCHBAR_RENDER_STANDBY =
				I915_READ(RSTDBYCTL);
			dev_priv->regfile.savePCH_PORT_HOTPLUG = I915_READ(PCH_PORT_HOTPLUG);
		} else {
			dev_priv->regfile.saveIER = I915_READ(IER);
			dev_priv->regfile.saveIMR = I915_READ(IMR);
		}
	}

	intel_disable_gt_powersave(dev);

	/* Cache mode state */
	dev_priv->regfile.saveCACHE_MODE_0 = I915_READ(CACHE_MODE_0);

	/* Memory Arbitration state */
	dev_priv->regfile.saveMI_ARB_STATE = I915_READ(MI_ARB_STATE);

	/* Scratch space */
	for (i = 0; i < 16; i++) {
		dev_priv->regfile.saveSWF0[i] = I915_READ(SWF00 + (i << 2));
		dev_priv->regfile.saveSWF1[i] = I915_READ(SWF10 + (i << 2));
	}
	for (i = 0; i < 3; i++)
		dev_priv->regfile.saveSWF2[i] = I915_READ(SWF30 + (i << 2));

	mutex_unlock(&dev->struct_mutex);

	return 0;
}