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
typedef  int uint16_t ;
struct nvbios {int* data; int dactestval; } ;
struct nouveau_drm {int dummy; } ;
struct drm_device {int dummy; } ;
struct bit_entry {int length; size_t offset; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOSYS ; 
 int /*<<< orphan*/  NV_DEBUG (struct nouveau_drm*,char*) ; 
 int /*<<< orphan*/  NV_ERROR (struct nouveau_drm*,char*,...) ; 
 int ROM16 (int) ; 
 int ROM32 (int) ; 
 struct nouveau_drm* nouveau_drm (struct drm_device*) ; 

__attribute__((used)) static int parse_bit_A_tbl_entry(struct drm_device *dev, struct nvbios *bios, struct bit_entry *bitentry)
{
	/*
	 * Parses the load detect values for g80 cards.
	 *
	 * offset + 0 (16 bits): loadval table pointer
	 */

	struct nouveau_drm *drm = nouveau_drm(dev);
	uint16_t load_table_ptr;
	uint8_t version, headerlen, entrylen, num_entries;

	if (bitentry->length != 3) {
		NV_ERROR(drm, "Do not understand BIT A table\n");
		return -EINVAL;
	}

	load_table_ptr = ROM16(bios->data[bitentry->offset]);

	if (load_table_ptr == 0x0) {
		NV_DEBUG(drm, "Pointer to BIT loadval table invalid\n");
		return -EINVAL;
	}

	version = bios->data[load_table_ptr];

	if (version != 0x10) {
		NV_ERROR(drm, "BIT loadval table version %d.%d not supported\n",
			 version >> 4, version & 0xF);
		return -ENOSYS;
	}

	headerlen = bios->data[load_table_ptr + 1];
	entrylen = bios->data[load_table_ptr + 2];
	num_entries = bios->data[load_table_ptr + 3];

	if (headerlen != 4 || entrylen != 4 || num_entries != 2) {
		NV_ERROR(drm, "Do not understand BIT loadval table\n");
		return -EINVAL;
	}

	/* First entry is normal dac, 2nd tv-out perhaps? */
	bios->dactestval = ROM32(bios->data[load_table_ptr + headerlen]) & 0x3ff;

	return 0;
}