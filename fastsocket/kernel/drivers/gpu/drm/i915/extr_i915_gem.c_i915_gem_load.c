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
struct drm_i915_gem_object {int dummy; } ;
struct drm_device {TYPE_4__* dev_private; } ;
struct TYPE_11__ {int /*<<< orphan*/  seeks; int /*<<< orphan*/  shrink; } ;
struct TYPE_9__ {int interruptible; TYPE_5__ inactive_shrinker; int /*<<< orphan*/  retire_work; int /*<<< orphan*/  fence_list; int /*<<< orphan*/  bound_list; int /*<<< orphan*/  unbound_list; int /*<<< orphan*/  inactive_list; int /*<<< orphan*/  active_list; } ;
struct TYPE_8__ {int /*<<< orphan*/  reset_queue; } ;
struct TYPE_10__ {int fence_reg_start; int num_fence_regs; TYPE_3__ mm; int /*<<< orphan*/  pending_flip_queue; int /*<<< orphan*/  relative_constants_mode; TYPE_2__ gpu_error; TYPE_1__* fence_regs; int /*<<< orphan*/ * ring; int /*<<< orphan*/  slab; } ;
typedef  TYPE_4__ drm_i915_private_t ;
struct TYPE_12__ {int gen; } ;
struct TYPE_7__ {int /*<<< orphan*/  lru_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEFAULT_SEEKS ; 
 int /*<<< orphan*/  DRIVER_MODESET ; 
 int /*<<< orphan*/  I915_EXEC_CONSTANTS_REL_GENERAL ; 
 int I915_MAX_NUM_FENCES ; 
 int I915_NUM_RINGS ; 
 int /*<<< orphan*/  I915_WRITE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 TYPE_6__* INTEL_INFO (struct drm_device*) ; 
 scalar_t__ IS_G33 (struct drm_device*) ; 
 scalar_t__ IS_GEN3 (struct drm_device*) ; 
 scalar_t__ IS_I945G (struct drm_device*) ; 
 scalar_t__ IS_I945GM (struct drm_device*) ; 
 int /*<<< orphan*/  MI_ARB_C3_LP_WRITE_ENABLE ; 
 int /*<<< orphan*/  MI_ARB_STATE ; 
 int /*<<< orphan*/  SLAB_HWCACHE_ALIGN ; 
 int /*<<< orphan*/  _MASKED_BIT_ENABLE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_core_check_feature (struct drm_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i915_gem_detect_bit_6_swizzle (struct drm_device*) ; 
 int /*<<< orphan*/  i915_gem_inactive_shrink ; 
 int /*<<< orphan*/  i915_gem_reset_fences (struct drm_device*) ; 
 int /*<<< orphan*/  i915_gem_retire_work_handler ; 
 int /*<<< orphan*/  init_ring_lists (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kmem_cache_create (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  register_shrinker (TYPE_5__*) ; 

void
i915_gem_load(struct drm_device *dev)
{
	drm_i915_private_t *dev_priv = dev->dev_private;
	int i;

	dev_priv->slab =
		kmem_cache_create("i915_gem_object",
				  sizeof(struct drm_i915_gem_object), 0,
				  SLAB_HWCACHE_ALIGN,
				  NULL);

	INIT_LIST_HEAD(&dev_priv->mm.active_list);
	INIT_LIST_HEAD(&dev_priv->mm.inactive_list);
	INIT_LIST_HEAD(&dev_priv->mm.unbound_list);
	INIT_LIST_HEAD(&dev_priv->mm.bound_list);
	INIT_LIST_HEAD(&dev_priv->mm.fence_list);
	for (i = 0; i < I915_NUM_RINGS; i++)
		init_ring_lists(&dev_priv->ring[i]);
	for (i = 0; i < I915_MAX_NUM_FENCES; i++)
		INIT_LIST_HEAD(&dev_priv->fence_regs[i].lru_list);
	INIT_DELAYED_WORK(&dev_priv->mm.retire_work,
			  i915_gem_retire_work_handler);
	init_waitqueue_head(&dev_priv->gpu_error.reset_queue);

	/* On GEN3 we really need to make sure the ARB C3 LP bit is set */
	if (IS_GEN3(dev)) {
		I915_WRITE(MI_ARB_STATE,
			   _MASKED_BIT_ENABLE(MI_ARB_C3_LP_WRITE_ENABLE));
	}

	dev_priv->relative_constants_mode = I915_EXEC_CONSTANTS_REL_GENERAL;

	/* Old X drivers will take 0-2 for front, back, depth buffers */
	if (!drm_core_check_feature(dev, DRIVER_MODESET))
		dev_priv->fence_reg_start = 3;

	if (INTEL_INFO(dev)->gen >= 4 || IS_I945G(dev) || IS_I945GM(dev) || IS_G33(dev))
		dev_priv->num_fence_regs = 16;
	else
		dev_priv->num_fence_regs = 8;

	/* Initialize fence registers to zero */
	i915_gem_reset_fences(dev);

	i915_gem_detect_bit_6_swizzle(dev);
	init_waitqueue_head(&dev_priv->pending_flip_queue);

	dev_priv->mm.interruptible = true;

	dev_priv->mm.inactive_shrinker.shrink = i915_gem_inactive_shrink;
	dev_priv->mm.inactive_shrinker.seeks = DEFAULT_SEEKS;
	register_shrinker(&dev_priv->mm.inactive_shrinker);
}