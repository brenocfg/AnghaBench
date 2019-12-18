#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ sec_count; int* sec_offset; } ;
typedef  TYPE_1__ vapi_sec_info_t ;
struct TYPE_5__ {TYPE_1__* sectors; } ;
typedef  TYPE_2__ vapi_additional_info_t ;
typedef  int ULONG ;
typedef  size_t UBYTE ;

/* Variables and functions */
 scalar_t__ BINLOAD_start_binloading ; 
 scalar_t__ BOOT_SECTORS_LOGICAL ; 
 scalar_t__ BOOT_SECTORS_PHYSICAL ; 
 scalar_t__ IMAGE_TYPE_ATR ; 
 scalar_t__ IMAGE_TYPE_PRO ; 
 scalar_t__ IMAGE_TYPE_VAPI ; 
 TYPE_2__** additional_info ; 
 scalar_t__* boot_sectors_type ; 
 scalar_t__* image_type ; 
 int* sectorcount ; 
 int* sectorsize ; 

void SIO_SizeOfSector(UBYTE unit, int sector, int *sz, ULONG *ofs)
{
	int size;
	ULONG offset;
	int header_size = (image_type[unit] == IMAGE_TYPE_ATR ? 16 : 0);

	if (BINLOAD_start_binloading) {
		if (sz)
			*sz = 128;
		if (ofs)
			*ofs = 0;
		return;
	}

	if (image_type[unit] == IMAGE_TYPE_PRO) {
		size = 128;
		offset = 16 + (128+12)*(sector -1); /* returns offset of header */
	}
	else if (image_type[unit] == IMAGE_TYPE_VAPI) {
		vapi_additional_info_t *info;
		vapi_sec_info_t *secinfo;

		size = 128;
		info = additional_info[unit];
		if (info == NULL)
			offset = 0;
		else if (sector > sectorcount[unit])
			offset = 0;
		else {
			secinfo = &info->sectors[sector-1];
			if (secinfo->sec_count == 0  )
				offset = 0;
			else
				offset = secinfo->sec_offset[0];
		}
	}
	else if (sector < 4) {
		/* special case for first three sectors in ATR and XFD image */
		size = 128;
		offset = header_size + (sector - 1) * (boot_sectors_type[unit] == BOOT_SECTORS_PHYSICAL ? 256 : 128);
	}
	else {
		size = sectorsize[unit];
		offset = header_size + (boot_sectors_type[unit] == BOOT_SECTORS_LOGICAL ? 0x180 : 0x300) + (sector - 4) * size;
	}

	if (sz)
		*sz = size;

	if (ofs)
		*ofs = offset;
}