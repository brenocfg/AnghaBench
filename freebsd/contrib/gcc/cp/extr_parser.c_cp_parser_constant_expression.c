#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tree ;
struct TYPE_4__ {int integral_constant_expression_p; int allow_non_integral_constant_expression_p; int non_integral_constant_expression_p; } ;
typedef  TYPE_1__ cp_parser ;

/* Variables and functions */
 int /*<<< orphan*/  cp_parser_assignment_expression (TYPE_1__*,int) ; 
 int /*<<< orphan*/  error_mark_node ; 

__attribute__((used)) static tree
cp_parser_constant_expression (cp_parser* parser,
			       bool allow_non_constant_p,
			       bool *non_constant_p)
{
  bool saved_integral_constant_expression_p;
  bool saved_allow_non_integral_constant_expression_p;
  bool saved_non_integral_constant_expression_p;
  tree expression;

  /* It might seem that we could simply parse the
     conditional-expression, and then check to see if it were
     TREE_CONSTANT.  However, an expression that is TREE_CONSTANT is
     one that the compiler can figure out is constant, possibly after
     doing some simplifications or optimizations.  The standard has a
     precise definition of constant-expression, and we must honor
     that, even though it is somewhat more restrictive.

     For example:

       int i[(2, 3)];

     is not a legal declaration, because `(2, 3)' is not a
     constant-expression.  The `,' operator is forbidden in a
     constant-expression.  However, GCC's constant-folding machinery
     will fold this operation to an INTEGER_CST for `3'.  */

  /* Save the old settings.  */
  saved_integral_constant_expression_p = parser->integral_constant_expression_p;
  saved_allow_non_integral_constant_expression_p
    = parser->allow_non_integral_constant_expression_p;
  saved_non_integral_constant_expression_p = parser->non_integral_constant_expression_p;
  /* We are now parsing a constant-expression.  */
  parser->integral_constant_expression_p = true;
  parser->allow_non_integral_constant_expression_p = allow_non_constant_p;
  parser->non_integral_constant_expression_p = false;
  /* Although the grammar says "conditional-expression", we parse an
     "assignment-expression", which also permits "throw-expression"
     and the use of assignment operators.  In the case that
     ALLOW_NON_CONSTANT_P is false, we get better errors than we would
     otherwise.  In the case that ALLOW_NON_CONSTANT_P is true, it is
     actually essential that we look for an assignment-expression.
     For example, cp_parser_initializer_clauses uses this function to
     determine whether a particular assignment-expression is in fact
     constant.  */
  expression = cp_parser_assignment_expression (parser, /*cast_p=*/false);
  /* Restore the old settings.  */
  parser->integral_constant_expression_p
    = saved_integral_constant_expression_p;
  parser->allow_non_integral_constant_expression_p
    = saved_allow_non_integral_constant_expression_p;
  if (allow_non_constant_p)
    *non_constant_p = parser->non_integral_constant_expression_p;
  else if (parser->non_integral_constant_expression_p)
    expression = error_mark_node;
  parser->non_integral_constant_expression_p
    = saved_non_integral_constant_expression_p;

  return expression;
}