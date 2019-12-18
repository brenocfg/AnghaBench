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
ia64_patch_imm64 (u64 insn_addr, u64 val)
{
	/* The assembler may generate offset pointing to either slot 1
	   or slot 2 for a long (2-slot) instruction, occupying slots 1
	   and 2.  */
  	insn_addr &= -16UL;
	ia64_patch(insn_addr + 2,
		   0x01fffefe000UL, (  ((val & 0x8000000000000000UL) >> 27) /* bit 63 -> 36 */
				     | ((val & 0x0000000000200000UL) <<  0) /* bit 21 -> 21 */
				     | ((val & 0x00000000001f0000UL) <<  6) /* bit 16 -> 22 */
				     | ((val & 0x000000000000ff80UL) << 20) /* bit  7 -> 27 */
				     | ((val & 0x000000000000007fUL) << 13) /* bit  0 -> 13 */));
	ia64_patch(insn_addr + 1, 0x1ffffffffffUL, val >> 22);
}