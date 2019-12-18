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
typedef  scalar_t__ tree ;

/* Variables and functions */
 scalar_t__ INTEGER_CST ; 
 scalar_t__ NULL_TREE ; 
 int /*<<< orphan*/  STRIP_TYPE_NOPS (scalar_t__) ; 
 scalar_t__ TREE_CODE (scalar_t__) ; 
 scalar_t__ c_dialect_cxx () ; 
 int /*<<< orphan*/  constant_expression_warning (scalar_t__) ; 
 scalar_t__ decl_constant_value (scalar_t__) ; 
 int /*<<< orphan*/  error (char*) ; 
 scalar_t__ error_mark_node ; 
 scalar_t__ fold (scalar_t__) ; 
 scalar_t__ perform_integral_promotions (scalar_t__) ; 

__attribute__((used)) static tree
check_case_value (tree value)
{
  if (value == NULL_TREE)
    return value;

  /* ??? Can we ever get nops here for a valid case value?  We
     shouldn't for C.  */
  STRIP_TYPE_NOPS (value);
  /* In C++, the following is allowed:

       const int i = 3;
       switch (...) { case i: ... }

     So, we try to reduce the VALUE to a constant that way.  */
  if (c_dialect_cxx ())
    {
      value = decl_constant_value (value);
      STRIP_TYPE_NOPS (value);
      value = fold (value);
    }

  if (TREE_CODE (value) == INTEGER_CST)
    /* Promote char or short to int.  */
    value = perform_integral_promotions (value);
  else if (value != error_mark_node)
    {
      error ("case label does not reduce to an integer constant");
      value = error_mark_node;
    }

  constant_expression_warning (value);

  return value;
}