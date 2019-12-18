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
typedef  enum neon_shape { ____Placeholder_neon_shape } neon_shape ;
struct TYPE_4__ {int instruction; TYPE_1__* operands; } ;
struct TYPE_3__ {unsigned int imm; unsigned int reg; int immisfloat; scalar_t__ regisimm; } ;

/* Variables and functions */
 int FAIL ; 
 int HI1 (unsigned int) ; 
 int LOW4 (unsigned int) ; 
 int /*<<< orphan*/  NS_DI ; 
 int /*<<< orphan*/  NS_NULL ; 
 int /*<<< orphan*/  NS_QI ; 
 scalar_t__ NT_invtype ; 
 int /*<<< orphan*/  N_EQK ; 
 int N_F32 ; 
 int N_I16 ; 
 int N_I32 ; 
 int N_I64 ; 
 int N_I8 ; 
 int N_KEY ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  constraint (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  first_error (int /*<<< orphan*/ ) ; 
 TYPE_2__ inst ; 
 struct neon_type_el neon_check_type (int,int,int,int /*<<< orphan*/ ) ; 
 int neon_cmode_for_move_imm (unsigned int,unsigned int,int,unsigned int*,int*,int,scalar_t__) ; 
 int /*<<< orphan*/  neon_invert_size (unsigned int*,unsigned int*,int) ; 
 int neon_quad (int) ; 
 int neon_select_shape (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  neon_write_immbits (unsigned int) ; 

__attribute__((used)) static void
neon_move_immediate (void)
{
  enum neon_shape rs = neon_select_shape (NS_DI, NS_QI, NS_NULL);
  struct neon_type_el et = neon_check_type (2, rs,
    N_I8 | N_I16 | N_I32 | N_I64 | N_F32 | N_KEY, N_EQK);
  unsigned immlo, immhi = 0, immbits;
  int op, cmode, float_p;

  constraint (et.type == NT_invtype,
              _("operand size must be specified for immediate VMOV"));

  /* We start out as an MVN instruction if OP = 1, MOV otherwise.  */
  op = (inst.instruction & (1 << 5)) != 0;

  immlo = inst.operands[1].imm;
  if (inst.operands[1].regisimm)
    immhi = inst.operands[1].reg;

  constraint (et.size < 32 && (immlo & ~((1 << et.size) - 1)) != 0,
              _("immediate has bits set outside the operand size"));

  float_p = inst.operands[1].immisfloat;

  if ((cmode = neon_cmode_for_move_imm (immlo, immhi, float_p, &immbits, &op,
                                        et.size, et.type)) == FAIL)
    {
      /* Invert relevant bits only.  */
      neon_invert_size (&immlo, &immhi, et.size);
      /* Flip from VMOV/VMVN to VMVN/VMOV. Some immediate types are unavailable
         with one or the other; those cases are caught by
         neon_cmode_for_move_imm.  */
      op = !op;
      if ((cmode = neon_cmode_for_move_imm (immlo, immhi, float_p, &immbits,
					    &op, et.size, et.type)) == FAIL)
        {
          first_error (_("immediate out of range"));
          return;
        }
    }

  inst.instruction &= ~(1 << 5);
  inst.instruction |= op << 5;

  inst.instruction |= LOW4 (inst.operands[0].reg) << 12;
  inst.instruction |= HI1 (inst.operands[0].reg) << 22;
  inst.instruction |= neon_quad (rs) << 6;
  inst.instruction |= cmode << 8;

  neon_write_immbits (immbits);
}