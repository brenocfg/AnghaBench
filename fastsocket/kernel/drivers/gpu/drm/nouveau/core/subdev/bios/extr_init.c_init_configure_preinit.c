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
typedef  int u32 ;
struct nvbios_init {int offset; struct nouveau_bios* bios; } ;
struct TYPE_2__ {int major; } ;
struct nouveau_bios {TYPE_1__ version; } ;

/* Variables and functions */
 int /*<<< orphan*/  init_done (struct nvbios_init*) ; 
 int /*<<< orphan*/  init_exec_force (struct nvbios_init*,int) ; 
 int init_rd32 (struct nvbios_init*,int) ; 
 int /*<<< orphan*/  init_wrvgai (struct nvbios_init*,int,int,int) ; 
 int /*<<< orphan*/  trace (char*) ; 

__attribute__((used)) static void
init_configure_preinit(struct nvbios_init *init)
{
	struct nouveau_bios *bios = init->bios;
	u32 strap;

	trace("CONFIGURE_PREINIT\n");
	init->offset += 1;

	if (bios->version.major > 2) {
		init_done(init);
		return;
	}
	init_exec_force(init, true);

	strap = init_rd32(init, 0x101000);
	strap = ((strap << 2) & 0xf0) | ((strap & 0x40) >> 6);
	init_wrvgai(init, 0x03d4, 0x3c, strap);

	init_exec_force(init, false);
}