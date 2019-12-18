#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct drm_i915_private {int dummy; } ;
struct drm_device {struct drm_i915_private* dev_private; } ;
struct drm_clip_rect {int dummy; } ;
struct TYPE_4__ {int num_cliprects; int start; int used; int /*<<< orphan*/  DR4; int /*<<< orphan*/  DR1; } ;
typedef  TYPE_1__ drm_i915_batchbuffer_t ;
struct TYPE_5__ {int gen; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADVANCE_LP_RING () ; 
 int BEGIN_LP_RING (int) ; 
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int EINVAL ; 
 TYPE_3__* INTEL_INFO (struct drm_device*) ; 
 int /*<<< orphan*/  IS_845G (struct drm_device*) ; 
 scalar_t__ IS_G4X (struct drm_device*) ; 
 scalar_t__ IS_GEN5 (struct drm_device*) ; 
 int /*<<< orphan*/  IS_I830 (struct drm_device*) ; 
 int MI_BATCH_BUFFER ; 
 int MI_BATCH_BUFFER_START ; 
 int MI_BATCH_NON_SECURE ; 
 int MI_BATCH_NON_SECURE_I965 ; 
 int MI_FLUSH ; 
 int MI_INVALIDATE_ISP ; 
 int MI_NOOP ; 
 int MI_NO_WRITE_FLUSH ; 
 int /*<<< orphan*/  OUT_RING (int) ; 
 int i915_emit_box (struct drm_device*,struct drm_clip_rect*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i915_emit_breadcrumb (struct drm_device*) ; 
 int /*<<< orphan*/  i915_kernel_lost_context (struct drm_device*) ; 

__attribute__((used)) static int i915_dispatch_batchbuffer(struct drm_device * dev,
				     drm_i915_batchbuffer_t * batch,
				     struct drm_clip_rect *cliprects)
{
	struct drm_i915_private *dev_priv = dev->dev_private;
	int nbox = batch->num_cliprects;
	int i, count, ret;

	if ((batch->start | batch->used) & 0x7) {
		DRM_ERROR("alignment");
		return -EINVAL;
	}

	i915_kernel_lost_context(dev);

	count = nbox ? nbox : 1;
	for (i = 0; i < count; i++) {
		if (i < nbox) {
			ret = i915_emit_box(dev, &cliprects[i],
					    batch->DR1, batch->DR4);
			if (ret)
				return ret;
		}

		if (!IS_I830(dev) && !IS_845G(dev)) {
			ret = BEGIN_LP_RING(2);
			if (ret)
				return ret;

			if (INTEL_INFO(dev)->gen >= 4) {
				OUT_RING(MI_BATCH_BUFFER_START | (2 << 6) | MI_BATCH_NON_SECURE_I965);
				OUT_RING(batch->start);
			} else {
				OUT_RING(MI_BATCH_BUFFER_START | (2 << 6));
				OUT_RING(batch->start | MI_BATCH_NON_SECURE);
			}
		} else {
			ret = BEGIN_LP_RING(4);
			if (ret)
				return ret;

			OUT_RING(MI_BATCH_BUFFER);
			OUT_RING(batch->start | MI_BATCH_NON_SECURE);
			OUT_RING(batch->start + batch->used - 4);
			OUT_RING(0);
		}
		ADVANCE_LP_RING();
	}


	if (IS_G4X(dev) || IS_GEN5(dev)) {
		if (BEGIN_LP_RING(2) == 0) {
			OUT_RING(MI_FLUSH | MI_NO_WRITE_FLUSH | MI_INVALIDATE_ISP);
			OUT_RING(MI_NOOP);
			ADVANCE_LP_RING();
		}
	}

	i915_emit_breadcrumb(dev);
	return 0;
}