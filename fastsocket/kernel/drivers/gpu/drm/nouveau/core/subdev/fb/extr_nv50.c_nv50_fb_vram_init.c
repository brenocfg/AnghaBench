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
struct TYPE_2__ {int size; int stolen; int ranks; int /*<<< orphan*/  type; } ;
struct nouveau_fb {TYPE_1__ ram; int /*<<< orphan*/  vram; } ;
struct nouveau_device {int chipset; } ;
struct nouveau_bios {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  NV_MEM_TYPE_DDR1 ; 
 int /*<<< orphan*/  NV_MEM_TYPE_DDR2 ; 
 int /*<<< orphan*/  NV_MEM_TYPE_DDR3 ; 
 int /*<<< orphan*/  NV_MEM_TYPE_GDDR3 ; 
 int /*<<< orphan*/  NV_MEM_TYPE_GDDR4 ; 
 int /*<<< orphan*/  NV_MEM_TYPE_GDDR5 ; 
 int /*<<< orphan*/  NV_MEM_TYPE_STOLEN ; 
 struct nouveau_bios* nouveau_bios (struct nouveau_device*) ; 
 int /*<<< orphan*/  nouveau_fb_bios_memtype (struct nouveau_bios*) ; 
 int nouveau_mm_init (int /*<<< orphan*/ *,int const,int,int) ; 
 int nv50_fb_vram_rblock (struct nouveau_fb*) ; 
 struct nouveau_device* nv_device (struct nouveau_fb*) ; 
 int nv_rd32 (struct nouveau_fb*,int) ; 

__attribute__((used)) static int
nv50_fb_vram_init(struct nouveau_fb *pfb)
{
	struct nouveau_device *device = nv_device(pfb);
	struct nouveau_bios *bios = nouveau_bios(device);
	const u32 rsvd_head = ( 256 * 1024) >> 12; /* vga memory */
	const u32 rsvd_tail = (1024 * 1024) >> 12; /* vbios etc */
	u32 size, tags = 0;
	int ret;

	pfb->ram.size = nv_rd32(pfb, 0x10020c);
	pfb->ram.size = (pfb->ram.size & 0xffffff00) |
		       ((pfb->ram.size & 0x000000ff) << 32);

	size = (pfb->ram.size >> 12) - rsvd_head - rsvd_tail;
	switch (device->chipset) {
	case 0xaa:
	case 0xac:
	case 0xaf: /* IGPs, no reordering, no real VRAM */
		ret = nouveau_mm_init(&pfb->vram, rsvd_head, size, 1);
		if (ret)
			return ret;

		pfb->ram.type   = NV_MEM_TYPE_STOLEN;
		pfb->ram.stolen = (u64)nv_rd32(pfb, 0x100e10) << 12;
		break;
	default:
		switch (nv_rd32(pfb, 0x100714) & 0x00000007) {
		case 0: pfb->ram.type = NV_MEM_TYPE_DDR1; break;
		case 1:
			if (nouveau_fb_bios_memtype(bios) == NV_MEM_TYPE_DDR3)
				pfb->ram.type = NV_MEM_TYPE_DDR3;
			else
				pfb->ram.type = NV_MEM_TYPE_DDR2;
			break;
		case 2: pfb->ram.type = NV_MEM_TYPE_GDDR3; break;
		case 3: pfb->ram.type = NV_MEM_TYPE_GDDR4; break;
		case 4: pfb->ram.type = NV_MEM_TYPE_GDDR5; break;
		default:
			break;
		}

		ret = nouveau_mm_init(&pfb->vram, rsvd_head, size,
				      nv50_fb_vram_rblock(pfb) >> 12);
		if (ret)
			return ret;

		pfb->ram.ranks = (nv_rd32(pfb, 0x100200) & 0x4) ? 2 : 1;
		tags = nv_rd32(pfb, 0x100320);
		break;
	}

	return tags;
}