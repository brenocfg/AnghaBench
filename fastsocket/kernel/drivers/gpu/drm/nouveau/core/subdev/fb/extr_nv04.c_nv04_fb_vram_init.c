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
struct TYPE_2__ {int size; int /*<<< orphan*/  type; } ;
struct nouveau_fb {TYPE_1__ ram; } ;

/* Variables and functions */
 int /*<<< orphan*/  NV04_PFB_BOOT_0 ; 
 int NV04_PFB_BOOT_0_RAM_AMOUNT ; 
#define  NV04_PFB_BOOT_0_RAM_AMOUNT_16MB 131 
#define  NV04_PFB_BOOT_0_RAM_AMOUNT_32MB 130 
#define  NV04_PFB_BOOT_0_RAM_AMOUNT_4MB 129 
#define  NV04_PFB_BOOT_0_RAM_AMOUNT_8MB 128 
 int /*<<< orphan*/  NV_MEM_TYPE_SDRAM ; 
 int /*<<< orphan*/  NV_MEM_TYPE_SGRAM ; 
 int nv_rd32 (struct nouveau_fb*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
nv04_fb_vram_init(struct nouveau_fb *pfb)
{
	u32 boot0 = nv_rd32(pfb, NV04_PFB_BOOT_0);
	if (boot0 & 0x00000100) {
		pfb->ram.size  = ((boot0 >> 12) & 0xf) * 2 + 2;
		pfb->ram.size *= 1024 * 1024;
	} else {
		switch (boot0 & NV04_PFB_BOOT_0_RAM_AMOUNT) {
		case NV04_PFB_BOOT_0_RAM_AMOUNT_32MB:
			pfb->ram.size = 32 * 1024 * 1024;
			break;
		case NV04_PFB_BOOT_0_RAM_AMOUNT_16MB:
			pfb->ram.size = 16 * 1024 * 1024;
			break;
		case NV04_PFB_BOOT_0_RAM_AMOUNT_8MB:
			pfb->ram.size = 8 * 1024 * 1024;
			break;
		case NV04_PFB_BOOT_0_RAM_AMOUNT_4MB:
			pfb->ram.size = 4 * 1024 * 1024;
			break;
		}
	}

	if ((boot0 & 0x00000038) <= 0x10)
		pfb->ram.type = NV_MEM_TYPE_SGRAM;
	else
		pfb->ram.type = NV_MEM_TYPE_SDRAM;
	return 0;
}