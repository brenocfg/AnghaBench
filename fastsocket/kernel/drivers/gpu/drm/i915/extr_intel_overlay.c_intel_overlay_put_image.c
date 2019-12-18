#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct put_image_params {int dst_y; int dst_h; scalar_t__ src_w; scalar_t__ src_h; scalar_t__ src_scan_w; scalar_t__ src_scan_h; int format; int /*<<< orphan*/  offset_V; int /*<<< orphan*/  offset_U; int /*<<< orphan*/  offset_Y; int /*<<< orphan*/  stride_UV; int /*<<< orphan*/  stride_Y; int /*<<< orphan*/  dst_w; int /*<<< orphan*/  dst_x; } ;
struct intel_overlay {int pfit_active; int pfit_vscale_ratio; struct intel_crtc* crtc; } ;
struct drm_display_mode {int hdisplay; } ;
struct TYPE_3__ {struct drm_display_mode mode; } ;
struct intel_crtc {scalar_t__ pipe; struct intel_overlay* overlay; TYPE_1__ base; } ;
struct drm_mode_object {int dummy; } ;
struct drm_intel_overlay_put_image {int flags; int dst_y; int dst_height; scalar_t__ src_width; scalar_t__ src_height; scalar_t__ src_scan_width; scalar_t__ src_scan_height; int /*<<< orphan*/  offset_V; int /*<<< orphan*/  offset_U; int /*<<< orphan*/  offset_Y; int /*<<< orphan*/  stride_UV; int /*<<< orphan*/  stride_Y; int /*<<< orphan*/  dst_width; int /*<<< orphan*/  dst_x; int /*<<< orphan*/  bo_handle; int /*<<< orphan*/  crtc_id; } ;
struct drm_i915_gem_object {int /*<<< orphan*/  base; scalar_t__ tiling_mode; } ;
struct drm_file {int dummy; } ;
struct drm_device {int /*<<< orphan*/  struct_mutex; TYPE_2__* dev_private; } ;
struct TYPE_4__ {struct intel_overlay* overlay; } ;
typedef  TYPE_2__ drm_i915_private_t ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG (char*) ; 
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int /*<<< orphan*/  DRM_MODE_OBJECT_CRTC ; 
 int EINVAL ; 
 int ENODEV ; 
 int ENOENT ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int I915_OVERLAY_ENABLE ; 
 int I915_OVERLAY_FLAGS_MASK ; 
 int check_overlay_dst (struct intel_overlay*,struct drm_intel_overlay_put_image*) ; 
 int check_overlay_possible_on_crtc (struct intel_overlay*,struct intel_crtc*) ; 
 int check_overlay_scaling (struct put_image_params*) ; 
 int check_overlay_src (struct drm_device*,struct drm_intel_overlay_put_image*,struct drm_i915_gem_object*) ; 
 int /*<<< orphan*/  drm_gem_object_lookup (struct drm_device*,struct drm_file*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_gem_object_unreference_unlocked (int /*<<< orphan*/ *) ; 
 struct drm_mode_object* drm_mode_object_find (struct drm_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_modeset_lock_all (struct drm_device*) ; 
 int /*<<< orphan*/  drm_modeset_unlock_all (struct drm_device*) ; 
 int intel_overlay_do_put_image (struct intel_overlay*,struct drm_i915_gem_object*,struct put_image_params*) ; 
 int intel_overlay_recover_from_interrupt (struct intel_overlay*) ; 
 int intel_overlay_switch_off (struct intel_overlay*) ; 
 scalar_t__ intel_panel_fitter_pipe (struct drm_device*) ; 
 int /*<<< orphan*/  kfree (struct put_image_params*) ; 
 struct put_image_params* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  obj_to_crtc (struct drm_mode_object*) ; 
 struct drm_i915_gem_object* to_intel_bo (int /*<<< orphan*/ ) ; 
 struct intel_crtc* to_intel_crtc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  update_pfit_vscale_ratio (struct intel_overlay*) ; 

int intel_overlay_put_image(struct drm_device *dev, void *data,
			    struct drm_file *file_priv)
{
	struct drm_intel_overlay_put_image *put_image_rec = data;
	drm_i915_private_t *dev_priv = dev->dev_private;
	struct intel_overlay *overlay;
	struct drm_mode_object *drmmode_obj;
	struct intel_crtc *crtc;
	struct drm_i915_gem_object *new_bo;
	struct put_image_params *params;
	int ret;

	/* No need to check for DRIVER_MODESET - we don't set it up then. */
	overlay = dev_priv->overlay;
	if (!overlay) {
		DRM_DEBUG("userspace bug: no overlay\n");
		return -ENODEV;
	}

	if (!(put_image_rec->flags & I915_OVERLAY_ENABLE)) {
		drm_modeset_lock_all(dev);
		mutex_lock(&dev->struct_mutex);

		ret = intel_overlay_switch_off(overlay);

		mutex_unlock(&dev->struct_mutex);
		drm_modeset_unlock_all(dev);

		return ret;
	}

	params = kmalloc(sizeof(struct put_image_params), GFP_KERNEL);
	if (!params)
		return -ENOMEM;

	drmmode_obj = drm_mode_object_find(dev, put_image_rec->crtc_id,
					   DRM_MODE_OBJECT_CRTC);
	if (!drmmode_obj) {
		ret = -ENOENT;
		goto out_free;
	}
	crtc = to_intel_crtc(obj_to_crtc(drmmode_obj));

	new_bo = to_intel_bo(drm_gem_object_lookup(dev, file_priv,
						   put_image_rec->bo_handle));
	if (&new_bo->base == NULL) {
		ret = -ENOENT;
		goto out_free;
	}

	drm_modeset_lock_all(dev);
	mutex_lock(&dev->struct_mutex);

	if (new_bo->tiling_mode) {
		DRM_ERROR("buffer used for overlay image can not be tiled\n");
		ret = -EINVAL;
		goto out_unlock;
	}

	ret = intel_overlay_recover_from_interrupt(overlay);
	if (ret != 0)
		goto out_unlock;

	if (overlay->crtc != crtc) {
		struct drm_display_mode *mode = &crtc->base.mode;
		ret = intel_overlay_switch_off(overlay);
		if (ret != 0)
			goto out_unlock;

		ret = check_overlay_possible_on_crtc(overlay, crtc);
		if (ret != 0)
			goto out_unlock;

		overlay->crtc = crtc;
		crtc->overlay = overlay;

		/* line too wide, i.e. one-line-mode */
		if (mode->hdisplay > 1024 &&
		    intel_panel_fitter_pipe(dev) == crtc->pipe) {
			overlay->pfit_active = 1;
			update_pfit_vscale_ratio(overlay);
		} else
			overlay->pfit_active = 0;
	}

	ret = check_overlay_dst(overlay, put_image_rec);
	if (ret != 0)
		goto out_unlock;

	if (overlay->pfit_active) {
		params->dst_y = ((((u32)put_image_rec->dst_y) << 12) /
				 overlay->pfit_vscale_ratio);
		/* shifting right rounds downwards, so add 1 */
		params->dst_h = ((((u32)put_image_rec->dst_height) << 12) /
				 overlay->pfit_vscale_ratio) + 1;
	} else {
		params->dst_y = put_image_rec->dst_y;
		params->dst_h = put_image_rec->dst_height;
	}
	params->dst_x = put_image_rec->dst_x;
	params->dst_w = put_image_rec->dst_width;

	params->src_w = put_image_rec->src_width;
	params->src_h = put_image_rec->src_height;
	params->src_scan_w = put_image_rec->src_scan_width;
	params->src_scan_h = put_image_rec->src_scan_height;
	if (params->src_scan_h > params->src_h ||
	    params->src_scan_w > params->src_w) {
		ret = -EINVAL;
		goto out_unlock;
	}

	ret = check_overlay_src(dev, put_image_rec, new_bo);
	if (ret != 0)
		goto out_unlock;
	params->format = put_image_rec->flags & ~I915_OVERLAY_FLAGS_MASK;
	params->stride_Y = put_image_rec->stride_Y;
	params->stride_UV = put_image_rec->stride_UV;
	params->offset_Y = put_image_rec->offset_Y;
	params->offset_U = put_image_rec->offset_U;
	params->offset_V = put_image_rec->offset_V;

	/* Check scaling after src size to prevent a divide-by-zero. */
	ret = check_overlay_scaling(params);
	if (ret != 0)
		goto out_unlock;

	ret = intel_overlay_do_put_image(overlay, new_bo, params);
	if (ret != 0)
		goto out_unlock;

	mutex_unlock(&dev->struct_mutex);
	drm_modeset_unlock_all(dev);

	kfree(params);

	return 0;

out_unlock:
	mutex_unlock(&dev->struct_mutex);
	drm_modeset_unlock_all(dev);
	drm_gem_object_unreference_unlocked(&new_bo->base);
out_free:
	kfree(params);

	return ret;
}