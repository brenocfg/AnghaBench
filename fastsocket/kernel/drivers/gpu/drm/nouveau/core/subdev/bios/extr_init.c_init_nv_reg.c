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
typedef  int /*<<< orphan*/  u32 ;
struct nvbios_init {scalar_t__ offset; struct nouveau_bios* bios; } ;
struct nouveau_bios {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  init_mask (struct nvbios_init*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nv_ro32 (struct nouveau_bios*,scalar_t__) ; 
 int /*<<< orphan*/  trace (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
init_nv_reg(struct nvbios_init *init)
{
	struct nouveau_bios *bios = init->bios;
	u32  reg = nv_ro32(bios, init->offset + 1);
	u32 mask = nv_ro32(bios, init->offset + 5);
	u32 data = nv_ro32(bios, init->offset + 9);

	trace("NV_REG\tR[0x%06x] &= 0x%08x |= 0x%08x\n", reg, mask, data);
	init->offset += 13;

	init_mask(init, reg, ~mask, data);
}