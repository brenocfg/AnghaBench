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
struct nvbios_init {int offset; int /*<<< orphan*/  bios; } ;

/* Variables and functions */
 int /*<<< orphan*/  nv_ro08 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  trace (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
init_reserved(struct nvbios_init *init)
{
	u8 opcode = nv_ro08(init->bios, init->offset);
	trace("RESERVED\t0x%02x\n", opcode);
	init->offset += 1;
}