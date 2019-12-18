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
 int /*<<< orphan*/  init_rd32 (struct nvbios_init*,int) ; 
 int init_shift (int /*<<< orphan*/ ,int) ; 
 int init_xlat_ (struct nvbios_init*,int,int) ; 
 int nv_ro08 (struct nouveau_bios*,scalar_t__) ; 
 int nv_ro32 (struct nouveau_bios*,scalar_t__) ; 
 int /*<<< orphan*/  trace (char*,int,int,int,int,char*,int,int,int) ; 

__attribute__((used)) static void
init_xlat(struct nvbios_init *init)
{
	struct nouveau_bios *bios = init->bios;
	u32 saddr = nv_ro32(bios, init->offset + 1);
	u8 sshift = nv_ro08(bios, init->offset + 5);
	u8  smask = nv_ro08(bios, init->offset + 6);
	u8  index = nv_ro08(bios, init->offset + 7);
	u32 daddr = nv_ro32(bios, init->offset + 8);
	u32 dmask = nv_ro32(bios, init->offset + 12);
	u8  shift = nv_ro08(bios, init->offset + 16);
	u32 data;

	trace("INIT_XLAT\tR[0x%06x] &= 0x%08x |= "
	      "(X%02x((R[0x%06x] %s 0x%02x) & 0x%02x) << 0x%02x)\n",
	      daddr, dmask, index, saddr, (sshift & 0x80) ? "<<" : ">>",
	      (sshift & 0x80) ? (0x100 - sshift) : sshift, smask, shift);
	init->offset += 17;

	data = init_shift(init_rd32(init, saddr), sshift) & smask;
	data = init_xlat_(init, index, data) << shift;
	init_mask(init, daddr, ~dmask, data);
}