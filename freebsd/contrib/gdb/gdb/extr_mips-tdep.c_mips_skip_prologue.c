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
typedef  scalar_t__ CORE_ADDR ;

/* Variables and functions */
 scalar_t__ after_prologue (scalar_t__,int /*<<< orphan*/ *) ; 
 scalar_t__ max (scalar_t__,scalar_t__) ; 
 scalar_t__ mips16_skip_prologue (scalar_t__) ; 
 scalar_t__ mips32_skip_prologue (scalar_t__) ; 
 scalar_t__ pc_is_mips16 (scalar_t__) ; 

__attribute__((used)) static CORE_ADDR
mips_skip_prologue (CORE_ADDR pc)
{
  /* See if we can determine the end of the prologue via the symbol table.
     If so, then return either PC, or the PC after the prologue, whichever
     is greater.  */

  CORE_ADDR post_prologue_pc = after_prologue (pc, NULL);

  if (post_prologue_pc != 0)
    return max (pc, post_prologue_pc);

  /* Can't determine prologue from the symbol table, need to examine
     instructions.  */

  if (pc_is_mips16 (pc))
    return mips16_skip_prologue (pc);
  else
    return mips32_skip_prologue (pc);
}