#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct drm_get_cap {int value; int capability; } ;
struct drm_file {int dummy; } ;
struct TYPE_3__ {int preferred_depth; int prefer_shadow; } ;
struct drm_device {TYPE_2__* driver; TYPE_1__ mode_config; } ;
struct TYPE_4__ {int /*<<< orphan*/  prime_handle_to_fd; int /*<<< orphan*/  prime_fd_to_handle; int /*<<< orphan*/  dumb_create; } ;

/* Variables and functions */
#define  DRM_CAP_DUMB_BUFFER 133 
#define  DRM_CAP_DUMB_PREFERRED_DEPTH 132 
#define  DRM_CAP_DUMB_PREFER_SHADOW 131 
#define  DRM_CAP_PRIME 130 
#define  DRM_CAP_TIMESTAMP_MONOTONIC 129 
#define  DRM_CAP_VBLANK_HIGH_CRTC 128 
 int DRM_PRIME_CAP_EXPORT ; 
 int DRM_PRIME_CAP_IMPORT ; 
 int EINVAL ; 
 int drm_timestamp_monotonic ; 

int drm_getcap(struct drm_device *dev, void *data, struct drm_file *file_priv)
{
	struct drm_get_cap *req = data;

	req->value = 0;
	switch (req->capability) {
	case DRM_CAP_DUMB_BUFFER:
		if (dev->driver->dumb_create)
			req->value = 1;
		break;
	case DRM_CAP_VBLANK_HIGH_CRTC:
		req->value = 1;
		break;
	case DRM_CAP_DUMB_PREFERRED_DEPTH:
		req->value = dev->mode_config.preferred_depth;
		break;
	case DRM_CAP_DUMB_PREFER_SHADOW:
		req->value = dev->mode_config.prefer_shadow;
		break;
	case DRM_CAP_PRIME:
		req->value |= dev->driver->prime_fd_to_handle ? DRM_PRIME_CAP_IMPORT : 0;
		req->value |= dev->driver->prime_handle_to_fd ? DRM_PRIME_CAP_EXPORT : 0;
		break;
	case DRM_CAP_TIMESTAMP_MONOTONIC:
		req->value = drm_timestamp_monotonic;
		break;
	default:
		return -EINVAL;
	}
	return 0;
}