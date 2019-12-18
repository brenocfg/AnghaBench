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
typedef  scalar_t__ u16 ;
struct nvbios_init {scalar_t__ repeat; scalar_t__ repend; scalar_t__ offset; struct nouveau_bios* bios; } ;
struct nouveau_bios {int dummy; } ;

/* Variables and functions */
 scalar_t__ nv_ro08 (struct nouveau_bios*,scalar_t__) ; 
 int /*<<< orphan*/  nvbios_exec (struct nvbios_init*) ; 
 int /*<<< orphan*/  trace (char*,scalar_t__) ; 

__attribute__((used)) static void
init_repeat(struct nvbios_init *init)
{
	struct nouveau_bios *bios = init->bios;
	u8 count = nv_ro08(bios, init->offset + 1);
	u16 repeat = init->repeat;

	trace("REPEAT\t0x%02x\n", count);
	init->offset += 2;

	init->repeat = init->offset;
	init->repend = init->offset;
	while (count--) {
		init->offset = init->repeat;
		nvbios_exec(init);
		if (count)
			trace("REPEAT\t0x%02x\n", count);
	}
	init->offset = init->repend;
	init->repeat = repeat;
}