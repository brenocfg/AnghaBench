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
struct nvbios_init {scalar_t__ offset; struct nouveau_bios* bios; } ;
struct nouveau_bios {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  init_rdvgai (struct nvbios_init*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_wrvgai (struct nvbios_init*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nv_ro08 (struct nouveau_bios*,scalar_t__) ; 
 int /*<<< orphan*/  trace (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
init_cr_idx_adr_latch(struct nvbios_init *init)
{
	struct nouveau_bios *bios = init->bios;
	u8 addr0 = nv_ro08(bios, init->offset + 1);
	u8 addr1 = nv_ro08(bios, init->offset + 2);
	u8  base = nv_ro08(bios, init->offset + 3);
	u8 count = nv_ro08(bios, init->offset + 4);
	u8 save0;

	trace("CR_INDEX_ADDR C[%02x] C[%02x]\n", addr0, addr1);
	init->offset += 5;

	save0 = init_rdvgai(init, 0x03d4, addr0);
	while (count--) {
		u8 data = nv_ro08(bios, init->offset);

		trace("\t\t[0x%02x] = 0x%02x\n", base, data);
		init->offset += 1;

		init_wrvgai(init, 0x03d4, addr0, base++);
		init_wrvgai(init, 0x03d4, addr1, data);
	}
	init_wrvgai(init, 0x03d4, addr0, save0);
}