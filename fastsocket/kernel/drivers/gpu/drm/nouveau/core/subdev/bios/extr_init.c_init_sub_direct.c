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
typedef  void* u16 ;
struct nvbios_init {void* offset; struct nouveau_bios* bios; } ;
struct nouveau_bios {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  error (char*) ; 
 scalar_t__ init_exec (struct nvbios_init*) ; 
 void* nv_ro16 (struct nouveau_bios*,void*) ; 
 scalar_t__ nvbios_exec (struct nvbios_init*) ; 
 int /*<<< orphan*/  trace (char*,void*) ; 

__attribute__((used)) static void
init_sub_direct(struct nvbios_init *init)
{
	struct nouveau_bios *bios = init->bios;
	u16 addr = nv_ro16(bios, init->offset + 1);
	u16 save;

	trace("SUB_DIRECT\t0x%04x\n", addr);

	if (init_exec(init)) {
		save = init->offset;
		init->offset = addr;
		if (nvbios_exec(init)) {
			error("error parsing sub-table\n");
			return;
		}
		init->offset = save;
	}

	init->offset += 3;
}