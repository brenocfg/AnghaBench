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
struct TYPE_4__ {int instruction; TYPE_1__* operands; } ;
struct TYPE_3__ {int imm; int /*<<< orphan*/  reg; } ;

/* Variables and functions */
 int HI1 (int /*<<< orphan*/ ) ; 
 int LOW4 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NS_DLD ; 
 int N_8 ; 
 int /*<<< orphan*/  N_EQK ; 
 int N_KEY ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  first_error (int /*<<< orphan*/ ) ; 
 TYPE_2__ inst ; 
 int /*<<< orphan*/  neon_check_type (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 unsigned int neon_dp_fixup (unsigned int) ; 

__attribute__((used)) static void
do_neon_tbl_tbx (void)
{
  unsigned listlenbits;
  neon_check_type (3, NS_DLD, N_EQK, N_EQK, N_8 | N_KEY);
  
  if (inst.operands[1].imm < 1 || inst.operands[1].imm > 4)
    {
      first_error (_("bad list length for table lookup"));
      return;
    }
  
  listlenbits = inst.operands[1].imm - 1;
  inst.instruction |= LOW4 (inst.operands[0].reg) << 12;
  inst.instruction |= HI1 (inst.operands[0].reg) << 22;
  inst.instruction |= LOW4 (inst.operands[1].reg) << 16;
  inst.instruction |= HI1 (inst.operands[1].reg) << 7;
  inst.instruction |= LOW4 (inst.operands[2].reg);
  inst.instruction |= HI1 (inst.operands[2].reg) << 5;
  inst.instruction |= listlenbits << 8;
  
  inst.instruction = neon_dp_fixup (inst.instruction);
}