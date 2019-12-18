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
 int /*<<< orphan*/  init_rd32 (struct nvbios_init*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_wr32 (struct nvbios_init*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nv_ro32 (struct nouveau_bios*,scalar_t__) ; 
 int /*<<< orphan*/  trace (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
init_copy_zm_reg(struct nvbios_init *init)
{
	struct nouveau_bios *bios = init->bios;
	u32 sreg = nv_ro32(bios, init->offset + 1);
	u32 dreg = nv_ro32(bios, init->offset + 5);

	trace("COPY_ZM_REG\tR[0x%06x] = R[0x%06x]\n", dreg, sreg);
	init->offset += 9;

	init_wr32(init, dreg, init_rd32(init, sreg));
}