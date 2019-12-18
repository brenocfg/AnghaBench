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
typedef  int u8 ;
typedef  int u32 ;
struct nvbios_init {scalar_t__ offset; struct nouveau_bios* bios; } ;
struct nouveau_bios {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  init_mask (struct nvbios_init*,int,int,int) ; 
 int /*<<< orphan*/  init_wr32 (struct nvbios_init*,int,int) ; 
 int nv_ro08 (struct nouveau_bios*,scalar_t__) ; 
 int nv_ro32 (struct nouveau_bios*,scalar_t__) ; 
 int /*<<< orphan*/  trace (char*,int,int,...) ; 

__attribute__((used)) static void
init_idx_addr_latched(struct nvbios_init *init)
{
	struct nouveau_bios *bios = init->bios;
	u32 creg = nv_ro32(bios, init->offset + 1);
	u32 dreg = nv_ro32(bios, init->offset + 5);
	u32 mask = nv_ro32(bios, init->offset + 9);
	u32 data = nv_ro32(bios, init->offset + 13);
	u8 count = nv_ro08(bios, init->offset + 17);

	trace("INDEX_ADDRESS_LATCHED\t"
	      "R[0x%06x] : R[0x%06x]\n\tCTRL &= 0x%08x |= 0x%08x\n",
	      creg, dreg, mask, data);
	init->offset += 18;

	while (count--) {
		u8 iaddr = nv_ro08(bios, init->offset + 0);
		u8 idata = nv_ro08(bios, init->offset + 1);

		trace("\t[0x%02x] = 0x%02x\n", iaddr, idata);
		init->offset += 2;

		init_wr32(init, dreg, idata);
		init_mask(init, creg, ~mask, data | iaddr);
	}
}