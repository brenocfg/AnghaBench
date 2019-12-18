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
 scalar_t__ NV_20 ; 
 struct nouveau_drm* nouveau_drm (struct drm_device*) ; 
 int /*<<< orphan*/  nv04_update_arb (struct drm_device*,int,int,int*,int*) ; 
 int /*<<< orphan*/  nv20_update_arb (int*,int*) ; 
 TYPE_1__* nv_device (int /*<<< orphan*/ ) ; 

void
nouveau_calc_arb(struct drm_device *dev, int vclk, int bpp, int *burst, int *lwm)
{
	struct nouveau_drm *drm = nouveau_drm(dev);

	if (nv_device(drm->device)->card_type < NV_20)
		nv04_update_arb(dev, vclk, bpp, burst, lwm);
	else if ((dev->pci_device & 0xfff0) == 0x0240 /*CHIPSET_C51*/ ||
		 (dev->pci_device & 0xfff0) == 0x03d0 /*CHIPSET_C512*/) {
		*burst = 128;
		*lwm = 0x0480;
	} else
		nv20_update_arb(burst, lwm);
}