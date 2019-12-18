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
struct nvbios {int feature_byte; int* data; int is_mobile; void* tvdactestval; void* dactestval; } ;
struct nouveau_drm {int dummy; } ;
struct drm_device {int dummy; } ;
struct bit_entry {int length; int offset; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOSYS ; 
 int FEATURE_MOBILE ; 
 int /*<<< orphan*/  NV_ERROR (struct nouveau_drm*,char*) ; 
 int /*<<< orphan*/  NV_WARN (struct nouveau_drm*,char*,...) ; 
 size_t ROM16 (int) ; 
 void* ROM32 (int) ; 
 struct nouveau_drm* nouveau_drm (struct drm_device*) ; 

__attribute__((used)) static int parse_bit_i_tbl_entry(struct drm_device *dev, struct nvbios *bios, struct bit_entry *bitentry)
{
	/*
	 * BIT 'i' (info?) table
	 *
	 * offset + 0  (32 bits): BIOS version dword (as in B table)
	 * offset + 5  (8  bits): BIOS feature byte (same as for BMP?)
	 * offset + 13 (16 bits): pointer to table containing DAC load
	 * detection comparison values
	 *
	 * There's other things in the table, purpose unknown
	 */

	struct nouveau_drm *drm = nouveau_drm(dev);
	uint16_t daccmpoffset;
	uint8_t dacver, dacheaderlen;

	if (bitentry->length < 6) {
		NV_ERROR(drm, "BIT i table too short for needed information\n");
		return -EINVAL;
	}

	/*
	 * bit 4 seems to indicate a mobile bios (doesn't suffer from BMP's
	 * Quadro identity crisis), other bits possibly as for BMP feature byte
	 */
	bios->feature_byte = bios->data[bitentry->offset + 5];
	bios->is_mobile = bios->feature_byte & FEATURE_MOBILE;

	if (bitentry->length < 15) {
		NV_WARN(drm, "BIT i table not long enough for DAC load "
			       "detection comparison table\n");
		return -EINVAL;
	}

	daccmpoffset = ROM16(bios->data[bitentry->offset + 13]);

	/* doesn't exist on g80 */
	if (!daccmpoffset)
		return 0;

	/*
	 * The first value in the table, following the header, is the
	 * comparison value, the second entry is a comparison value for
	 * TV load detection.
	 */

	dacver = bios->data[daccmpoffset];
	dacheaderlen = bios->data[daccmpoffset + 1];

	if (dacver != 0x00 && dacver != 0x10) {
		NV_WARN(drm, "DAC load detection comparison table version "
			       "%d.%d not known\n", dacver >> 4, dacver & 0xf);
		return -ENOSYS;
	}

	bios->dactestval = ROM32(bios->data[daccmpoffset + dacheaderlen]);
	bios->tvdactestval = ROM32(bios->data[daccmpoffset + dacheaderlen + 4]);

	return 0;
}