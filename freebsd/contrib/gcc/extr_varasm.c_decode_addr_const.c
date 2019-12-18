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
typedef  int /*<<< orphan*/  tree ;
struct addr_const {int offset; int /*<<< orphan*/  base; } ;
typedef  int /*<<< orphan*/  rtx ;

/* Variables and functions */
 int ARRAY_RANGE_REF ; 
 int ARRAY_REF ; 
#define  COMPLEX_CST 135 
 int COMPONENT_REF ; 
#define  CONSTRUCTOR 134 
 int /*<<< orphan*/  DECL_RTL (int /*<<< orphan*/ ) ; 
#define  FUNCTION_DECL 133 
 int /*<<< orphan*/  FUNCTION_MODE ; 
#define  INTEGER_CST 132 
#define  LABEL_DECL 131 
 int /*<<< orphan*/  MEM_P (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Pmode ; 
#define  REAL_CST 130 
#define  STRING_CST 129 
 int TREE_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_OPERAND (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  TREE_TYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TYPE_SIZE_UNIT (int /*<<< orphan*/ ) ; 
#define  VAR_DECL 128 
 int /*<<< orphan*/  XEXP (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  byte_position (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  force_label_rtx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gcc_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gcc_unreachable () ; 
 int /*<<< orphan*/  gen_rtx_LABEL_REF (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_rtx_MEM (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ host_integerp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ int_byte_position (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  output_constant_def (int /*<<< orphan*/ ,int) ; 
 int tree_low_cst (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
decode_addr_const (tree exp, struct addr_const *value)
{
  tree target = TREE_OPERAND (exp, 0);
  int offset = 0;
  rtx x;

  while (1)
    {
      if (TREE_CODE (target) == COMPONENT_REF
	  && host_integerp (byte_position (TREE_OPERAND (target, 1)), 0))

	{
	  offset += int_byte_position (TREE_OPERAND (target, 1));
	  target = TREE_OPERAND (target, 0);
	}
      else if (TREE_CODE (target) == ARRAY_REF
	       || TREE_CODE (target) == ARRAY_RANGE_REF)
	{
	  offset += (tree_low_cst (TYPE_SIZE_UNIT (TREE_TYPE (target)), 1)
		     * tree_low_cst (TREE_OPERAND (target, 1), 0));
	  target = TREE_OPERAND (target, 0);
	}
      else
	break;
    }

  switch (TREE_CODE (target))
    {
    case VAR_DECL:
    case FUNCTION_DECL:
      x = DECL_RTL (target);
      break;

    case LABEL_DECL:
      x = gen_rtx_MEM (FUNCTION_MODE,
		       gen_rtx_LABEL_REF (Pmode, force_label_rtx (target)));
      break;

    case REAL_CST:
    case STRING_CST:
    case COMPLEX_CST:
    case CONSTRUCTOR:
    case INTEGER_CST:
      x = output_constant_def (target, 1);
      break;

    default:
      gcc_unreachable ();
    }

  gcc_assert (MEM_P (x));
  x = XEXP (x, 0);

  value->base = x;
  value->offset = offset;
}