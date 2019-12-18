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
struct TYPE_6__ {struct drm_device* dev; } ;
struct TYPE_5__ {TYPE_2__ base; } ;
struct intel_sdvo_connector {TYPE_1__ base; } ;
struct intel_sdvo {int color_range_auto; } ;
struct drm_device {int dummy; } ;
struct TYPE_7__ {int gen; } ;

/* Variables and functions */
 TYPE_4__* INTEL_INFO (struct drm_device*) ; 
 scalar_t__ IS_MOBILE (struct drm_device*) ; 
 int /*<<< orphan*/  intel_attach_broadcast_rgb_property (TYPE_2__*) ; 
 int /*<<< orphan*/  intel_attach_force_audio_property (TYPE_2__*) ; 

__attribute__((used)) static void
intel_sdvo_add_hdmi_properties(struct intel_sdvo *intel_sdvo,
			       struct intel_sdvo_connector *connector)
{
	struct drm_device *dev = connector->base.base.dev;

	intel_attach_force_audio_property(&connector->base.base);
	if (INTEL_INFO(dev)->gen >= 4 && IS_MOBILE(dev)) {
		intel_attach_broadcast_rgb_property(&connector->base.base);
		intel_sdvo->color_range_auto = true;
	}
}