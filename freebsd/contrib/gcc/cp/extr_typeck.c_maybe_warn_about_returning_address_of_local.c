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

/* Variables and functions */
 scalar_t__ ADDR_EXPR ; 
 scalar_t__ AGGR_INIT_EXPR ; 
 scalar_t__ ARRAY_REF ; 
 scalar_t__ BLOCK_POINTER_TYPE ; 
 scalar_t__ COMPONENT_REF ; 
 scalar_t__ COMPOUND_EXPR ; 
 scalar_t__ CONVERT_EXPR ; 
 scalar_t__ DECL_FUNCTION_SCOPE_P (int /*<<< orphan*/ ) ; 
 scalar_t__ DECL_NAME (int /*<<< orphan*/ ) ; 
 scalar_t__ DECL_P (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DECL_RESULT (int /*<<< orphan*/ ) ; 
 scalar_t__ NON_LVALUE_EXPR ; 
 scalar_t__ NOP_EXPR ; 
 scalar_t__ REFERENCE_TYPE ; 
 scalar_t__ TARGET_EXPR ; 
 scalar_t__ TEMP_NAME_P (scalar_t__) ; 
 scalar_t__ TREE_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_OPERAND (int /*<<< orphan*/ ,int) ; 
 scalar_t__ TREE_PUBLIC (int /*<<< orphan*/ ) ; 
 scalar_t__ TREE_STATIC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_TYPE (int /*<<< orphan*/ ) ; 
 scalar_t__ VAR_DECL ; 
 int /*<<< orphan*/  current_function_decl ; 
 int /*<<< orphan*/  error (char*) ; 
 int /*<<< orphan*/  warning (int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static void
maybe_warn_about_returning_address_of_local (tree retval)
{
  tree valtype = TREE_TYPE (DECL_RESULT (current_function_decl));
  tree whats_returned = retval;

  for (;;)
    {
      if (TREE_CODE (whats_returned) == COMPOUND_EXPR)
	whats_returned = TREE_OPERAND (whats_returned, 1);
      else if (TREE_CODE (whats_returned) == CONVERT_EXPR
	       || TREE_CODE (whats_returned) == NON_LVALUE_EXPR
	       || TREE_CODE (whats_returned) == NOP_EXPR)
	whats_returned = TREE_OPERAND (whats_returned, 0);
      else
	break;
    }

  if (TREE_CODE (whats_returned) != ADDR_EXPR)
    return;
  whats_returned = TREE_OPERAND (whats_returned, 0);

  if (TREE_CODE (valtype) == REFERENCE_TYPE)
    {
      if (TREE_CODE (whats_returned) == AGGR_INIT_EXPR
	  || TREE_CODE (whats_returned) == TARGET_EXPR)
	{
	  warning (0, "returning reference to temporary");
	  return;
	}
      if (TREE_CODE (whats_returned) == VAR_DECL
	  && DECL_NAME (whats_returned)
	  && TEMP_NAME_P (DECL_NAME (whats_returned)))
	{
	  warning (0, "reference to non-lvalue returned");
	  return;
	}
    }

  while (TREE_CODE (whats_returned) == COMPONENT_REF
	 || TREE_CODE (whats_returned) == ARRAY_REF)
    whats_returned = TREE_OPERAND (whats_returned, 0);

  if (DECL_P (whats_returned)
      && DECL_NAME (whats_returned)
      && DECL_FUNCTION_SCOPE_P (whats_returned)
      && !(TREE_STATIC (whats_returned)
	   || TREE_PUBLIC (whats_returned)))
    {
      if (TREE_CODE (valtype) == REFERENCE_TYPE)
	warning (0, "reference to local variable %q+D returned",
		 whats_returned);
      /* APPLE LOCAL begin blocks 6040305 (cn) */
      else if (TREE_CODE (valtype) == BLOCK_POINTER_TYPE)
	error ("returning block that lives on the local stack");
      /* APPLE LOCAL end blocks 6040305 (cn) */
      else
	warning (0, "address of local variable %q+D returned",
		 whats_returned);
      return;
    }
}