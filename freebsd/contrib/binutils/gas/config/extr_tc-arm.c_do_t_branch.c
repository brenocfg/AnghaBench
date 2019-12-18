#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int pc_rel; int /*<<< orphan*/  type; } ;
struct TYPE_4__ {int cond; int instruction; int size_req; int relax; TYPE_1__ reloc; } ;

/* Variables and functions */
 int /*<<< orphan*/  BAD_BRANCH ; 
 int /*<<< orphan*/  BFD_RELOC_THUMB_PCREL_BRANCH12 ; 
 int /*<<< orphan*/  BFD_RELOC_THUMB_PCREL_BRANCH20 ; 
 int /*<<< orphan*/  BFD_RELOC_THUMB_PCREL_BRANCH25 ; 
 int /*<<< orphan*/  BFD_RELOC_THUMB_PCREL_BRANCH9 ; 
 int COND_ALWAYS ; 
 int THUMB_OP16 (int) ; 
 int THUMB_OP32 (int) ; 
 int T_MNEM_bcond ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  constraint (int,int /*<<< orphan*/ ) ; 
 int current_it_mask ; 
 TYPE_2__ inst ; 
 scalar_t__ unified_syntax ; 

__attribute__((used)) static void
do_t_branch (void)
{
  int opcode;
  int cond;

  if (current_it_mask)
    {
      /* Conditional branches inside IT blocks are encoded as unconditional
         branches.  */
      cond = COND_ALWAYS;
      /* A branch must be the last instruction in an IT block.  */
      constraint (current_it_mask != 0x10, BAD_BRANCH);
    }
  else
    cond = inst.cond;

  if (cond != COND_ALWAYS)
    opcode = T_MNEM_bcond;
  else
    opcode = inst.instruction;

  if (unified_syntax && inst.size_req == 4)
    {
      inst.instruction = THUMB_OP32(opcode);
      if (cond == COND_ALWAYS)
	inst.reloc.type = BFD_RELOC_THUMB_PCREL_BRANCH25;
      else
	{
	  assert (cond != 0xF);
	  inst.instruction |= cond << 22;
	  inst.reloc.type = BFD_RELOC_THUMB_PCREL_BRANCH20;
	}
    }
  else
    {
      inst.instruction = THUMB_OP16(opcode);
      if (cond == COND_ALWAYS)
	inst.reloc.type = BFD_RELOC_THUMB_PCREL_BRANCH12;
      else
	{
	  inst.instruction |= cond << 8;
	  inst.reloc.type = BFD_RELOC_THUMB_PCREL_BRANCH9;
	}
      /* Allow section relaxation.  */
      if (unified_syntax && inst.size_req != 2)
	inst.relax = opcode;
    }

  inst.reloc.pc_rel = 1;
}