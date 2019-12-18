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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
struct nvbios_init {scalar_t__ offset; struct nouveau_bios* bios; } ;
struct nouveau_bios {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  init_wr32 (struct nvbios_init*,int,int) ; 
 int /*<<< orphan*/  nv_ro08 (struct nouveau_bios*,scalar_t__) ; 
 int nv_ro32 (struct nouveau_bios*,scalar_t__) ; 
 int /*<<< orphan*/  trace (char*,int,...) ; 

__attribute__((used)) static void
init_zm_reg_sequence(struct nvbios_init *init)
{
	struct nouveau_bios *bios = init->bios;
	u32 base = nv_ro32(bios, init->offset + 1);
	u8 count = nv_ro08(bios, init->offset + 5);

	trace("ZM_REG_SEQUENCE\t0x%02x\n", count);
	init->offset += 6;

	while (count--) {
		u32 data = nv_ro32(bios, init->offset);

		trace("\t\tR[0x%06x] = 0x%08x\n", base, data);
		init->offset += 4;

		init_wr32(init, base, data);
		base += 4;
	}
}