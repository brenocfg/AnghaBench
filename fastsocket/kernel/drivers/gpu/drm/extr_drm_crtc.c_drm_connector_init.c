#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  dpms_property; int /*<<< orphan*/  edid_property; int /*<<< orphan*/  num_connector; int /*<<< orphan*/  connector_list; } ;
struct drm_device {TYPE_1__ mode_config; } ;
struct drm_connector_funcs {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/ * properties; } ;
struct drm_connector {int connector_type; TYPE_2__ base; int /*<<< orphan*/  head; int /*<<< orphan*/  status; int /*<<< orphan*/ * edid_blob_ptr; int /*<<< orphan*/  modes; int /*<<< orphan*/  probed_modes; int /*<<< orphan*/  user_modes; scalar_t__ connector_type_id; struct drm_connector_funcs const* funcs; struct drm_device* dev; int /*<<< orphan*/  properties; } ;
struct TYPE_7__ {scalar_t__ count; } ;

/* Variables and functions */
 int DRM_MODE_CONNECTOR_VIRTUAL ; 
 int /*<<< orphan*/  DRM_MODE_OBJECT_CONNECTOR ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  connector_status_unknown ; 
 TYPE_4__* drm_connector_enum_list ; 
 int drm_mode_object_get (struct drm_device*,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_modeset_lock_all (struct drm_device*) ; 
 int /*<<< orphan*/  drm_modeset_unlock_all (struct drm_device*) ; 
 int /*<<< orphan*/  drm_object_attach_property (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int drm_connector_init(struct drm_device *dev,
		       struct drm_connector *connector,
		       const struct drm_connector_funcs *funcs,
		       int connector_type)
{
	int ret;

	drm_modeset_lock_all(dev);

	ret = drm_mode_object_get(dev, &connector->base, DRM_MODE_OBJECT_CONNECTOR);
	if (ret)
		goto out;

	connector->base.properties = &connector->properties;
	connector->dev = dev;
	connector->funcs = funcs;
	connector->connector_type = connector_type;
	connector->connector_type_id =
		++drm_connector_enum_list[connector_type].count; /* TODO */
	INIT_LIST_HEAD(&connector->user_modes);
	INIT_LIST_HEAD(&connector->probed_modes);
	INIT_LIST_HEAD(&connector->modes);
	connector->edid_blob_ptr = NULL;
	connector->status = connector_status_unknown;

	list_add_tail(&connector->head, &dev->mode_config.connector_list);
	dev->mode_config.num_connector++;

	if (connector_type != DRM_MODE_CONNECTOR_VIRTUAL)
		drm_object_attach_property(&connector->base,
					      dev->mode_config.edid_property,
					      0);

	drm_object_attach_property(&connector->base,
				      dev->mode_config.dpms_property, 0);

 out:
	drm_modeset_unlock_all(dev);

	return ret;
}