#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  hpd_irq_setup; } ;
struct TYPE_9__ {int /*<<< orphan*/  hangcheck_timer; int /*<<< orphan*/  work; } ;
struct TYPE_8__ {int /*<<< orphan*/  error_work; } ;
struct TYPE_7__ {int /*<<< orphan*/  work; } ;
struct drm_i915_private {TYPE_4__ display; int /*<<< orphan*/  pm_qos; TYPE_3__ gpu_error; TYPE_2__ l3_parity; TYPE_1__ rps; int /*<<< orphan*/  hotplug_work; } ;
struct drm_device {int max_vblank_count; TYPE_5__* driver; struct drm_i915_private* dev_private; } ;
struct TYPE_12__ {int gen; } ;
struct TYPE_11__ {int /*<<< orphan*/  disable_vblank; int /*<<< orphan*/  enable_vblank; int /*<<< orphan*/  irq_handler; void* irq_uninstall; int /*<<< orphan*/  irq_postinstall; void* irq_preinstall; int /*<<< orphan*/  get_scanout_position; int /*<<< orphan*/ * get_vblank_timestamp; int /*<<< orphan*/  get_vblank_counter; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRIVER_MODESET ; 
 scalar_t__ HAS_PCH_SPLIT (struct drm_device*) ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_6__* INTEL_INFO (struct drm_device*) ; 
 scalar_t__ IS_G4X (struct drm_device*) ; 
 scalar_t__ IS_HASWELL (struct drm_device*) ; 
 scalar_t__ IS_IVYBRIDGE (struct drm_device*) ; 
 scalar_t__ IS_VALLEYVIEW (struct drm_device*) ; 
 int /*<<< orphan*/  PM_QOS_CPU_DMA_LATENCY ; 
 int /*<<< orphan*/  PM_QOS_DEFAULT_VALUE ; 
 scalar_t__ drm_core_check_feature (struct drm_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen6_pm_rps_work ; 
 int /*<<< orphan*/  gm45_get_vblank_counter ; 
 int /*<<< orphan*/  i8xx_irq_handler ; 
 int /*<<< orphan*/  i8xx_irq_postinstall ; 
 void* i8xx_irq_preinstall ; 
 void* i8xx_irq_uninstall ; 
 int /*<<< orphan*/  i915_disable_vblank ; 
 int /*<<< orphan*/  i915_enable_vblank ; 
 int /*<<< orphan*/  i915_error_work_func ; 
 int /*<<< orphan*/  i915_get_crtc_scanoutpos ; 
 int /*<<< orphan*/  i915_get_vblank_counter ; 
 int /*<<< orphan*/ * i915_get_vblank_timestamp ; 
 int /*<<< orphan*/  i915_hangcheck_elapsed ; 
 int /*<<< orphan*/  i915_hotplug_work_func ; 
 int /*<<< orphan*/  i915_hpd_irq_setup ; 
 int /*<<< orphan*/  i915_irq_handler ; 
 int /*<<< orphan*/  i915_irq_postinstall ; 
 void* i915_irq_preinstall ; 
 void* i915_irq_uninstall ; 
 int /*<<< orphan*/  i965_hpd_irq_setup ; 
 int /*<<< orphan*/  i965_irq_handler ; 
 int /*<<< orphan*/  i965_irq_postinstall ; 
 void* i965_irq_preinstall ; 
 void* i965_irq_uninstall ; 
 int /*<<< orphan*/  ironlake_disable_vblank ; 
 int /*<<< orphan*/  ironlake_enable_vblank ; 
 int /*<<< orphan*/  ironlake_irq_handler ; 
 int /*<<< orphan*/  ironlake_irq_postinstall ; 
 void* ironlake_irq_preinstall ; 
 void* ironlake_irq_uninstall ; 
 int /*<<< orphan*/  ivybridge_disable_vblank ; 
 int /*<<< orphan*/  ivybridge_enable_vblank ; 
 int /*<<< orphan*/  ivybridge_irq_handler ; 
 int /*<<< orphan*/  ivybridge_irq_postinstall ; 
 int /*<<< orphan*/  ivybridge_parity_work ; 
 int /*<<< orphan*/  pm_qos_add_request (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setup_timer (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  valleyview_disable_vblank ; 
 int /*<<< orphan*/  valleyview_enable_vblank ; 
 int /*<<< orphan*/  valleyview_hpd_irq_setup ; 
 int /*<<< orphan*/  valleyview_irq_handler ; 
 int /*<<< orphan*/  valleyview_irq_postinstall ; 
 void* valleyview_irq_preinstall ; 
 void* valleyview_irq_uninstall ; 

void intel_irq_init(struct drm_device *dev)
{
	struct drm_i915_private *dev_priv = dev->dev_private;

	INIT_WORK(&dev_priv->hotplug_work, i915_hotplug_work_func);
	INIT_WORK(&dev_priv->gpu_error.work, i915_error_work_func);
	INIT_WORK(&dev_priv->rps.work, gen6_pm_rps_work);
	INIT_WORK(&dev_priv->l3_parity.error_work, ivybridge_parity_work);

	setup_timer(&dev_priv->gpu_error.hangcheck_timer,
		    i915_hangcheck_elapsed,
		    (unsigned long) dev);

	pm_qos_add_request(&dev_priv->pm_qos, PM_QOS_CPU_DMA_LATENCY, PM_QOS_DEFAULT_VALUE);

	dev->driver->get_vblank_counter = i915_get_vblank_counter;
	dev->max_vblank_count = 0xffffff; /* only 24 bits of frame count */
	if (IS_G4X(dev) || INTEL_INFO(dev)->gen >= 5) {
		dev->max_vblank_count = 0xffffffff; /* full 32 bit counter */
		dev->driver->get_vblank_counter = gm45_get_vblank_counter;
	}

	if (drm_core_check_feature(dev, DRIVER_MODESET))
		dev->driver->get_vblank_timestamp = i915_get_vblank_timestamp;
	else
		dev->driver->get_vblank_timestamp = NULL;
	dev->driver->get_scanout_position = i915_get_crtc_scanoutpos;

	if (IS_VALLEYVIEW(dev)) {
		dev->driver->irq_handler = valleyview_irq_handler;
		dev->driver->irq_preinstall = valleyview_irq_preinstall;
		dev->driver->irq_postinstall = valleyview_irq_postinstall;
		dev->driver->irq_uninstall = valleyview_irq_uninstall;
		dev->driver->enable_vblank = valleyview_enable_vblank;
		dev->driver->disable_vblank = valleyview_disable_vblank;
		dev_priv->display.hpd_irq_setup = valleyview_hpd_irq_setup;
	} else if (IS_IVYBRIDGE(dev) || IS_HASWELL(dev)) {
		/* Share pre & uninstall handlers with ILK/SNB */
		dev->driver->irq_handler = ivybridge_irq_handler;
		dev->driver->irq_preinstall = ironlake_irq_preinstall;
		dev->driver->irq_postinstall = ivybridge_irq_postinstall;
		dev->driver->irq_uninstall = ironlake_irq_uninstall;
		dev->driver->enable_vblank = ivybridge_enable_vblank;
		dev->driver->disable_vblank = ivybridge_disable_vblank;
	} else if (HAS_PCH_SPLIT(dev)) {
		dev->driver->irq_handler = ironlake_irq_handler;
		dev->driver->irq_preinstall = ironlake_irq_preinstall;
		dev->driver->irq_postinstall = ironlake_irq_postinstall;
		dev->driver->irq_uninstall = ironlake_irq_uninstall;
		dev->driver->enable_vblank = ironlake_enable_vblank;
		dev->driver->disable_vblank = ironlake_disable_vblank;
	} else {
		if (INTEL_INFO(dev)->gen == 2) {
			dev->driver->irq_preinstall = i8xx_irq_preinstall;
			dev->driver->irq_postinstall = i8xx_irq_postinstall;
			dev->driver->irq_handler = i8xx_irq_handler;
			dev->driver->irq_uninstall = i8xx_irq_uninstall;
		} else if (INTEL_INFO(dev)->gen == 3) {
			dev->driver->irq_preinstall = i915_irq_preinstall;
			dev->driver->irq_postinstall = i915_irq_postinstall;
			dev->driver->irq_uninstall = i915_irq_uninstall;
			dev->driver->irq_handler = i915_irq_handler;
			dev_priv->display.hpd_irq_setup = i915_hpd_irq_setup;
		} else {
			dev->driver->irq_preinstall = i965_irq_preinstall;
			dev->driver->irq_postinstall = i965_irq_postinstall;
			dev->driver->irq_uninstall = i965_irq_uninstall;
			dev->driver->irq_handler = i965_irq_handler;
			dev_priv->display.hpd_irq_setup = i965_hpd_irq_setup;
		}
		dev->driver->enable_vblank = i915_enable_vblank;
		dev->driver->disable_vblank = i915_disable_vblank;
	}
}