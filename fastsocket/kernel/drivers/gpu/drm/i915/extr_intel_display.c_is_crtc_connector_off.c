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
struct drm_crtc {int dummy; } ;
struct drm_connector {scalar_t__ dpms; TYPE_1__* encoder; } ;
struct TYPE_2__ {struct drm_crtc* crtc; } ;

/* Variables and functions */
 scalar_t__ DRM_MODE_DPMS_ON ; 

__attribute__((used)) static bool
is_crtc_connector_off(struct drm_crtc *crtc, struct drm_connector *connectors,
		      int num_connectors)
{
	int i;

	for (i = 0; i < num_connectors; i++)
		if (connectors[i].encoder &&
		    connectors[i].encoder->crtc == crtc &&
		    connectors[i].dpms != DRM_MODE_DPMS_ON)
			return true;

	return false;
}