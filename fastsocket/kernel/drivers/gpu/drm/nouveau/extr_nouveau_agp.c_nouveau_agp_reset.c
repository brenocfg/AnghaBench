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
typedef  int u32 ;
struct nouveau_drm {struct drm_device* dev; int /*<<< orphan*/  device; } ;
struct nouveau_device {int dummy; } ;
struct drm_device {TYPE_1__* agp; } ;
struct drm_agp_mode {int mode; } ;
struct drm_agp_info {int /*<<< orphan*/  mode; } ;
struct TYPE_2__ {int mode; } ;

/* Variables and functions */
 int NV04_PBUS_PCI_NV_1 ; 
 int NV04_PBUS_PCI_NV_19 ; 
 int PCI_AGP_COMMAND_FW ; 
 int drm_agp_enable (struct drm_device*,struct drm_agp_mode) ; 
 int drm_agp_info (struct drm_device*,struct drm_agp_info*) ; 
 int get_agp_mode (struct nouveau_drm*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nouveau_agp_enabled (struct nouveau_drm*) ; 
 struct nouveau_device* nv_device (int /*<<< orphan*/ ) ; 
 int nv_mask (struct nouveau_device*,int,int,int) ; 
 int nv_rd32 (struct nouveau_device*,int) ; 
 int /*<<< orphan*/  nv_wr32 (struct nouveau_device*,int,int) ; 

void
nouveau_agp_reset(struct nouveau_drm *drm)
{
#if __OS_HAS_AGP
	struct nouveau_device *device = nv_device(drm->device);
	struct drm_device *dev = drm->dev;
	u32 save[2];
	int ret;

	if (!nouveau_agp_enabled(drm))
		return;

	/* First of all, disable fast writes, otherwise if it's
	 * already enabled in the AGP bridge and we disable the card's
	 * AGP controller we might be locking ourselves out of it. */
	if ((nv_rd32(device, NV04_PBUS_PCI_NV_19) |
	     dev->agp->mode) & PCI_AGP_COMMAND_FW) {
		struct drm_agp_info info;
		struct drm_agp_mode mode;

		ret = drm_agp_info(dev, &info);
		if (ret)
			return;

		mode.mode  = get_agp_mode(drm, info.mode);
		mode.mode &= ~PCI_AGP_COMMAND_FW;

		ret = drm_agp_enable(dev, mode);
		if (ret)
			return;
	}


	/* clear busmaster bit, and disable AGP */
	save[0] = nv_mask(device, NV04_PBUS_PCI_NV_1, 0x00000004, 0x00000000);
	nv_wr32(device, NV04_PBUS_PCI_NV_19, 0);

	/* reset PGRAPH, PFIFO and PTIMER */
	save[1] = nv_mask(device, 0x000200, 0x00011100, 0x00000000);
	nv_mask(device, 0x000200, 0x00011100, save[1]);

	/* and restore bustmaster bit (gives effect of resetting AGP) */
	nv_wr32(device, NV04_PBUS_PCI_NV_1, save[0]);
#endif
}