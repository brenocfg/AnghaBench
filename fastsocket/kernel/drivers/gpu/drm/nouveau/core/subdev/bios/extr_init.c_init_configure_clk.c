#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u16 ;
struct nvbios_init {int offset; struct nouveau_bios* bios; } ;
struct TYPE_2__ {int major; } ;
struct nouveau_bios {TYPE_1__ version; } ;

/* Variables and functions */
 int init_configure_mem_clk (struct nvbios_init*) ; 
 int /*<<< orphan*/  init_done (struct nvbios_init*) ; 
 int /*<<< orphan*/  init_exec_force (struct nvbios_init*,int) ; 
 int /*<<< orphan*/  init_prog_pll (struct nvbios_init*,int,int) ; 
 int nv_ro08 (struct nouveau_bios*,int) ; 
 int nv_ro16 (struct nouveau_bios*,int) ; 
 int /*<<< orphan*/  trace (char*) ; 

__attribute__((used)) static void
init_configure_clk(struct nvbios_init *init)
{
	struct nouveau_bios *bios = init->bios;
	u16 mdata, clock;

	trace("CONFIGURE_CLK\n");
	init->offset += 1;

	if (bios->version.major > 2) {
		init_done(init);
		return;
	}
	init_exec_force(init, true);

	mdata = init_configure_mem_clk(init);

	/* NVPLL */
	clock = nv_ro16(bios, mdata + 4) * 10;
	init_prog_pll(init, 0x680500, clock);

	/* MPLL */
	clock = nv_ro16(bios, mdata + 2) * 10;
	if (nv_ro08(bios, mdata) & 0x01)
		clock *= 2;
	init_prog_pll(init, 0x680504, clock);

	init_exec_force(init, false);
}