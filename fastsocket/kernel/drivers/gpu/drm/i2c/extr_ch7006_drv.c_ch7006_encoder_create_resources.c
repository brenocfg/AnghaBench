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
struct drm_mode_config {int /*<<< orphan*/  tv_flicker_reduction_property; int /*<<< orphan*/  tv_contrast_property; int /*<<< orphan*/  tv_brightness_property; int /*<<< orphan*/  tv_mode_property; int /*<<< orphan*/  tv_bottom_margin_property; int /*<<< orphan*/  tv_left_margin_property; int /*<<< orphan*/  tv_subconnector_property; int /*<<< orphan*/  tv_select_subconnector_property; } ;
struct drm_encoder {struct drm_device* dev; } ;
struct drm_device {struct drm_mode_config mode_config; } ;
struct drm_connector {int /*<<< orphan*/  base; } ;
struct ch7006_priv {int /*<<< orphan*/  scale; int /*<<< orphan*/  scale_property; int /*<<< orphan*/  flicker; int /*<<< orphan*/  contrast; int /*<<< orphan*/  brightness; int /*<<< orphan*/  norm; int /*<<< orphan*/  vmargin; int /*<<< orphan*/  hmargin; int /*<<< orphan*/  subconnector; int /*<<< orphan*/  select_subconnector; } ;

/* Variables and functions */
 int /*<<< orphan*/  NUM_TV_NORMS ; 
 int /*<<< orphan*/  ch7006_tv_norm_names ; 
 int /*<<< orphan*/  drm_mode_create_tv_properties (struct drm_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_object_attach_property (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_property_create_range (struct drm_device*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int) ; 
 struct ch7006_priv* to_ch7006_priv (struct drm_encoder*) ; 

__attribute__((used)) static int ch7006_encoder_create_resources(struct drm_encoder *encoder,
					   struct drm_connector *connector)
{
	struct ch7006_priv *priv = to_ch7006_priv(encoder);
	struct drm_device *dev = encoder->dev;
	struct drm_mode_config *conf = &dev->mode_config;

	drm_mode_create_tv_properties(dev, NUM_TV_NORMS, ch7006_tv_norm_names);

	priv->scale_property = drm_property_create_range(dev, 0, "scale", 0, 2);

	drm_object_attach_property(&connector->base, conf->tv_select_subconnector_property,
				      priv->select_subconnector);
	drm_object_attach_property(&connector->base, conf->tv_subconnector_property,
				      priv->subconnector);
	drm_object_attach_property(&connector->base, conf->tv_left_margin_property,
				      priv->hmargin);
	drm_object_attach_property(&connector->base, conf->tv_bottom_margin_property,
				      priv->vmargin);
	drm_object_attach_property(&connector->base, conf->tv_mode_property,
				      priv->norm);
	drm_object_attach_property(&connector->base, conf->tv_brightness_property,
				      priv->brightness);
	drm_object_attach_property(&connector->base, conf->tv_contrast_property,
				      priv->contrast);
	drm_object_attach_property(&connector->base, conf->tv_flicker_reduction_property,
				      priv->flicker);
	drm_object_attach_property(&connector->base, priv->scale_property,
				      priv->scale);

	return 0;
}