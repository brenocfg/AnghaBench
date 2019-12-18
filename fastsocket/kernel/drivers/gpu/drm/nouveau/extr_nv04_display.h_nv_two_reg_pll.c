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
struct drm_device {int pci_device; } ;
struct TYPE_2__ {scalar_t__ card_type; } ;

/* Variables and functions */
 scalar_t__ NV_40 ; 
 struct nouveau_drm* nouveau_drm (struct drm_device*) ; 
 TYPE_1__* nv_device (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline bool
nv_two_reg_pll(struct drm_device *dev)
{
	struct nouveau_drm *drm = nouveau_drm(dev);
	const int impl = dev->pci_device & 0x0ff0;

	if (impl == 0x0310 || impl == 0x0340 || nv_device(drm->device)->card_type >= NV_40)
		return true;
	return false;
}