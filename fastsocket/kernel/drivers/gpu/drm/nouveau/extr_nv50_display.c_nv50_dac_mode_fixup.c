#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct nouveau_encoder {int dummy; } ;
struct nouveau_connector {scalar_t__ scaling_mode; struct drm_display_mode* native_mode; } ;
struct drm_encoder {int dummy; } ;
struct TYPE_2__ {int id; } ;
struct drm_display_mode {TYPE_1__ base; } ;

/* Variables and functions */
 scalar_t__ DRM_MODE_SCALE_NONE ; 
 struct nouveau_encoder* nouveau_encoder (struct drm_encoder*) ; 
 struct nouveau_connector* nouveau_encoder_connector_get (struct nouveau_encoder*) ; 

__attribute__((used)) static bool
nv50_dac_mode_fixup(struct drm_encoder *encoder,
		    const struct drm_display_mode *mode,
		    struct drm_display_mode *adjusted_mode)
{
	struct nouveau_encoder *nv_encoder = nouveau_encoder(encoder);
	struct nouveau_connector *nv_connector;

	nv_connector = nouveau_encoder_connector_get(nv_encoder);
	if (nv_connector && nv_connector->native_mode) {
		if (nv_connector->scaling_mode != DRM_MODE_SCALE_NONE) {
			int id = adjusted_mode->base.id;
			*adjusted_mode = *nv_connector->native_mode;
			adjusted_mode->base.id = id;
		}
	}

	return true;
}