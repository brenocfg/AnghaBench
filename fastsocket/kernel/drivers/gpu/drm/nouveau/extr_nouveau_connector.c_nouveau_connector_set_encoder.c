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
struct nouveau_encoder {TYPE_2__* dcb; } ;
struct nouveau_drm {int /*<<< orphan*/  device; } ;
struct nouveau_connector {scalar_t__ type; struct nouveau_encoder* detected_encoder; } ;
struct TYPE_4__ {int /*<<< orphan*/  dvi_i_subconnector_property; } ;
struct drm_device {int pci_device; TYPE_1__ mode_config; } ;
struct drm_connector {int interlace_allowed; int doublescan_allowed; int /*<<< orphan*/  base; struct drm_device* dev; } ;
struct TYPE_6__ {scalar_t__ card_type; } ;
struct TYPE_5__ {scalar_t__ type; } ;

/* Variables and functions */
 scalar_t__ DCB_CONNECTOR_DVI_I ; 
 scalar_t__ DCB_OUTPUT_LVDS ; 
 scalar_t__ DCB_OUTPUT_TMDS ; 
 int /*<<< orphan*/  DRM_MODE_SUBCONNECTOR_DVIA ; 
 int /*<<< orphan*/  DRM_MODE_SUBCONNECTOR_DVID ; 
 scalar_t__ NV_10 ; 
 scalar_t__ NV_20 ; 
 scalar_t__ NV_50 ; 
 int /*<<< orphan*/  drm_object_property_set_value (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct nouveau_connector* nouveau_connector (struct drm_connector*) ; 
 struct nouveau_drm* nouveau_drm (struct drm_device*) ; 
 TYPE_3__* nv_device (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
nouveau_connector_set_encoder(struct drm_connector *connector,
			      struct nouveau_encoder *nv_encoder)
{
	struct nouveau_connector *nv_connector = nouveau_connector(connector);
	struct nouveau_drm *drm = nouveau_drm(connector->dev);
	struct drm_device *dev = connector->dev;

	if (nv_connector->detected_encoder == nv_encoder)
		return;
	nv_connector->detected_encoder = nv_encoder;

	if (nv_device(drm->device)->card_type >= NV_50) {
		connector->interlace_allowed = true;
		connector->doublescan_allowed = true;
	} else
	if (nv_encoder->dcb->type == DCB_OUTPUT_LVDS ||
	    nv_encoder->dcb->type == DCB_OUTPUT_TMDS) {
		connector->doublescan_allowed = false;
		connector->interlace_allowed = false;
	} else {
		connector->doublescan_allowed = true;
		if (nv_device(drm->device)->card_type == NV_20 ||
		   (nv_device(drm->device)->card_type == NV_10 &&
		    (dev->pci_device & 0x0ff0) != 0x0100 &&
		    (dev->pci_device & 0x0ff0) != 0x0150))
			/* HW is broken */
			connector->interlace_allowed = false;
		else
			connector->interlace_allowed = true;
	}

	if (nv_connector->type == DCB_CONNECTOR_DVI_I) {
		drm_object_property_set_value(&connector->base,
			dev->mode_config.dvi_i_subconnector_property,
			nv_encoder->dcb->type == DCB_OUTPUT_TMDS ?
			DRM_MODE_SUBCONNECTOR_DVID :
			DRM_MODE_SUBCONNECTOR_DVIA);
	}
}