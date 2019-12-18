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
typedef  int uint32_t ;
struct nouveau_object {int dummy; } ;
struct nouveau_drm {struct nouveau_object* device; } ;
struct drm_device {int dummy; } ;

/* Variables and functions */
 struct nouveau_drm* nouveau_drm (struct drm_device*) ; 
 scalar_t__ nv_device_match (struct nouveau_object*,int,int,int) ; 

__attribute__((used)) static bool
get_tv_detect_quirks(struct drm_device *dev, uint32_t *pin_mask)
{
	struct nouveau_drm *drm = nouveau_drm(dev);
	struct nouveau_object *device = drm->device;

	/* Zotac FX5200 */
	if (nv_device_match(device, 0x0322, 0x19da, 0x1035) ||
	    nv_device_match(device, 0x0322, 0x19da, 0x2035)) {
		*pin_mask = 0xc;
		return false;
	}

	/* MSI nForce2 IGP */
	if (nv_device_match(device, 0x01f0, 0x1462, 0x5710)) {
		*pin_mask = 0xc;
		return false;
	}

	return true;
}