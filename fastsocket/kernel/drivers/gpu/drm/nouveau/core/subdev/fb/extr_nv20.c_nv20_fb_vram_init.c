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
typedef  int u32 ;
struct TYPE_2__ {int size; int parts; int /*<<< orphan*/  type; } ;
struct nouveau_fb {TYPE_1__ ram; } ;

/* Variables and functions */
 int /*<<< orphan*/  NV_MEM_TYPE_DDR1 ; 
 int /*<<< orphan*/  NV_MEM_TYPE_GDDR2 ; 
 int /*<<< orphan*/  NV_MEM_TYPE_GDDR3 ; 
 int /*<<< orphan*/  NV_MEM_TYPE_SDRAM ; 
 int nv_rd32 (struct nouveau_fb*,int) ; 

int
nv20_fb_vram_init(struct nouveau_fb *pfb)
{
	u32 pbus1218 = nv_rd32(pfb, 0x001218);

	switch (pbus1218 & 0x00000300) {
	case 0x00000000: pfb->ram.type = NV_MEM_TYPE_SDRAM; break;
	case 0x00000100: pfb->ram.type = NV_MEM_TYPE_DDR1; break;
	case 0x00000200: pfb->ram.type = NV_MEM_TYPE_GDDR3; break;
	case 0x00000300: pfb->ram.type = NV_MEM_TYPE_GDDR2; break;
	}
	pfb->ram.size  = (nv_rd32(pfb, 0x10020c) & 0xff000000);
	pfb->ram.parts = (nv_rd32(pfb, 0x100200) & 0x00000003) + 1;

	return nv_rd32(pfb, 0x100320);
}