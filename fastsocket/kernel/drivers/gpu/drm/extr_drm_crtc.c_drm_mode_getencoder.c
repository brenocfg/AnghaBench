#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct drm_mode_object {int dummy; } ;
struct drm_mode_get_encoder {int /*<<< orphan*/  possible_clones; int /*<<< orphan*/  possible_crtcs; int /*<<< orphan*/  encoder_id; int /*<<< orphan*/  encoder_type; scalar_t__ crtc_id; } ;
struct drm_file {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  id; } ;
struct drm_encoder {int /*<<< orphan*/  possible_clones; int /*<<< orphan*/  possible_crtcs; TYPE_3__ base; int /*<<< orphan*/  encoder_type; TYPE_2__* crtc; } ;
struct drm_device {int dummy; } ;
struct TYPE_4__ {scalar_t__ id; } ;
struct TYPE_5__ {TYPE_1__ base; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRIVER_MODESET ; 
 int /*<<< orphan*/  DRM_MODE_OBJECT_ENCODER ; 
 int EINVAL ; 
 int /*<<< orphan*/  drm_core_check_feature (struct drm_device*,int /*<<< orphan*/ ) ; 
 struct drm_mode_object* drm_mode_object_find (struct drm_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_modeset_lock_all (struct drm_device*) ; 
 int /*<<< orphan*/  drm_modeset_unlock_all (struct drm_device*) ; 
 struct drm_encoder* obj_to_encoder (struct drm_mode_object*) ; 

int drm_mode_getencoder(struct drm_device *dev, void *data,
			struct drm_file *file_priv)
{
	struct drm_mode_get_encoder *enc_resp = data;
	struct drm_mode_object *obj;
	struct drm_encoder *encoder;
	int ret = 0;

	if (!drm_core_check_feature(dev, DRIVER_MODESET))
		return -EINVAL;

	drm_modeset_lock_all(dev);
	obj = drm_mode_object_find(dev, enc_resp->encoder_id,
				   DRM_MODE_OBJECT_ENCODER);
	if (!obj) {
		ret = -EINVAL;
		goto out;
	}
	encoder = obj_to_encoder(obj);

	if (encoder->crtc)
		enc_resp->crtc_id = encoder->crtc->base.id;
	else
		enc_resp->crtc_id = 0;
	enc_resp->encoder_type = encoder->encoder_type;
	enc_resp->encoder_id = encoder->base.id;
	enc_resp->possible_crtcs = encoder->possible_crtcs;
	enc_resp->possible_clones = encoder->possible_clones;

out:
	drm_modeset_unlock_all(dev);
	return ret;
}