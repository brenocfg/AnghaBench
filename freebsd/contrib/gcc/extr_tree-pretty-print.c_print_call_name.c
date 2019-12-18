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
typedef  int /*<<< orphan*/  pretty_printer ;

/* Variables and functions */
#define  ADDR_EXPR 137 
#define  ARRAY_REF 136 
 int const CALL_EXPR ; 
#define  COMPONENT_REF 135 
#define  COND_EXPR 134 
#define  INDIRECT_REF 133 
 int /*<<< orphan*/  NIY ; 
 int const NON_LVALUE_EXPR ; 
#define  NOP_EXPR 132 
#define  OBJ_TYPE_REF 131 
#define  PARM_DECL 130 
#define  SSA_NAME 129 
 int const TREE_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_OPERAND (int /*<<< orphan*/ ,int) ; 
#define  VAR_DECL 128 
 int /*<<< orphan*/  dump_function_name (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dump_generic_node (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 int /*<<< orphan*/  pp_string (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static void
print_call_name (pretty_printer *buffer, tree node)
{
  tree op0;

  gcc_assert (TREE_CODE (node) == CALL_EXPR);

  op0 = TREE_OPERAND (node, 0);

  if (TREE_CODE (op0) == NON_LVALUE_EXPR)
    op0 = TREE_OPERAND (op0, 0);

  switch (TREE_CODE (op0))
    {
    case VAR_DECL:
    case PARM_DECL:
      dump_function_name (buffer, op0);
      break;

    case ADDR_EXPR:
    case INDIRECT_REF:
    case NOP_EXPR:
      dump_generic_node (buffer, TREE_OPERAND (op0, 0), 0, 0, false);
      break;

    case COND_EXPR:
      pp_string (buffer, "(");
      dump_generic_node (buffer, TREE_OPERAND (op0, 0), 0, 0, false);
      pp_string (buffer, ") ? ");
      dump_generic_node (buffer, TREE_OPERAND (op0, 1), 0, 0, false);
      pp_string (buffer, " : ");
      dump_generic_node (buffer, TREE_OPERAND (op0, 2), 0, 0, false);
      break;

    case COMPONENT_REF:
      /* The function is a pointer contained in a structure.  */
      if (TREE_CODE (TREE_OPERAND (op0, 0)) == INDIRECT_REF ||
	  TREE_CODE (TREE_OPERAND (op0, 0)) == VAR_DECL)
	dump_function_name (buffer, TREE_OPERAND (op0, 1));
      else
	dump_generic_node (buffer, TREE_OPERAND (op0, 0), 0, 0, false);
      /* else
	 We can have several levels of structures and a function
	 pointer inside.  This is not implemented yet...  */
      /*		  NIY;*/
      break;

    case ARRAY_REF:
      if (TREE_CODE (TREE_OPERAND (op0, 0)) == VAR_DECL)
	dump_function_name (buffer, TREE_OPERAND (op0, 0));
      else
	dump_generic_node (buffer, op0, 0, 0, false);
      break;

    case SSA_NAME:
    case OBJ_TYPE_REF:
      dump_generic_node (buffer, op0, 0, 0, false);
      break;

    default:
      NIY;
    }
}