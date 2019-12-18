#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct intel_device_info {int gen; } ;
struct TYPE_14__ {int /*<<< orphan*/  (* gtt_remove ) (struct drm_device*) ;int /*<<< orphan*/ * mappable; int /*<<< orphan*/  mappable_base; int /*<<< orphan*/  mappable_end; } ;
struct TYPE_15__ {scalar_t__ shrink; } ;
struct TYPE_13__ {int suspended; int gtt_mtrr; TYPE_5__ inactive_shrinker; } ;
struct TYPE_12__ {int /*<<< orphan*/  hw_lock; int /*<<< orphan*/  lock; } ;
struct TYPE_11__ {int /*<<< orphan*/  lock; } ;
struct drm_i915_private {int num_pipe; int /*<<< orphan*/  bridge_dev; TYPE_4__ gtt; int /*<<< orphan*/  regs; TYPE_3__ mm; int /*<<< orphan*/ * wq; int /*<<< orphan*/  modeset_restore_lock; TYPE_2__ rps; int /*<<< orphan*/  dpio_lock; TYPE_1__ gpu_error; int /*<<< orphan*/  irq_lock; struct intel_device_info* info; struct drm_device* dev; } ;
struct drm_device {int counters; TYPE_6__* pdev; void* dev_private; int /*<<< orphan*/ * types; } ;
typedef  int /*<<< orphan*/  drm_i915_private_t ;
struct TYPE_16__ {scalar_t__ msi_enabled; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_BIT_MASK (int) ; 
 int /*<<< orphan*/  DRIVER_MODESET ; 
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int EIO ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_BROADWATER (struct drm_device*) ; 
 scalar_t__ IS_CRESTLINE (struct drm_device*) ; 
 scalar_t__ IS_GEN2 (struct drm_device*) ; 
 scalar_t__ IS_GEN5 (struct drm_device*) ; 
 scalar_t__ IS_HASWELL (struct drm_device*) ; 
 int /*<<< orphan*/  IS_I945G (struct drm_device*) ; 
 int /*<<< orphan*/  IS_I945GM (struct drm_device*) ; 
 scalar_t__ IS_IVYBRIDGE (struct drm_device*) ; 
 scalar_t__ IS_MOBILE (struct drm_device*) ; 
 int /*<<< orphan*/  _DRM_STAT_DMA ; 
 int /*<<< orphan*/  _DRM_STAT_IRQ ; 
 int /*<<< orphan*/  _DRM_STAT_PRIMARY ; 
 int /*<<< orphan*/  _DRM_STAT_SECONDARY ; 
 int /*<<< orphan*/  acpi_video_register () ; 
 int /*<<< orphan*/ * alloc_ordered_workqueue (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  destroy_workqueue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dma_set_coherent_mask (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ drm_core_check_feature (struct drm_device*,int /*<<< orphan*/ ) ; 
 int drm_vblank_init (struct drm_device*,int) ; 
 int /*<<< orphan*/  i915_dump_device_info (struct drm_i915_private*) ; 
 int i915_gem_gtt_init (struct drm_device*) ; 
 int /*<<< orphan*/  i915_gem_load (struct drm_device*) ; 
 scalar_t__ i915_get_bridge_dev (struct drm_device*) ; 
 int /*<<< orphan*/  i915_kick_out_firmware_fb (struct drm_i915_private*) ; 
 int i915_load_modeset_init (struct drm_device*) ; 
 int /*<<< orphan*/  i915_mtrr_setup (struct drm_i915_private*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i915_setup_sysfs (struct drm_device*) ; 
 int /*<<< orphan*/  intel_detect_pch (struct drm_device*) ; 
 int /*<<< orphan*/  intel_gpu_ips_init (struct drm_i915_private*) ; 
 int /*<<< orphan*/  intel_gt_init (struct drm_device*) ; 
 int /*<<< orphan*/  intel_irq_init (struct drm_device*) ; 
 int /*<<< orphan*/  intel_opregion_init (struct drm_device*) ; 
 int /*<<< orphan*/  intel_opregion_setup (struct drm_device*) ; 
 int /*<<< orphan*/  intel_setup_bios (struct drm_device*) ; 
 int /*<<< orphan*/  intel_setup_gmbus (struct drm_device*) ; 
 int /*<<< orphan*/  intel_setup_mchbar (struct drm_device*) ; 
 int /*<<< orphan*/  intel_teardown_gmbus (struct drm_device*) ; 
 int /*<<< orphan*/  intel_teardown_mchbar (struct drm_device*) ; 
 int /*<<< orphan*/ * io_mapping_create_wc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  io_mapping_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct drm_i915_private*) ; 
 struct drm_i915_private* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtrr_del (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_dev_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_disable_msi (TYPE_6__*) ; 
 int /*<<< orphan*/  pci_enable_msi (TYPE_6__*) ; 
 int /*<<< orphan*/  pci_iomap (TYPE_6__*,int,int) ; 
 int /*<<< orphan*/  pci_iounmap (TYPE_6__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_set_master (TYPE_6__*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct drm_device*) ; 
 int /*<<< orphan*/  unregister_shrinker (TYPE_5__*) ; 

int i915_driver_load(struct drm_device *dev, unsigned long flags)
{
	struct drm_i915_private *dev_priv;
	struct intel_device_info *info;
	int ret = 0, mmio_bar, mmio_size;
	uint32_t aperture_size;

	info = (struct intel_device_info *) flags;

	/* Refuse to load on gen6+ without kms enabled. */
	if (info->gen >= 6 && !drm_core_check_feature(dev, DRIVER_MODESET))
		return -ENODEV;

	/* i915 has 4 more counters */
	dev->counters += 4;
	dev->types[6] = _DRM_STAT_IRQ;
	dev->types[7] = _DRM_STAT_PRIMARY;
	dev->types[8] = _DRM_STAT_SECONDARY;
	dev->types[9] = _DRM_STAT_DMA;

	dev_priv = kzalloc(sizeof(drm_i915_private_t), GFP_KERNEL);
	if (dev_priv == NULL)
		return -ENOMEM;

	dev->dev_private = (void *)dev_priv;
	dev_priv->dev = dev;
	dev_priv->info = info;

	i915_dump_device_info(dev_priv);

	if (i915_get_bridge_dev(dev)) {
		ret = -EIO;
		goto free_priv;
	}

	ret = i915_gem_gtt_init(dev);
	if (ret)
		goto put_bridge;

	if (drm_core_check_feature(dev, DRIVER_MODESET))
		i915_kick_out_firmware_fb(dev_priv);

	pci_set_master(dev->pdev);

	/* overlay on gen2 is broken and can't address above 1G */
	if (IS_GEN2(dev))
		dma_set_coherent_mask(&dev->pdev->dev, DMA_BIT_MASK(30));

	/* 965GM sometimes incorrectly writes to hardware status page (HWS)
	 * using 32bit addressing, overwriting memory if HWS is located
	 * above 4GB.
	 *
	 * The documentation also mentions an issue with undefined
	 * behaviour if any general state is accessed within a page above 4GB,
	 * which also needs to be handled carefully.
	 */
	if (IS_BROADWATER(dev) || IS_CRESTLINE(dev))
		dma_set_coherent_mask(&dev->pdev->dev, DMA_BIT_MASK(32));

	mmio_bar = IS_GEN2(dev) ? 1 : 0;
	/* Before gen4, the registers and the GTT are behind different BARs.
	 * However, from gen4 onwards, the registers and the GTT are shared
	 * in the same BAR, so we want to restrict this ioremap from
	 * clobbering the GTT which we want ioremap_wc instead. Fortunately,
	 * the register BAR remains the same size for all the earlier
	 * generations up to Ironlake.
	 */
	if (info->gen < 5)
		mmio_size = 512*1024;
	else
		mmio_size = 2*1024*1024;

	dev_priv->regs = pci_iomap(dev->pdev, mmio_bar, mmio_size);
	if (!dev_priv->regs) {
		DRM_ERROR("failed to map registers\n");
		ret = -EIO;
		goto put_gmch;
	}

	aperture_size = dev_priv->gtt.mappable_end;

	dev_priv->gtt.mappable =
		io_mapping_create_wc(dev_priv->gtt.mappable_base,
				     aperture_size);
	if (dev_priv->gtt.mappable == NULL) {
		ret = -EIO;
		goto out_rmmap;
	}

	i915_mtrr_setup(dev_priv, dev_priv->gtt.mappable_base,
			aperture_size);

	/* The i915 workqueue is primarily used for batched retirement of
	 * requests (and thus managing bo) once the task has been completed
	 * by the GPU. i915_gem_retire_requests() is called directly when we
	 * need high-priority retirement, such as waiting for an explicit
	 * bo.
	 *
	 * It is also used for periodic low-priority events, such as
	 * idle-timers and recording error state.
	 *
	 * All tasks on the workqueue are expected to acquire the dev mutex
	 * so there is no point in running more than one instance of the
	 * workqueue at any time.  Use an ordered one.
	 */
	dev_priv->wq = alloc_ordered_workqueue("i915", 0);
	if (dev_priv->wq == NULL) {
		DRM_ERROR("Failed to create our workqueue.\n");
		ret = -ENOMEM;
		goto out_mtrrfree;
	}

	/* This must be called before any calls to HAS_PCH_* */
	intel_detect_pch(dev);

	intel_irq_init(dev);
	intel_gt_init(dev);

	/* Try to make sure MCHBAR is enabled before poking at it */
	intel_setup_mchbar(dev);
	intel_setup_gmbus(dev);
	intel_opregion_setup(dev);

	intel_setup_bios(dev);

	i915_gem_load(dev);

	/* On the 945G/GM, the chipset reports the MSI capability on the
	 * integrated graphics even though the support isn't actually there
	 * according to the published specs.  It doesn't appear to function
	 * correctly in testing on 945G.
	 * This may be a side effect of MSI having been made available for PEG
	 * and the registers being closely associated.
	 *
	 * According to chipset errata, on the 965GM, MSI interrupts may
	 * be lost or delayed, but we use them anyways to avoid
	 * stuck interrupts on some machines.
	 */
	if (!IS_I945G(dev) && !IS_I945GM(dev))
		pci_enable_msi(dev->pdev);

	spin_lock_init(&dev_priv->irq_lock);
	spin_lock_init(&dev_priv->gpu_error.lock);
	spin_lock_init(&dev_priv->rps.lock);
	mutex_init(&dev_priv->dpio_lock);

	mutex_init(&dev_priv->rps.hw_lock);
	mutex_init(&dev_priv->modeset_restore_lock);

	if (IS_IVYBRIDGE(dev) || IS_HASWELL(dev))
		dev_priv->num_pipe = 3;
	else if (IS_MOBILE(dev) || !IS_GEN2(dev))
		dev_priv->num_pipe = 2;
	else
		dev_priv->num_pipe = 1;

	ret = drm_vblank_init(dev, dev_priv->num_pipe);
	if (ret)
		goto out_gem_unload;

	/* Start out suspended */
	dev_priv->mm.suspended = 1;

	if (drm_core_check_feature(dev, DRIVER_MODESET)) {
		ret = i915_load_modeset_init(dev);
		if (ret < 0) {
			DRM_ERROR("failed to init modeset\n");
			goto out_gem_unload;
		}
	}

	i915_setup_sysfs(dev);

	/* Must be done after probing outputs */
	intel_opregion_init(dev);
	acpi_video_register();

	if (IS_GEN5(dev))
		intel_gpu_ips_init(dev_priv);

	return 0;

out_gem_unload:
	if (dev_priv->mm.inactive_shrinker.shrink)
		unregister_shrinker(&dev_priv->mm.inactive_shrinker);

	if (dev->pdev->msi_enabled)
		pci_disable_msi(dev->pdev);

	intel_teardown_gmbus(dev);
	intel_teardown_mchbar(dev);
	destroy_workqueue(dev_priv->wq);
out_mtrrfree:
	if (dev_priv->mm.gtt_mtrr >= 0) {
		mtrr_del(dev_priv->mm.gtt_mtrr,
			 dev_priv->gtt.mappable_base,
			 aperture_size);
		dev_priv->mm.gtt_mtrr = -1;
	}
	io_mapping_free(dev_priv->gtt.mappable);
out_rmmap:
	pci_iounmap(dev->pdev, dev_priv->regs);
put_gmch:
	dev_priv->gtt.gtt_remove(dev);
put_bridge:
	pci_dev_put(dev_priv->bridge_dev);
free_priv:
	kfree(dev_priv);
	return ret;
}