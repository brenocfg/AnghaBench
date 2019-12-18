#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int /*<<< orphan*/  work; int /*<<< orphan*/  hangcheck_timer; } ;
struct TYPE_13__ {scalar_t__ shrink; } ;
struct TYPE_10__ {int gtt_mtrr; int /*<<< orphan*/  retire_work; TYPE_6__ inactive_shrinker; } ;
struct TYPE_9__ {int /*<<< orphan*/  mappable_end; int /*<<< orphan*/  mappable_base; int /*<<< orphan*/  mappable; } ;
struct drm_i915_private {int /*<<< orphan*/  bridge_dev; scalar_t__ slab; int /*<<< orphan*/  pm_qos; int /*<<< orphan*/  wq; int /*<<< orphan*/ * regs; TYPE_3__ gpu_error; scalar_t__ child_dev_num; struct drm_i915_private* child_dev; int /*<<< orphan*/  console_resume_work; TYPE_2__ mm; TYPE_1__ gtt; } ;
struct drm_device {struct drm_i915_private* dev_private; TYPE_4__* pdev; int /*<<< orphan*/  struct_mutex; } ;
struct TYPE_12__ {scalar_t__ msi_enabled; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRIVER_MODESET ; 
 int /*<<< orphan*/  DRM_ERROR (char*,int) ; 
 int /*<<< orphan*/  I915_NEED_GFX_HWS (struct drm_device*) ; 
 int /*<<< orphan*/  acpi_video_unregister () ; 
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  destroy_workqueue (int /*<<< orphan*/ ) ; 
 scalar_t__ drm_core_check_feature (struct drm_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  flush_workqueue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i915_destroy_error_state (struct drm_device*) ; 
 int /*<<< orphan*/  i915_free_hws (struct drm_device*) ; 
 int /*<<< orphan*/  i915_gem_cleanup_aliasing_ppgtt (struct drm_device*) ; 
 int /*<<< orphan*/  i915_gem_cleanup_ringbuffer (struct drm_device*) ; 
 int /*<<< orphan*/  i915_gem_cleanup_stolen (struct drm_device*) ; 
 int /*<<< orphan*/  i915_gem_context_fini (struct drm_device*) ; 
 int /*<<< orphan*/  i915_gem_free_all_phys_object (struct drm_device*) ; 
 int /*<<< orphan*/  i915_gem_retire_requests (struct drm_device*) ; 
 int i915_gpu_idle (struct drm_device*) ; 
 int /*<<< orphan*/  i915_teardown_sysfs (struct drm_device*) ; 
 int /*<<< orphan*/  intel_fbdev_fini (struct drm_device*) ; 
 int /*<<< orphan*/  intel_gpu_ips_teardown () ; 
 int /*<<< orphan*/  intel_modeset_cleanup (struct drm_device*) ; 
 int /*<<< orphan*/  intel_opregion_fini (struct drm_device*) ; 
 int /*<<< orphan*/  intel_teardown_gmbus (struct drm_device*) ; 
 int /*<<< orphan*/  intel_teardown_mchbar (struct drm_device*) ; 
 int /*<<< orphan*/  io_mapping_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct drm_i915_private*) ; 
 int /*<<< orphan*/  kmem_cache_destroy (scalar_t__) ; 
 int /*<<< orphan*/  mtrr_del (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_dev_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_disable_msi (TYPE_4__*) ; 
 int /*<<< orphan*/  pci_iounmap (TYPE_4__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_qos_remove_request (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unregister_shrinker (TYPE_6__*) ; 
 int /*<<< orphan*/  vga_client_register (TYPE_4__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vga_switcheroo_unregister_client (TYPE_4__*) ; 

int i915_driver_unload(struct drm_device *dev)
{
	struct drm_i915_private *dev_priv = dev->dev_private;
	int ret;

	intel_gpu_ips_teardown();

	i915_teardown_sysfs(dev);

	if (dev_priv->mm.inactive_shrinker.shrink)
		unregister_shrinker(&dev_priv->mm.inactive_shrinker);

	mutex_lock(&dev->struct_mutex);
	ret = i915_gpu_idle(dev);
	if (ret)
		DRM_ERROR("failed to idle hardware: %d\n", ret);
	i915_gem_retire_requests(dev);
	mutex_unlock(&dev->struct_mutex);

	/* Cancel the retire work handler, which should be idle now. */
	cancel_delayed_work_sync(&dev_priv->mm.retire_work);

	io_mapping_free(dev_priv->gtt.mappable);
	if (dev_priv->mm.gtt_mtrr >= 0) {
		mtrr_del(dev_priv->mm.gtt_mtrr,
			 dev_priv->gtt.mappable_base,
			 dev_priv->gtt.mappable_end);
		dev_priv->mm.gtt_mtrr = -1;
	}

	acpi_video_unregister();

	if (drm_core_check_feature(dev, DRIVER_MODESET)) {
		intel_fbdev_fini(dev);
		intel_modeset_cleanup(dev);
		cancel_work_sync(&dev_priv->console_resume_work);

		/*
		 * free the memory space allocated for the child device
		 * config parsed from VBT
		 */
		if (dev_priv->child_dev && dev_priv->child_dev_num) {
			kfree(dev_priv->child_dev);
			dev_priv->child_dev = NULL;
			dev_priv->child_dev_num = 0;
		}

		vga_switcheroo_unregister_client(dev->pdev);
		vga_client_register(dev->pdev, NULL, NULL, NULL);
	}

	/* Free error state after interrupts are fully disabled. */
	del_timer_sync(&dev_priv->gpu_error.hangcheck_timer);
	cancel_work_sync(&dev_priv->gpu_error.work);
	i915_destroy_error_state(dev);

	if (dev->pdev->msi_enabled)
		pci_disable_msi(dev->pdev);

	intel_opregion_fini(dev);

	if (drm_core_check_feature(dev, DRIVER_MODESET)) {
		/* Flush any outstanding unpin_work. */
		flush_workqueue(dev_priv->wq);

		mutex_lock(&dev->struct_mutex);
		i915_gem_free_all_phys_object(dev);
		i915_gem_cleanup_ringbuffer(dev);
		i915_gem_context_fini(dev);
		mutex_unlock(&dev->struct_mutex);
		i915_gem_cleanup_aliasing_ppgtt(dev);
		i915_gem_cleanup_stolen(dev);

		if (!I915_NEED_GFX_HWS(dev))
			i915_free_hws(dev);
	}

	if (dev_priv->regs != NULL)
		pci_iounmap(dev->pdev, dev_priv->regs);

	intel_teardown_gmbus(dev);
	intel_teardown_mchbar(dev);

	destroy_workqueue(dev_priv->wq);
	pm_qos_remove_request(&dev_priv->pm_qos);

	if (dev_priv->slab)
		kmem_cache_destroy(dev_priv->slab);

	pci_dev_put(dev_priv->bridge_dev);
	kfree(dev->dev_private);

	return 0;
}