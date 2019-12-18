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
typedef  int u16 ;
struct radeon_encoder {int encoder_id; } ;
struct drm_mode_object {int dummy; } ;
struct drm_encoder {int dummy; } ;
struct drm_connector {scalar_t__* encoder_ids; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int DRM_CONNECTOR_MAX_ENCODER ; 
 int /*<<< orphan*/  DRM_MODE_OBJECT_ENCODER ; 
 int ENCODER_OBJECT_ID_NONE ; 
#define  ENCODER_OBJECT_ID_NUTMEG 129 
#define  ENCODER_OBJECT_ID_TRAVIS 128 
 struct drm_mode_object* drm_mode_object_find (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 struct drm_encoder* obj_to_encoder (struct drm_mode_object*) ; 
 struct radeon_encoder* to_radeon_encoder (struct drm_encoder*) ; 

u16 radeon_connector_encoder_get_dp_bridge_encoder_id(struct drm_connector *connector)
{
	struct drm_mode_object *obj;
	struct drm_encoder *encoder;
	struct radeon_encoder *radeon_encoder;
	int i;

	for (i = 0; i < DRM_CONNECTOR_MAX_ENCODER; i++) {
		if (connector->encoder_ids[i] == 0)
			break;

		obj = drm_mode_object_find(connector->dev, connector->encoder_ids[i], DRM_MODE_OBJECT_ENCODER);
		if (!obj)
			continue;

		encoder = obj_to_encoder(obj);
		radeon_encoder = to_radeon_encoder(encoder);

		switch (radeon_encoder->encoder_id) {
		case ENCODER_OBJECT_ID_TRAVIS:
		case ENCODER_OBJECT_ID_NUTMEG:
			return radeon_encoder->encoder_id;
		default:
			break;
		}
	}

	return ENCODER_OBJECT_ID_NONE;
}