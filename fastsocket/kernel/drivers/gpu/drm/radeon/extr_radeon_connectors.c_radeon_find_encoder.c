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
struct drm_mode_object {int dummy; } ;
struct drm_encoder {int encoder_type; } ;
struct drm_connector {scalar_t__* encoder_ids; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int DRM_CONNECTOR_MAX_ENCODER ; 
 int /*<<< orphan*/  DRM_MODE_OBJECT_ENCODER ; 
 struct drm_mode_object* drm_mode_object_find (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 struct drm_encoder* obj_to_encoder (struct drm_mode_object*) ; 

__attribute__((used)) static struct drm_encoder *radeon_find_encoder(struct drm_connector *connector, int encoder_type)
{
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
		if (encoder->encoder_type == encoder_type)
			return encoder;
	}
	return NULL;
}