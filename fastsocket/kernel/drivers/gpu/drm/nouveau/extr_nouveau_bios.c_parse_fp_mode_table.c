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
typedef  int uint8_t ;
struct TYPE_2__ {int fptablepointer; int fpxlatetableptr; int lvdsmanufacturerpointer; int xlatwidth; int mode_ptr; } ;
struct nvbios {int digital_min_front_porch; int* data; int fp_no_ddc; TYPE_1__ fp; int /*<<< orphan*/  is_mobile; } ;
struct nouveau_drm {int dummy; } ;
struct lvdstableheader {int lvds_ver; int headerlen; int recordlen; } ;
struct drm_device {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOENT ; 
 int ENOSYS ; 
 int /*<<< orphan*/  NV_ERROR (struct nouveau_drm*,char*,...) ; 
 int /*<<< orphan*/  NV_INFO (struct nouveau_drm*,char*,int,int,int) ; 
 int ROM16 (int) ; 
 int get_fp_strap (struct drm_device*,struct nvbios*) ; 
 struct nouveau_drm* nouveau_drm (struct drm_device*) ; 
 int parse_lvds_manufacturer_table_header (struct drm_device*,struct nvbios*,struct lvdstableheader*) ; 

__attribute__((used)) static int parse_fp_mode_table(struct drm_device *dev, struct nvbios *bios)
{
	struct nouveau_drm *drm = nouveau_drm(dev);
	uint8_t *fptable;
	uint8_t fptable_ver, headerlen = 0, recordlen, fpentries = 0xf, fpindex;
	int ret, ofs, fpstrapping;
	struct lvdstableheader lth;

	if (bios->fp.fptablepointer == 0x0) {
		/* Apple cards don't have the fp table; the laptops use DDC */
		/* The table is also missing on some x86 IGPs */
#ifndef __powerpc__
		NV_ERROR(drm, "Pointer to flat panel table invalid\n");
#endif
		bios->digital_min_front_porch = 0x4b;
		return 0;
	}

	fptable = &bios->data[bios->fp.fptablepointer];
	fptable_ver = fptable[0];

	switch (fptable_ver) {
	/*
	 * BMP version 0x5.0x11 BIOSen have version 1 like tables, but no
	 * version field, and miss one of the spread spectrum/PWM bytes.
	 * This could affect early GF2Go parts (not seen any appropriate ROMs
	 * though). Here we assume that a version of 0x05 matches this case
	 * (combining with a BMP version check would be better), as the
	 * common case for the panel type field is 0x0005, and that is in
	 * fact what we are reading the first byte of.
	 */
	case 0x05:	/* some NV10, 11, 15, 16 */
		recordlen = 42;
		ofs = -1;
		break;
	case 0x10:	/* some NV15/16, and NV11+ */
		recordlen = 44;
		ofs = 0;
		break;
	case 0x20:	/* NV40+ */
		headerlen = fptable[1];
		recordlen = fptable[2];
		fpentries = fptable[3];
		/*
		 * fptable[4] is the minimum
		 * RAMDAC_FP_HCRTC -> RAMDAC_FP_HSYNC_START gap
		 */
		bios->digital_min_front_porch = fptable[4];
		ofs = -7;
		break;
	default:
		NV_ERROR(drm,
			 "FP table revision %d.%d not currently supported\n",
			 fptable_ver >> 4, fptable_ver & 0xf);
		return -ENOSYS;
	}

	if (!bios->is_mobile) /* !mobile only needs digital_min_front_porch */
		return 0;

	ret = parse_lvds_manufacturer_table_header(dev, bios, &lth);
	if (ret)
		return ret;

	if (lth.lvds_ver == 0x30 || lth.lvds_ver == 0x40) {
		bios->fp.fpxlatetableptr = bios->fp.lvdsmanufacturerpointer +
							lth.headerlen + 1;
		bios->fp.xlatwidth = lth.recordlen;
	}
	if (bios->fp.fpxlatetableptr == 0x0) {
		NV_ERROR(drm, "Pointer to flat panel xlat table invalid\n");
		return -EINVAL;
	}

	fpstrapping = get_fp_strap(dev, bios);

	fpindex = bios->data[bios->fp.fpxlatetableptr +
					fpstrapping * bios->fp.xlatwidth];

	if (fpindex > fpentries) {
		NV_ERROR(drm, "Bad flat panel table index\n");
		return -ENOENT;
	}

	/* nv4x cards need both a strap value and fpindex of 0xf to use DDC */
	if (lth.lvds_ver > 0x10)
		bios->fp_no_ddc = fpstrapping != 0xf || fpindex != 0xf;

	/*
	 * If either the strap or xlated fpindex value are 0xf there is no
	 * panel using a strap-derived bios mode present.  this condition
	 * includes, but is different from, the DDC panel indicator above
	 */
	if (fpstrapping == 0xf || fpindex == 0xf)
		return 0;

	bios->fp.mode_ptr = bios->fp.fptablepointer + headerlen +
			    recordlen * fpindex + ofs;

	NV_INFO(drm, "BIOS FP mode: %dx%d (%dkHz pixel clock)\n",
		 ROM16(bios->data[bios->fp.mode_ptr + 11]) + 1,
		 ROM16(bios->data[bios->fp.mode_ptr + 25]) + 1,
		 ROM16(bios->data[bios->fp.mode_ptr + 7]) * 10);

	return 0;
}