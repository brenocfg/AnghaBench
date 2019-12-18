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
typedef  unsigned long u64 ;

/* Variables and functions */
 int /*<<< orphan*/  ia64_patch (unsigned long,int,unsigned long) ; 

void
ia64_patch_imm60 (u64 insn_addr, u64 val)
{
	/* The assembler may generate offset pointing to either slot 1
	   or slot 2 for a long (2-slot) instruction, occupying slots 1
	   and 2.  */
  	insn_addr &= -16UL;
	ia64_patch(insn_addr + 2,
		   0x011ffffe000UL, (  ((val & 0x0800000000000000UL) >> 23) /* bit 59 -> 36 */
				     | ((val & 0x00000000000fffffUL) << 13) /* bit  0 -> 13 */));
	ia64_patch(insn_addr + 1, 0x1fffffffffcUL, val >> 18);
}