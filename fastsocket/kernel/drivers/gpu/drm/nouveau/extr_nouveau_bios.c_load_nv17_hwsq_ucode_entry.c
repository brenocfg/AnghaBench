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
typedef  int uint8_t ;
typedef  size_t uint16_t ;
struct nvbios {int* data; } ;
struct nouveau_drm {int /*<<< orphan*/  device; } ;
struct nouveau_device {int dummy; } ;
struct drm_device {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOENT ; 
 int /*<<< orphan*/  NV_ERROR (struct nouveau_drm*,char*) ; 
 int /*<<< orphan*/  NV_INFO (struct nouveau_drm*,char*) ; 
 int NV_PBUS_DEBUG_4 ; 
 int ROM32 (int) ; 
 struct nouveau_drm* nouveau_drm (struct drm_device*) ; 
 struct nouveau_device* nv_device (int /*<<< orphan*/ ) ; 
 int nv_rd32 (struct nouveau_device*,int) ; 
 int /*<<< orphan*/  nv_wr32 (struct nouveau_device*,int,int) ; 

__attribute__((used)) static int load_nv17_hwsq_ucode_entry(struct drm_device *dev, struct nvbios *bios, uint16_t hwsq_offset, int entry)
{
	/*
	 * The header following the "HWSQ" signature has the number of entries,
	 * and the entry size
	 *
	 * An entry consists of a dword to write to the sequencer control reg
	 * (0x00001304), followed by the ucode bytes, written sequentially,
	 * starting at reg 0x00001400
	 */

	struct nouveau_drm *drm = nouveau_drm(dev);
	struct nouveau_device *device = nv_device(drm->device);
	uint8_t bytes_to_write;
	uint16_t hwsq_entry_offset;
	int i;

	if (bios->data[hwsq_offset] <= entry) {
		NV_ERROR(drm, "Too few entries in HW sequencer table for "
				"requested entry\n");
		return -ENOENT;
	}

	bytes_to_write = bios->data[hwsq_offset + 1];

	if (bytes_to_write != 36) {
		NV_ERROR(drm, "Unknown HW sequencer entry size\n");
		return -EINVAL;
	}

	NV_INFO(drm, "Loading NV17 power sequencing microcode\n");

	hwsq_entry_offset = hwsq_offset + 2 + entry * bytes_to_write;

	/* set sequencer control */
	nv_wr32(device, 0x00001304, ROM32(bios->data[hwsq_entry_offset]));
	bytes_to_write -= 4;

	/* write ucode */
	for (i = 0; i < bytes_to_write; i += 4)
		nv_wr32(device, 0x00001400 + i, ROM32(bios->data[hwsq_entry_offset + i + 4]));

	/* twiddle NV_PBUS_DEBUG_4 */
	nv_wr32(device, NV_PBUS_DEBUG_4, nv_rd32(device, NV_PBUS_DEBUG_4) | 0x18);

	return 0;
}