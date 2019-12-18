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
typedef  int u16 ;
struct nvbios_init {struct nouveau_bios* bios; } ;
struct TYPE_2__ {int major; } ;
struct nouveau_bios {int bmp_offset; TYPE_1__ version; } ;

/* Variables and functions */
 int bmp_version (struct nouveau_bios*) ; 
 int init_script_table (struct nvbios_init*) ; 
 int nv_ro16 (struct nouveau_bios*,int) ; 

__attribute__((used)) static u16
init_script(struct nouveau_bios *bios, int index)
{
	struct nvbios_init init = { .bios = bios };
	u16 data;

	if (bmp_version(bios) && bmp_version(bios) < 0x0510) {
		if (index > 1)
			return 0x0000;

		data = bios->bmp_offset + (bios->version.major < 2 ? 14 : 18);
		return nv_ro16(bios, data + (index * 2));
	}

	data = init_script_table(&init);
	if (data)
		return nv_ro16(bios, data + (index * 2));

	return 0x0000;
}