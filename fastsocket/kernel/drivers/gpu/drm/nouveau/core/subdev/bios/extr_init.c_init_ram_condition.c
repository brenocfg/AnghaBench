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
typedef  int u8 ;
struct nvbios_init {scalar_t__ offset; struct nouveau_bios* bios; } ;
struct nouveau_bios {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  init_exec_set (struct nvbios_init*,int) ; 
 int init_rd32 (struct nvbios_init*,int) ; 
 int nv_ro08 (struct nouveau_bios*,scalar_t__) ; 
 int /*<<< orphan*/  trace (char*,int,int) ; 

__attribute__((used)) static void
init_ram_condition(struct nvbios_init *init)
{
	struct nouveau_bios *bios = init->bios;
	u8  mask = nv_ro08(bios, init->offset + 1);
	u8 value = nv_ro08(bios, init->offset + 2);

	trace("RAM_CONDITION\t"
	      "(R[0x100000] & 0x%02x) == 0x%02x\n", mask, value);
	init->offset += 3;

	if ((init_rd32(init, 0x100000) & mask) != value)
		init_exec_set(init, false);
}