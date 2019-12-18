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
typedef  int /*<<< orphan*/  u32 ;
struct nouveau_drm {int /*<<< orphan*/  device; } ;
struct nouveau_device {scalar_t__ card_type; int chipset; } ;
struct TYPE_2__ {int /*<<< orphan*/  bdev; } ;
struct nouveau_bo {int tile_mode; int page_shift; TYPE_1__ bo; } ;

/* Variables and functions */
 scalar_t__ NV_50 ; 
 int PAGE_SIZE ; 
 int max (int,int) ; 
 struct nouveau_drm* nouveau_bdev (int /*<<< orphan*/ ) ; 
 struct nouveau_device* nv_device (int /*<<< orphan*/ ) ; 
 int roundup (int,int) ; 

__attribute__((used)) static void
nouveau_bo_fixup_align(struct nouveau_bo *nvbo, u32 flags,
		       int *align, int *size)
{
	struct nouveau_drm *drm = nouveau_bdev(nvbo->bo.bdev);
	struct nouveau_device *device = nv_device(drm->device);

	if (device->card_type < NV_50) {
		if (nvbo->tile_mode) {
			if (device->chipset >= 0x40) {
				*align = 65536;
				*size = roundup(*size, 64 * nvbo->tile_mode);

			} else if (device->chipset >= 0x30) {
				*align = 32768;
				*size = roundup(*size, 64 * nvbo->tile_mode);

			} else if (device->chipset >= 0x20) {
				*align = 16384;
				*size = roundup(*size, 64 * nvbo->tile_mode);

			} else if (device->chipset >= 0x10) {
				*align = 16384;
				*size = roundup(*size, 32 * nvbo->tile_mode);
			}
		}
	} else {
		*size = roundup(*size, (1 << nvbo->page_shift));
		*align = max((1 <<  nvbo->page_shift), *align);
	}

	*size = roundup(*size, PAGE_SIZE);
}