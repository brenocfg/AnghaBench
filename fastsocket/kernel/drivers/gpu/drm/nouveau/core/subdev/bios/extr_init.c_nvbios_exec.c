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
typedef  size_t u8 ;
struct nvbios_init {int /*<<< orphan*/  nested; scalar_t__ offset; int /*<<< orphan*/  bios; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* exec ) (struct nvbios_init*) ;} ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  error (char*,size_t) ; 
 TYPE_1__* init_opcode ; 
 size_t init_opcode_nr ; 
 size_t nv_ro08 (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  stub1 (struct nvbios_init*) ; 

int
nvbios_exec(struct nvbios_init *init)
{
	init->nested++;
	while (init->offset) {
		u8 opcode = nv_ro08(init->bios, init->offset);
		if (opcode >= init_opcode_nr || !init_opcode[opcode].exec) {
			error("unknown opcode 0x%02x\n", opcode);
			return -EINVAL;
		}

		init_opcode[opcode].exec(init);
	}
	init->nested--;
	return 0;
}