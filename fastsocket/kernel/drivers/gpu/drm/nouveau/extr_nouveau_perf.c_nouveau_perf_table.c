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
typedef  int /*<<< orphan*/  u8 ;
struct nvbios {scalar_t__ type; int* data; int offset; } ;
struct nouveau_drm {struct nvbios vbios; } ;
struct drm_device {int dummy; } ;
struct bit_entry {int version; int* data; } ;

/* Variables and functions */
 scalar_t__ NVBIOS_BMP ; 
 int /*<<< orphan*/ * ROMPTR (struct drm_device*,int) ; 
 int /*<<< orphan*/  bit_table (struct drm_device*,char,struct bit_entry*) ; 
 struct nouveau_drm* nouveau_drm (struct drm_device*) ; 

__attribute__((used)) static u8 *
nouveau_perf_table(struct drm_device *dev, u8 *ver)
{
	struct nouveau_drm *drm = nouveau_drm(dev);
	struct nvbios *bios = &drm->vbios;
	struct bit_entry P;

	if (!bit_table(dev, 'P', &P) && P.version && P.version <= 2) {
		u8 *perf = ROMPTR(dev, P.data[0]);
		if (perf) {
			*ver = perf[0];
			return perf;
		}
	}

	if (bios->type == NVBIOS_BMP) {
		if (bios->data[bios->offset + 6] >= 0x25) {
			u8 *perf = ROMPTR(dev, bios->data[bios->offset + 0x94]);
			if (perf) {
				*ver = perf[1];
				return perf;
			}
		}
	}

	return NULL;
}