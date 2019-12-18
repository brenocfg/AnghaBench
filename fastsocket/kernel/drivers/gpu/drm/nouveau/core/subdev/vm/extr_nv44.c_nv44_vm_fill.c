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
typedef  int u32 ;
struct nouveau_gpuobj {int dummy; } ;
typedef  int dma_addr_t ;

/* Variables and functions */
 int nv_ro32 (struct nouveau_gpuobj*,int) ; 
 int /*<<< orphan*/  nv_wo32 (struct nouveau_gpuobj*,int,int) ; 

__attribute__((used)) static void
nv44_vm_fill(struct nouveau_gpuobj *pgt, dma_addr_t null,
	     dma_addr_t *list, u32 pte, u32 cnt)
{
	u32 base = (pte << 2) & ~0x0000000f;
	u32 tmp[4];

	tmp[0] = nv_ro32(pgt, base + 0x0);
	tmp[1] = nv_ro32(pgt, base + 0x4);
	tmp[2] = nv_ro32(pgt, base + 0x8);
	tmp[3] = nv_ro32(pgt, base + 0xc);

	while (cnt--) {
		u32 addr = list ? (*list++ >> 12) : (null >> 12);
		switch (pte++ & 0x3) {
		case 0:
			tmp[0] &= ~0x07ffffff;
			tmp[0] |= addr;
			break;
		case 1:
			tmp[0] &= ~0xf8000000;
			tmp[0] |= addr << 27;
			tmp[1] &= ~0x003fffff;
			tmp[1] |= addr >> 5;
			break;
		case 2:
			tmp[1] &= ~0xffc00000;
			tmp[1] |= addr << 22;
			tmp[2] &= ~0x0001ffff;
			tmp[2] |= addr >> 10;
			break;
		case 3:
			tmp[2] &= ~0xfffe0000;
			tmp[2] |= addr << 17;
			tmp[3] &= ~0x00000fff;
			tmp[3] |= addr >> 15;
			break;
		}
	}

	nv_wo32(pgt, base + 0x0, tmp[0]);
	nv_wo32(pgt, base + 0x4, tmp[1]);
	nv_wo32(pgt, base + 0x8, tmp[2]);
	nv_wo32(pgt, base + 0xc, tmp[3] | 0x40000000);
}