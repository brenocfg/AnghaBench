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
typedef  scalar_t__ u8 ;
typedef  scalar_t__ u32 ;
struct nvbios_init {scalar_t__ offset; struct nouveau_bios* bios; } ;
struct nouveau_bios {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  init_prog_pll (struct nvbios_init*,scalar_t__,scalar_t__) ; 
 scalar_t__ init_ram_restrict (struct nvbios_init*) ; 
 scalar_t__ init_ram_restrict_group_count (struct nvbios_init*) ; 
 scalar_t__ nv_ro08 (struct nouveau_bios*,scalar_t__) ; 
 scalar_t__ nv_ro32 (struct nouveau_bios*,scalar_t__) ; 
 int /*<<< orphan*/  trace (char*,scalar_t__) ; 

__attribute__((used)) static void
init_ram_restrict_pll(struct nvbios_init *init)
{
	struct nouveau_bios *bios = init->bios;
	u8  type = nv_ro08(bios, init->offset + 1);
	u8 count = init_ram_restrict_group_count(init);
	u8 strap = init_ram_restrict(init);
	u8 cconf;

	trace("RAM_RESTRICT_PLL\t0x%02x\n", type);
	init->offset += 2;

	for (cconf = 0; cconf < count; cconf++) {
		u32 freq = nv_ro32(bios, init->offset);

		if (cconf == strap) {
			trace("%dkHz *\n", freq);
			init_prog_pll(init, type, freq);
		} else {
			trace("%dkHz\n", freq);
		}

		init->offset += 4;
	}
}