#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct intel_ring_buffer {int dummy; } ;
struct TYPE_8__ {TYPE_3__* pwrctx; TYPE_1__* renderctx; } ;
struct TYPE_6__ {int interruptible; } ;
struct drm_i915_private {TYPE_4__ ips; TYPE_2__ mm; struct intel_ring_buffer* ring; } ;
struct drm_device {int /*<<< orphan*/  struct_mutex; struct drm_i915_private* dev_private; } ;
struct TYPE_7__ {int gtt_offset; } ;
struct TYPE_5__ {int gtt_offset; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int I915_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  I915_WRITE (int /*<<< orphan*/ ,int) ; 
 int MI_FLUSH ; 
 int MI_MM_SPACE_GTT ; 
 int MI_NOOP ; 
 int MI_RESTORE_EXT_STATE_EN ; 
 int MI_RESTORE_INHIBIT ; 
 int MI_SAVE_EXT_STATE_EN ; 
 int MI_SET_CONTEXT ; 
 int MI_SUSPEND_FLUSH ; 
 int MI_SUSPEND_FLUSH_EN ; 
 int /*<<< orphan*/  PWRCTXA ; 
 int PWRCTX_EN ; 
 size_t RCS ; 
 int RCX_SW_EXIT ; 
 int /*<<< orphan*/  RSTDBYCTL ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  intel_enable_rc6 (struct drm_device*) ; 
 int /*<<< orphan*/  intel_ring_advance (struct intel_ring_buffer*) ; 
 int intel_ring_begin (struct intel_ring_buffer*,int) ; 
 int /*<<< orphan*/  intel_ring_emit (struct intel_ring_buffer*,int) ; 
 int intel_ring_idle (struct intel_ring_buffer*) ; 
 int ironlake_setup_rc6 (struct drm_device*) ; 
 int /*<<< orphan*/  ironlake_teardown_rc6 (struct drm_device*) ; 
 int /*<<< orphan*/  mutex_is_locked (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ironlake_enable_rc6(struct drm_device *dev)
{
	struct drm_i915_private *dev_priv = dev->dev_private;
	struct intel_ring_buffer *ring = &dev_priv->ring[RCS];
	bool was_interruptible;
	int ret;

	/* rc6 disabled by default due to repeated reports of hanging during
	 * boot and resume.
	 */
	if (!intel_enable_rc6(dev))
		return;

	WARN_ON(!mutex_is_locked(&dev->struct_mutex));

	ret = ironlake_setup_rc6(dev);
	if (ret)
		return;

	was_interruptible = dev_priv->mm.interruptible;
	dev_priv->mm.interruptible = false;

	/*
	 * GPU can automatically power down the render unit if given a page
	 * to save state.
	 */
	ret = intel_ring_begin(ring, 6);
	if (ret) {
		ironlake_teardown_rc6(dev);
		dev_priv->mm.interruptible = was_interruptible;
		return;
	}

	intel_ring_emit(ring, MI_SUSPEND_FLUSH | MI_SUSPEND_FLUSH_EN);
	intel_ring_emit(ring, MI_SET_CONTEXT);
	intel_ring_emit(ring, dev_priv->ips.renderctx->gtt_offset |
			MI_MM_SPACE_GTT |
			MI_SAVE_EXT_STATE_EN |
			MI_RESTORE_EXT_STATE_EN |
			MI_RESTORE_INHIBIT);
	intel_ring_emit(ring, MI_SUSPEND_FLUSH);
	intel_ring_emit(ring, MI_NOOP);
	intel_ring_emit(ring, MI_FLUSH);
	intel_ring_advance(ring);

	/*
	 * Wait for the command parser to advance past MI_SET_CONTEXT. The HW
	 * does an implicit flush, combined with MI_FLUSH above, it should be
	 * safe to assume that renderctx is valid
	 */
	ret = intel_ring_idle(ring);
	dev_priv->mm.interruptible = was_interruptible;
	if (ret) {
		DRM_ERROR("failed to enable ironlake power power savings\n");
		ironlake_teardown_rc6(dev);
		return;
	}

	I915_WRITE(PWRCTXA, dev_priv->ips.pwrctx->gtt_offset | PWRCTX_EN);
	I915_WRITE(RSTDBYCTL, I915_READ(RSTDBYCTL) & ~RCX_SW_EXIT);
}