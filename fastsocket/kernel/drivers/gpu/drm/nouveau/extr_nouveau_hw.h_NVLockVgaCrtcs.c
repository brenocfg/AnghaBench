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
struct nouveau_drm {int /*<<< orphan*/  device; } ;
struct drm_device {int dummy; } ;
struct TYPE_2__ {int chipset; } ;

/* Variables and functions */
 int /*<<< orphan*/  NVReadVgaCrtc (struct drm_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NVWriteVgaCrtc (struct drm_device*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NV_CIO_SR_LOCK_INDEX ; 
 int /*<<< orphan*/  NV_CIO_SR_LOCK_VALUE ; 
 int /*<<< orphan*/  NV_CIO_SR_UNLOCK_RW_VALUE ; 
 struct nouveau_drm* nouveau_drm (struct drm_device*) ; 
 TYPE_1__* nv_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nv_heads_tied (struct drm_device*) ; 

__attribute__((used)) static inline bool
NVLockVgaCrtcs(struct drm_device *dev, bool lock)
{
	struct nouveau_drm *drm = nouveau_drm(dev);
	bool waslocked = !NVReadVgaCrtc(dev, 0, NV_CIO_SR_LOCK_INDEX);

	NVWriteVgaCrtc(dev, 0, NV_CIO_SR_LOCK_INDEX,
		       lock ? NV_CIO_SR_LOCK_VALUE : NV_CIO_SR_UNLOCK_RW_VALUE);
	/* NV11 has independently lockable extended crtcs, except when tied */
	if (nv_device(drm->device)->chipset == 0x11 && !nv_heads_tied(dev))
		NVWriteVgaCrtc(dev, 1, NV_CIO_SR_LOCK_INDEX,
			       lock ? NV_CIO_SR_LOCK_VALUE :
				      NV_CIO_SR_UNLOCK_RW_VALUE);

	return waslocked;
}