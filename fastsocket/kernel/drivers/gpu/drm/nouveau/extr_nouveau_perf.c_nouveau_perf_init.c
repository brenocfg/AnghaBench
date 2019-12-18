#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct nvbios {scalar_t__ type; int* data; int offset; } ;
struct TYPE_5__ {int /*<<< orphan*/  head; int /*<<< orphan*/ * func; int /*<<< orphan*/  name; } ;
struct nouveau_pm_level {int fanspeed; int volt_min; int core; int memory; int shader; int memscript; int vdec; int dom6; int id; TYPE_2__ profile; int /*<<< orphan*/  name; int /*<<< orphan*/  timing; void* hub07; void* daemon; void* rop; void* copy; void* hub01; void* hub06; void* unka0; } ;
struct TYPE_4__ {scalar_t__ supported; } ;
struct nouveau_pm {size_t nr_perflvl; int /*<<< orphan*/  profiles; TYPE_1__ voltage; struct nouveau_pm_level* perflvl; } ;
struct nouveau_drm {int /*<<< orphan*/  device; struct nvbios vbios; } ;
struct drm_device {int dummy; } ;
struct TYPE_6__ {int chipset; int /*<<< orphan*/  card_type; } ;

/* Variables and functions */
 scalar_t__ NVBIOS_BMP ; 
 int /*<<< orphan*/  NV_50 ; 
 int /*<<< orphan*/  NV_DEBUG (struct nouveau_drm*,char*,int,...) ; 
 int ROM16 (int) ; 
 int ROM32 (int) ; 
 int /*<<< orphan*/  legacy_perf_init (struct drm_device*) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct nouveau_drm* nouveau_drm (struct drm_device*) ; 
 int nouveau_mem_timing_calc (struct drm_device*,int,int /*<<< orphan*/ *) ; 
 int* nouveau_perf_entry (struct drm_device*,int,int*,int*,int*,int*) ; 
 int* nouveau_perf_table (struct drm_device*,int*) ; 
 int /*<<< orphan*/  nouveau_perf_voltage (struct drm_device*,struct nouveau_pm_level*) ; 
 struct nouveau_pm* nouveau_pm (struct drm_device*) ; 
 int /*<<< orphan*/  nouveau_pm_static_profile_func ; 
 int nouveau_volt_vid_lookup (struct drm_device*,int) ; 
 TYPE_3__* nv_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,int) ; 
 void* subent (int) ; 

void
nouveau_perf_init(struct drm_device *dev)
{
	struct nouveau_drm *drm = nouveau_drm(dev);
	struct nouveau_pm *pm = nouveau_pm(dev);
	struct nvbios *bios = &drm->vbios;
	u8 *perf, ver, hdr, cnt, len;
	int ret, vid, i = -1;

	if (bios->type == NVBIOS_BMP && bios->data[bios->offset + 6] < 0x25) {
		legacy_perf_init(dev);
		return;
	}

	perf = nouveau_perf_table(dev, &ver);

	while ((perf = nouveau_perf_entry(dev, ++i, &ver, &hdr, &cnt, &len))) {
		struct nouveau_pm_level *perflvl = &pm->perflvl[pm->nr_perflvl];

		if (perf[0] == 0xff)
			continue;

		switch (ver) {
		case 0x12:
		case 0x13:
		case 0x15:
			perflvl->fanspeed = perf[55];
			if (hdr > 56)
				perflvl->volt_min = perf[56];
			perflvl->core = ROM32(perf[1]) * 10;
			perflvl->memory = ROM32(perf[5]) * 20;
			break;
		case 0x21:
		case 0x23:
		case 0x24:
			perflvl->fanspeed = perf[4];
			perflvl->volt_min = perf[5];
			perflvl->shader = ROM16(perf[6]) * 1000;
			perflvl->core = perflvl->shader;
			perflvl->core += (signed char)perf[8] * 1000;
			if (nv_device(drm->device)->chipset == 0x49 ||
			    nv_device(drm->device)->chipset == 0x4b)
				perflvl->memory = ROM16(perf[11]) * 1000;
			else
				perflvl->memory = ROM16(perf[11]) * 2000;
			break;
		case 0x25:
			perflvl->fanspeed = perf[4];
			perflvl->volt_min = perf[5];
			perflvl->core = ROM16(perf[6]) * 1000;
			perflvl->shader = ROM16(perf[10]) * 1000;
			perflvl->memory = ROM16(perf[12]) * 1000;
			break;
		case 0x30:
			perflvl->memscript = ROM16(perf[2]);
		case 0x35:
			perflvl->fanspeed = perf[6];
			perflvl->volt_min = perf[7];
			perflvl->core = ROM16(perf[8]) * 1000;
			perflvl->shader = ROM16(perf[10]) * 1000;
			perflvl->memory = ROM16(perf[12]) * 1000;
			perflvl->vdec = ROM16(perf[16]) * 1000;
			perflvl->dom6 = ROM16(perf[20]) * 1000;
			break;
		case 0x40:
#define subent(n) ((ROM16(perf[hdr + (n) * len]) & 0xfff) * 1000)
			perflvl->fanspeed = 0; /*XXX*/
			perflvl->volt_min = perf[2];
			if (nv_device(drm->device)->card_type == NV_50) {
				perflvl->core   = subent(0);
				perflvl->shader = subent(1);
				perflvl->memory = subent(2);
				perflvl->vdec   = subent(3);
				perflvl->unka0  = subent(4);
			} else {
				perflvl->hub06  = subent(0);
				perflvl->hub01  = subent(1);
				perflvl->copy   = subent(2);
				perflvl->shader = subent(3);
				perflvl->rop    = subent(4);
				perflvl->memory = subent(5);
				perflvl->vdec   = subent(6);
				perflvl->daemon = subent(10);
				perflvl->hub07  = subent(11);
				perflvl->core   = perflvl->shader / 2;
			}
			break;
		}

		/* make sure vid is valid */
		nouveau_perf_voltage(dev, perflvl);
		if (pm->voltage.supported && perflvl->volt_min) {
			vid = nouveau_volt_vid_lookup(dev, perflvl->volt_min);
			if (vid < 0) {
				NV_DEBUG(drm, "perflvl %d, bad vid\n", i);
				continue;
			}
		}

		/* get the corresponding memory timings */
		ret = nouveau_mem_timing_calc(dev, perflvl->memory,
					          &perflvl->timing);
		if (ret) {
			NV_DEBUG(drm, "perflvl %d, bad timing: %d\n", i, ret);
			continue;
		}

		snprintf(perflvl->name, sizeof(perflvl->name),
			 "performance_level_%d", i);
		perflvl->id = i;

		snprintf(perflvl->profile.name, sizeof(perflvl->profile.name),
			 "%d", perflvl->id);
		perflvl->profile.func = &nouveau_pm_static_profile_func;
		list_add_tail(&perflvl->profile.head, &pm->profiles);


		pm->nr_perflvl++;
	}
}