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
typedef  int /*<<< orphan*/  u32 ;
struct nvbios_init {scalar_t__ offset; struct nouveau_bios* bios; } ;
struct nouveau_bios {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  init_wr32 (struct nvbios_init*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nv_ro08 (struct nouveau_bios*,scalar_t__) ; 
 int /*<<< orphan*/  nv_ro32 (struct nouveau_bios*,scalar_t__) ; 
 int /*<<< orphan*/  trace (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
init_zm_reg_group(struct nvbios_init *init)
{
	struct nouveau_bios *bios = init->bios;
	u32 addr = nv_ro32(bios, init->offset + 1);
	u8 count = nv_ro08(bios, init->offset + 5);

	trace("ZM_REG_GROUP\tR[0x%06x] =\n", addr);
	init->offset += 6;

	while (count--) {
		u32 data = nv_ro32(bios, init->offset);
		trace("\t0x%08x\n", data);
		init_wr32(init, addr, data);
		init->offset += 4;
	}
}