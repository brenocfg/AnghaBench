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
struct TYPE_2__ {scalar_t__* opcode; int /*<<< orphan*/ * addr; } ;

/* Variables and functions */
 int gdbstub_flush_caches ; 
 int /*<<< orphan*/  gdbstub_write_byte (scalar_t__,int /*<<< orphan*/ *) ; 
 TYPE_1__* step_bp ; 

__attribute__((used)) static inline void __gdbstub_restore_bp(void)
{
#ifdef GDBSTUB_USE_F7F7_AS_BREAKPOINT
	if (step_bp[0].addr) {
		gdbstub_write_byte(step_bp[0].opcode[0], step_bp[0].addr + 0);
		gdbstub_write_byte(step_bp[0].opcode[1], step_bp[0].addr + 1);
	}
	if (step_bp[1].addr) {
		gdbstub_write_byte(step_bp[1].opcode[0], step_bp[1].addr + 0);
		gdbstub_write_byte(step_bp[1].opcode[1], step_bp[1].addr + 1);
	}
#else
	if (step_bp[0].addr)
		gdbstub_write_byte(step_bp[0].opcode[0], step_bp[0].addr + 0);
	if (step_bp[1].addr)
		gdbstub_write_byte(step_bp[1].opcode[0], step_bp[1].addr + 0);
#endif

	gdbstub_flush_caches = 1;

	step_bp[0].addr		= NULL;
	step_bp[0].opcode[0]	= 0;
	step_bp[0].opcode[1]	= 0;
	step_bp[1].addr		= NULL;
	step_bp[1].opcode[0]	= 0;
	step_bp[1].opcode[1]	= 0;
}