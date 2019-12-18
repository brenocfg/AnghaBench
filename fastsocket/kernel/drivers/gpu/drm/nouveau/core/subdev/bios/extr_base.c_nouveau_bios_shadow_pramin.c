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
typedef  int u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct nouveau_device {scalar_t__ card_type; } ;
struct nouveau_bios {int size; scalar_t__ data; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ NV_50 ; 
 scalar_t__ kmalloc (int,int /*<<< orphan*/ ) ; 
 struct nouveau_device* nv_device (struct nouveau_bios*) ; 
 int /*<<< orphan*/  nv_mask (struct nouveau_bios*,int,int,int) ; 
 int nv_rd08 (struct nouveau_bios*,int) ; 
 int nv_rd32 (struct nouveau_bios*,int) ; 
 int /*<<< orphan*/  nv_wo08 (struct nouveau_bios*,int,int) ; 
 int /*<<< orphan*/  nv_wr32 (struct nouveau_bios*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
nouveau_bios_shadow_pramin(struct nouveau_bios *bios)
{
	struct nouveau_device *device = nv_device(bios);
	u32 bar0 = 0;
	int i;

	if (device->card_type >= NV_50) {
		u64 addr = (u64)(nv_rd32(bios, 0x619f04) & 0xffffff00) << 8;
		if (!addr) {
			addr  = (u64)nv_rd32(bios, 0x001700) << 16;
			addr += 0xf0000;
		}

		bar0 = nv_mask(bios, 0x001700, 0xffffffff, addr >> 16);
	}

	/* bail if no rom signature */
	if (nv_rd08(bios, 0x700000) != 0x55 ||
	    nv_rd08(bios, 0x700001) != 0xaa)
		goto out;

	bios->size = nv_rd08(bios, 0x700002) * 512;
	if (!bios->size)
		goto out;

	bios->data = kmalloc(bios->size, GFP_KERNEL);
	if (bios->data) {
		for (i = 0; i < bios->size; i++)
			nv_wo08(bios, i, nv_rd08(bios, 0x700000 + i));
	}

out:
	if (device->card_type >= NV_50)
		nv_wr32(bios, 0x001700, bar0);
}