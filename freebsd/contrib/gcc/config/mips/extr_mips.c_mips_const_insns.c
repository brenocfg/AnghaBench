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
struct mips_integer_op {int dummy; } ;
typedef  int /*<<< orphan*/  rtx ;
typedef  enum mips_symbol_type { ____Placeholder_mips_symbol_type } mips_symbol_type ;
typedef  int HOST_WIDE_INT ;

/* Variables and functions */
#define  CONST 134 
 int /*<<< orphan*/  CONST0_RTX (int /*<<< orphan*/ ) ; 
#define  CONST_DOUBLE 133 
 int /*<<< orphan*/  CONST_GP_P (int /*<<< orphan*/ ) ; 
#define  CONST_INT 132 
#define  CONST_VECTOR 131 
 int GET_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GET_MODE (int /*<<< orphan*/ ) ; 
#define  HIGH 130 
 int INTVAL (int /*<<< orphan*/ ) ; 
#define  LABEL_REF 129 
 int MIPS_MAX_INTEGER_OPS ; 
 int /*<<< orphan*/  SMALL_OPERAND (int) ; 
 int /*<<< orphan*/  SMALL_OPERAND_UNSIGNED (int) ; 
#define  SYMBOL_REF 128 
 int /*<<< orphan*/  TARGET_MIPS16 ; 
 int /*<<< orphan*/  XEXP (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int mips_build_integer (struct mips_integer_op*,int) ; 
 int mips_classify_symbol (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mips_split_const (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/ * mips_split_p ; 
 int mips_symbol_insns (int) ; 
 int /*<<< orphan*/  mips_symbolic_constant_p (int /*<<< orphan*/ ,int*) ; 

int
mips_const_insns (rtx x)
{
  struct mips_integer_op codes[MIPS_MAX_INTEGER_OPS];
  enum mips_symbol_type symbol_type;
  HOST_WIDE_INT offset;

  switch (GET_CODE (x))
    {
    case HIGH:
      if (TARGET_MIPS16
	  || !mips_symbolic_constant_p (XEXP (x, 0), &symbol_type)
	  || !mips_split_p[symbol_type])
	return 0;

      return 1;

    case CONST_INT:
      if (TARGET_MIPS16)
	/* Unsigned 8-bit constants can be loaded using an unextended
	   LI instruction.  Unsigned 16-bit constants can be loaded
	   using an extended LI.  Negative constants must be loaded
	   using LI and then negated.  */
	return (INTVAL (x) >= 0 && INTVAL (x) < 256 ? 1
		: SMALL_OPERAND_UNSIGNED (INTVAL (x)) ? 2
		: INTVAL (x) > -256 && INTVAL (x) < 0 ? 2
		: SMALL_OPERAND_UNSIGNED (-INTVAL (x)) ? 3
		: 0);

      return mips_build_integer (codes, INTVAL (x));

    case CONST_DOUBLE:
    case CONST_VECTOR:
      return (!TARGET_MIPS16 && x == CONST0_RTX (GET_MODE (x)) ? 1 : 0);

    case CONST:
      if (CONST_GP_P (x))
	return 1;

      /* See if we can refer to X directly.  */
      if (mips_symbolic_constant_p (x, &symbol_type))
	return mips_symbol_insns (symbol_type);

      /* Otherwise try splitting the constant into a base and offset.
	 16-bit offsets can be added using an extra addiu.  Larger offsets
	 must be calculated separately and then added to the base.  */
      mips_split_const (x, &x, &offset);
      if (offset != 0)
	{
	  int n = mips_const_insns (x);
	  if (n != 0)
	    {
	      if (SMALL_OPERAND (offset))
		return n + 1;
	      else
		return n + 1 + mips_build_integer (codes, offset);
	    }
	}
      return 0;

    case SYMBOL_REF:
    case LABEL_REF:
      return mips_symbol_insns (mips_classify_symbol (x));

    default:
      return 0;
    }
}