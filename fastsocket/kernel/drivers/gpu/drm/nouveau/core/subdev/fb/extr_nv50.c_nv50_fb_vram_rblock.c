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
typedef  int u64 ;
typedef  int u32 ;
struct TYPE_2__ {int size; } ;
struct nouveau_fb {TYPE_1__ ram; } ;

/* Variables and functions */
 int /*<<< orphan*/  nv_debug (struct nouveau_fb*,char*,int,...) ; 
 int nv_rd32 (struct nouveau_fb*,int) ; 
 int /*<<< orphan*/  nv_warn (struct nouveau_fb*,char*,int) ; 

__attribute__((used)) static u32
nv50_fb_vram_rblock(struct nouveau_fb *pfb)
{
	int i, parts, colbits, rowbitsa, rowbitsb, banks;
	u64 rowsize, predicted;
	u32 r0, r4, rt, ru, rblock_size;

	r0 = nv_rd32(pfb, 0x100200);
	r4 = nv_rd32(pfb, 0x100204);
	rt = nv_rd32(pfb, 0x100250);
	ru = nv_rd32(pfb, 0x001540);
	nv_debug(pfb, "memcfg 0x%08x 0x%08x 0x%08x 0x%08x\n", r0, r4, rt, ru);

	for (i = 0, parts = 0; i < 8; i++) {
		if (ru & (0x00010000 << i))
			parts++;
	}

	colbits  =  (r4 & 0x0000f000) >> 12;
	rowbitsa = ((r4 & 0x000f0000) >> 16) + 8;
	rowbitsb = ((r4 & 0x00f00000) >> 20) + 8;
	banks    = 1 << (((r4 & 0x03000000) >> 24) + 2);

	rowsize = parts * banks * (1 << colbits) * 8;
	predicted = rowsize << rowbitsa;
	if (r0 & 0x00000004)
		predicted += rowsize << rowbitsb;

	if (predicted != pfb->ram.size) {
		nv_warn(pfb, "memory controller reports %d MiB VRAM\n",
			(u32)(pfb->ram.size >> 20));
	}

	rblock_size = rowsize;
	if (rt & 1)
		rblock_size *= 3;

	nv_debug(pfb, "rblock %d bytes\n", rblock_size);
	return rblock_size;
}