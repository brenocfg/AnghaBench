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
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct nvbios_init {scalar_t__ offset; struct nouveau_bios* bios; } ;
struct nouveau_bios {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  init_prog_pll (struct nvbios_init*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int init_rdvgai (struct nvbios_init*,int /*<<< orphan*/ ,int) ; 
 int nv_ro08 (struct nouveau_bios*,scalar_t__) ; 
 int /*<<< orphan*/  nv_ro16 (struct nouveau_bios*,scalar_t__) ; 
 int /*<<< orphan*/  nv_ro32 (struct nouveau_bios*,scalar_t__) ; 
 int /*<<< orphan*/  trace (char*,...) ; 

__attribute__((used)) static void
init_io_restrict_pll2(struct nvbios_init *init)
{
	struct nouveau_bios *bios = init->bios;
	u16 port = nv_ro16(bios, init->offset + 1);
	u8 index = nv_ro08(bios, init->offset + 3);
	u8  mask = nv_ro08(bios, init->offset + 4);
	u8 shift = nv_ro08(bios, init->offset + 5);
	u8 count = nv_ro08(bios, init->offset + 6);
	u32  reg = nv_ro32(bios, init->offset + 7);
	u8  conf, i;

	trace("IO_RESTRICT_PLL2\t"
	      "R[0x%06x] =PLL= ((0x%04x[0x%02x] & 0x%02x) >> 0x%02x) [{\n",
	      reg, port, index, mask, shift);
	init->offset += 11;

	conf = (init_rdvgai(init, port, index) & mask) >> shift;
	for (i = 0; i < count; i++) {
		u32 freq = nv_ro32(bios, init->offset);
		if (i == conf) {
			trace("\t%dkHz *\n", freq);
			init_prog_pll(init, reg, freq);
		} else {
			trace("\t%dkHz\n", freq);
		}
		init->offset += 4;
	}
	trace("}]\n");
}