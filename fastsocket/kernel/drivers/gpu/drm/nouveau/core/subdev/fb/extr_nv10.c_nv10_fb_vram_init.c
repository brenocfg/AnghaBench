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
 int /*<<< orphan*/  NV_MEM_TYPE_DDR1 ; 
 int /*<<< orphan*/  NV_MEM_TYPE_SDRAM ; 
 int nv_rd32 (struct nouveau_fb*,int) ; 

__attribute__((used)) static int
nv10_fb_vram_init(struct nouveau_fb *pfb)
{
	u32 cfg0 = nv_rd32(pfb, 0x100200);
	if (cfg0 & 0x00000001)
		pfb->ram.type = NV_MEM_TYPE_DDR1;
	else
		pfb->ram.type = NV_MEM_TYPE_SDRAM;

	pfb->ram.size = nv_rd32(pfb, 0x10020c) & 0xff000000;
	return 0;
}