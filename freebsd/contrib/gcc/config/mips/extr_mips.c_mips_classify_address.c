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
struct mips_address_info {size_t symbol_type; void* type; void* reg; void* offset; } ;
typedef  void* rtx ;
typedef  enum machine_mode { ____Placeholder_machine_mode } machine_mode ;

/* Variables and functions */
 void* ADDRESS_CONST_INT ; 
 void* ADDRESS_LO_SUM ; 
 void* ADDRESS_REG ; 
 void* ADDRESS_SYMBOLIC ; 
#define  CONST 135 
#define  CONST_INT 134 
 int GET_CODE (void*) ; 
#define  LABEL_REF 133 
#define  LO_SUM 132 
#define  PLUS 131 
#define  REG 130 
 int /*<<< orphan*/  SMALL_INT (void*) ; 
#define  SUBREG 129 
#define  SYMBOL_REF 128 
 int /*<<< orphan*/  TARGET_MIPS16 ; 
 int /*<<< orphan*/  VOIDmode ; 
 void* XEXP (void*,int) ; 
 void* const0_rtx ; 
 int /*<<< orphan*/  const_arith_operand (void*,int /*<<< orphan*/ ) ; 
 size_t mips_classify_symbolic_expression (void*) ; 
 int /*<<< orphan*/ * mips_lo_relocs ; 
 int /*<<< orphan*/ * mips_split_p ; 
 int /*<<< orphan*/  mips_symbolic_address_p (size_t,int) ; 
 int /*<<< orphan*/  mips_symbolic_constant_p (void*,size_t*) ; 
 int mips_valid_base_register_p (void*,int,int) ; 

__attribute__((used)) static bool
mips_classify_address (struct mips_address_info *info, rtx x,
		       enum machine_mode mode, int strict)
{
  switch (GET_CODE (x))
    {
    case REG:
    case SUBREG:
      info->type = ADDRESS_REG;
      info->reg = x;
      info->offset = const0_rtx;
      return mips_valid_base_register_p (info->reg, mode, strict);

    case PLUS:
      info->type = ADDRESS_REG;
      info->reg = XEXP (x, 0);
      info->offset = XEXP (x, 1);
      return (mips_valid_base_register_p (info->reg, mode, strict)
	      && const_arith_operand (info->offset, VOIDmode));

    case LO_SUM:
      info->type = ADDRESS_LO_SUM;
      info->reg = XEXP (x, 0);
      info->offset = XEXP (x, 1);
      /* We have to trust the creator of the LO_SUM to do something vaguely
	 sane.  Target-independent code that creates a LO_SUM should also
	 create and verify the matching HIGH.  Target-independent code that
	 adds an offset to a LO_SUM must prove that the offset will not
	 induce a carry.  Failure to do either of these things would be
	 a bug, and we are not required to check for it here.  The MIPS
	 backend itself should only create LO_SUMs for valid symbolic
	 constants, with the high part being either a HIGH or a copy
	 of _gp. */
      info->symbol_type = mips_classify_symbolic_expression (info->offset);
      return (mips_valid_base_register_p (info->reg, mode, strict)
	      && mips_symbolic_address_p (info->symbol_type, mode)
	      && mips_lo_relocs[info->symbol_type] != 0);

    case CONST_INT:
      /* Small-integer addresses don't occur very often, but they
	 are legitimate if $0 is a valid base register.  */
      info->type = ADDRESS_CONST_INT;
      return !TARGET_MIPS16 && SMALL_INT (x);

    case CONST:
    case LABEL_REF:
    case SYMBOL_REF:
      info->type = ADDRESS_SYMBOLIC;
      return (mips_symbolic_constant_p (x, &info->symbol_type)
	      && mips_symbolic_address_p (info->symbol_type, mode)
	      && !mips_split_p[info->symbol_type]);

    default:
      return false;
    }
}