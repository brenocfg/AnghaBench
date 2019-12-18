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
struct nvbios {char* data; size_t offset; } ;
struct nouveau_pm {int nr_perflvl; TYPE_1__* perflvl; } ;
struct nouveau_drm {struct nvbios vbios; } ;
struct nouveau_device {int dummy; } ;
struct drm_device {int dummy; } ;
struct TYPE_2__ {int memory; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  NV_DEBUG (struct nouveau_drm*,char*) ; 
 int /*<<< orphan*/  NV_PEXTDEV_BOOT_0 ; 
 int /*<<< orphan*/  NV_WARN (struct nouveau_drm*,char*,char) ; 
 int ROM16 (char) ; 
 char* ROMPTR (struct drm_device*,char) ; 
 struct nouveau_device* nouveau_dev (struct drm_device*) ; 
 struct nouveau_drm* nouveau_drm (struct drm_device*) ; 
 struct nouveau_pm* nouveau_pm (struct drm_device*) ; 
 int nv_rd32 (struct nouveau_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sprintf (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void
legacy_perf_init(struct drm_device *dev)
{
	struct nouveau_device *device = nouveau_dev(dev);
	struct nouveau_drm *drm = nouveau_drm(dev);
	struct nvbios *bios = &drm->vbios;
	struct nouveau_pm *pm = nouveau_pm(dev);
	char *perf, *entry, *bmp = &bios->data[bios->offset];
	int headerlen, use_straps;

	if (bmp[5] < 0x5 || bmp[6] < 0x14) {
		NV_DEBUG(drm, "BMP version too old for perf\n");
		return;
	}

	perf = ROMPTR(dev, bmp[0x73]);
	if (!perf) {
		NV_DEBUG(drm, "No memclock table pointer found.\n");
		return;
	}

	switch (perf[0]) {
	case 0x12:
	case 0x14:
	case 0x18:
		use_straps = 0;
		headerlen = 1;
		break;
	case 0x01:
		use_straps = perf[1] & 1;
		headerlen = (use_straps ? 8 : 2);
		break;
	default:
		NV_WARN(drm, "Unknown memclock table version %x.\n", perf[0]);
		return;
	}

	entry = perf + headerlen;
	if (use_straps)
		entry += (nv_rd32(device, NV_PEXTDEV_BOOT_0) & 0x3c) >> 1;

	sprintf(pm->perflvl[0].name, "performance_level_0");
	pm->perflvl[0].memory = ROM16(entry[0]) * 20;
	pm->nr_perflvl = 1;
}