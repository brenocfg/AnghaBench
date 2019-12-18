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
struct neon_type_el {scalar_t__ type; int size; } ;
struct TYPE_4__ {int instruction; TYPE_1__* operands; } ;
struct TYPE_3__ {int imm; int immisalign; } ;

/* Variables and functions */
 int FAIL ; 
 int NEON_REGLIST_LENGTH (int) ; 
 int NEON_REG_STRIDE (int) ; 
 int /*<<< orphan*/  NS_NULL ; 
 scalar_t__ NT_invtype ; 
 int N_16 ; 
 int N_32 ; 
 int N_8 ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  constraint (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  first_error (int /*<<< orphan*/ ) ; 
 TYPE_2__ inst ; 
 int neon_alignment_bit (int,int,int*,int,int,int,int,int,...) ; 
 struct neon_type_el neon_check_type (int,int /*<<< orphan*/ ,int) ; 
 int neon_logbits (int) ; 

__attribute__((used)) static void
do_neon_ld_dup (void)
{
  struct neon_type_el et = neon_check_type (1, NS_NULL, N_8 | N_16 | N_32);
  int align_good, do_align = 0;

  if (et.type == NT_invtype)
    return;

  switch ((inst.instruction >> 8) & 3)
    {
    case 0:  /* VLD1.  */
      assert (NEON_REG_STRIDE (inst.operands[0].imm) != 2);
      align_good = neon_alignment_bit (et.size, inst.operands[1].imm >> 8,
                                       &do_align, 16, 16, 32, 32, -1);
      if (align_good == FAIL)
        return;
      switch (NEON_REGLIST_LENGTH (inst.operands[0].imm))
        {
        case 1: break;
        case 2: inst.instruction |= 1 << 5; break;
        default: first_error (_("bad list length")); return;
        }
      inst.instruction |= neon_logbits (et.size) << 6;
      break;

    case 1:  /* VLD2.  */
      align_good = neon_alignment_bit (et.size, inst.operands[1].imm >> 8,
                                       &do_align, 8, 16, 16, 32, 32, 64, -1);
      if (align_good == FAIL)
        return;
      constraint (NEON_REGLIST_LENGTH (inst.operands[0].imm) != 2,
                  _("bad list length"));
      if (NEON_REG_STRIDE (inst.operands[0].imm) == 2)
        inst.instruction |= 1 << 5;
      inst.instruction |= neon_logbits (et.size) << 6;
      break;

    case 2:  /* VLD3.  */
      constraint (inst.operands[1].immisalign,
                  _("can't use alignment with this instruction"));
      constraint (NEON_REGLIST_LENGTH (inst.operands[0].imm) != 3,
                  _("bad list length"));
      if (NEON_REG_STRIDE (inst.operands[0].imm) == 2)
        inst.instruction |= 1 << 5;
      inst.instruction |= neon_logbits (et.size) << 6;
      break;

    case 3:  /* VLD4.  */
      {
        int align = inst.operands[1].imm >> 8;
        align_good = neon_alignment_bit (et.size, align, &do_align, 8, 32,
                                         16, 64, 32, 64, 32, 128, -1);
        if (align_good == FAIL)
          return;
        constraint (NEON_REGLIST_LENGTH (inst.operands[0].imm) != 4,
                    _("bad list length"));
        if (NEON_REG_STRIDE (inst.operands[0].imm) == 2)
          inst.instruction |= 1 << 5;
        if (et.size == 32 && align == 128)
          inst.instruction |= 0x3 << 6;
        else
          inst.instruction |= neon_logbits (et.size) << 6;
      }
      break;

    default: ;
    }

  inst.instruction |= do_align << 4;
}