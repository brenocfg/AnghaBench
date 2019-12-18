#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct radeon_connector {int use_digital; } ;
struct drm_mode_object {int dummy; } ;
struct drm_encoder {scalar_t__ encoder_type; } ;
struct drm_connector {int* encoder_ids; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int DRM_CONNECTOR_MAX_ENCODER ; 
 scalar_t__ DRM_MODE_ENCODER_DAC ; 
 scalar_t__ DRM_MODE_ENCODER_TMDS ; 
 scalar_t__ DRM_MODE_ENCODER_TVDAC ; 
 int /*<<< orphan*/  DRM_MODE_OBJECT_ENCODER ; 
 struct drm_mode_object* drm_mode_object_find (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 struct drm_encoder* obj_to_encoder (struct drm_mode_object*) ; 
 struct radeon_connector* to_radeon_connector (struct drm_connector*) ; 

__attribute__((used)) static struct drm_encoder *radeon_dvi_encoder(struct drm_connector *connector)
{
	int enc_id = connector->encoder_ids[0];
	struct radeon_connector *radeon_connector = to_radeon_connector(connector);
	struct drm_mode_object *obj;
	struct drm_encoder *encoder;
	int i;
	for (i = 0; i < DRM_CONNECTOR_MAX_ENCODER; i++) {
		if (connector->encoder_ids[i] == 0)
			break;

		obj = drm_mode_object_find(connector->dev, connector->encoder_ids[i], DRM_MODE_OBJECT_ENCODER);
		if (!obj)
			continue;

		encoder = obj_to_encoder(obj);

		if (radeon_connector->use_digital == true) {
			if (encoder->encoder_type == DRM_MODE_ENCODER_TMDS)
				return encoder;
		} else {
			if (encoder->encoder_type == DRM_MODE_ENCODER_DAC ||
			    encoder->encoder_type == DRM_MODE_ENCODER_TVDAC)
				return encoder;
		}
	}

	/* see if we have a default encoder  TODO */

	/* then check use digitial */
	/* pick the first one */
	if (enc_id) {
		obj = drm_mode_object_find(connector->dev, enc_id, DRM_MODE_OBJECT_ENCODER);
		if (!obj)
			return NULL;
		encoder = obj_to_encoder(obj);
		return encoder;
	}
	return NULL;
}