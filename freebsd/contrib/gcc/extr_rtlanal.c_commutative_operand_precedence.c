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
typedef  int /*<<< orphan*/  rtx ;
typedef  enum rtx_code { ____Placeholder_rtx_code } rtx_code ;

/* Variables and functions */
 int /*<<< orphan*/  CONSTANT_P (int /*<<< orphan*/ ) ; 
 int CONST_DOUBLE ; 
 int CONST_INT ; 
 int GET_CODE (int /*<<< orphan*/ ) ; 
 int GET_RTX_CLASS (int) ; 
 int NEG ; 
 int NOT ; 
 int /*<<< orphan*/  OBJECT_P (int /*<<< orphan*/ ) ; 
#define  RTX_BIN_ARITH 133 
#define  RTX_COMM_ARITH 132 
#define  RTX_CONST_OBJ 131 
#define  RTX_EXTRA 130 
#define  RTX_OBJ 129 
#define  RTX_UNARY 128 
 int SUBREG ; 
 int /*<<< orphan*/  SUBREG_REG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  avoid_constant_pool_reference (int /*<<< orphan*/ ) ; 

int
commutative_operand_precedence (rtx op)
{
  enum rtx_code code = GET_CODE (op);
  
  /* Constants always come the second operand.  Prefer "nice" constants.  */
  if (code == CONST_INT)
    return -7;
  if (code == CONST_DOUBLE)
    return -6;
  op = avoid_constant_pool_reference (op);
  code = GET_CODE (op);

  switch (GET_RTX_CLASS (code))
    {
    case RTX_CONST_OBJ:
      if (code == CONST_INT)
        return -5;
      if (code == CONST_DOUBLE)
        return -4;
      return -3;

    case RTX_EXTRA:
      /* SUBREGs of objects should come second.  */
      if (code == SUBREG && OBJECT_P (SUBREG_REG (op)))
        return -2;

      if (!CONSTANT_P (op))
        return 0;
      else
	/* As for RTX_CONST_OBJ.  */
	return -3;

    case RTX_OBJ:
      /* Complex expressions should be the first, so decrease priority
         of objects.  */
      return -1;

    case RTX_COMM_ARITH:
      /* Prefer operands that are themselves commutative to be first.
         This helps to make things linear.  In particular,
         (and (and (reg) (reg)) (not (reg))) is canonical.  */
      return 4;

    case RTX_BIN_ARITH:
      /* If only one operand is a binary expression, it will be the first
         operand.  In particular,  (plus (minus (reg) (reg)) (neg (reg)))
         is canonical, although it will usually be further simplified.  */
      return 2;
  
    case RTX_UNARY:
      /* Then prefer NEG and NOT.  */
      if (code == NEG || code == NOT)
        return 1;

    default:
      return 0;
    }
}