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
typedef  int /*<<< orphan*/  location_t ;

/* Variables and functions */
#define  BIND_EXPR 146 
 int /*<<< orphan*/  BIND_EXPR_BODY (int /*<<< orphan*/ ) ; 
#define  CALL_EXPR 145 
#define  COMPOUND_EXPR 144 
#define  COND_EXPR 143 
 int /*<<< orphan*/  DECL_P (int /*<<< orphan*/ ) ; 
#define  EXIT_EXPR 142 
 int /*<<< orphan*/  EXPRESSION_CLASS_P (int /*<<< orphan*/ ) ; 
 scalar_t__ EXPR_HAS_LOCATION (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EXPR_LOCATION (int /*<<< orphan*/ ) ; 
#define  INDIRECT_REF 141 
#define  INIT_EXPR 140 
#define  MODIFY_EXPR 139 
#define  POSTDECREMENT_EXPR 138 
#define  POSTINCREMENT_EXPR 137 
#define  PREDECREMENT_EXPR 136 
#define  PREINCREMENT_EXPR 135 
 int /*<<< orphan*/  REFERENCE_CLASS_P (int /*<<< orphan*/ ) ; 
 int REFERENCE_TYPE ; 
#define  SAVE_EXPR 134 
#define  TARGET_EXPR 133 
 int TREE_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_CODE_LENGTH (int) ; 
 int /*<<< orphan*/  TREE_CONSTANT (int /*<<< orphan*/ ) ; 
 scalar_t__ TREE_NO_WARNING (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_OPERAND (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  TREE_SIDE_EFFECTS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_THIS_VOLATILE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_TYPE (int /*<<< orphan*/ ) ; 
 scalar_t__ TREE_USED (int /*<<< orphan*/ ) ; 
#define  TRUTH_ANDIF_EXPR 132 
#define  TRUTH_ORIF_EXPR 131 
#define  TRY_CATCH_EXPR 130 
#define  VA_ARG_EXPR 129 
 scalar_t__ VOID_TYPE_P (int /*<<< orphan*/ ) ; 
#define  WITH_CLEANUP_EXPR 128 
 int /*<<< orphan*/  warning (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 

int
warn_if_unused_value (tree exp, location_t locus)
{
 restart:
  if (TREE_USED (exp) || TREE_NO_WARNING (exp))
    return 0;

  /* Don't warn about void constructs.  This includes casting to void,
     void function calls, and statement expressions with a final cast
     to void.  */
  if (VOID_TYPE_P (TREE_TYPE (exp)))
    return 0;

  if (EXPR_HAS_LOCATION (exp))
    locus = EXPR_LOCATION (exp);

  switch (TREE_CODE (exp))
    {
    case PREINCREMENT_EXPR:
    case POSTINCREMENT_EXPR:
    case PREDECREMENT_EXPR:
    case POSTDECREMENT_EXPR:
    case MODIFY_EXPR:
    case INIT_EXPR:
    case TARGET_EXPR:
    case CALL_EXPR:
    case TRY_CATCH_EXPR:
    case WITH_CLEANUP_EXPR:
    case EXIT_EXPR:
    case VA_ARG_EXPR:
      return 0;

    case BIND_EXPR:
      /* For a binding, warn if no side effect within it.  */
      exp = BIND_EXPR_BODY (exp);
      goto restart;

    case SAVE_EXPR:
      exp = TREE_OPERAND (exp, 0);
      goto restart;

    case TRUTH_ORIF_EXPR:
    case TRUTH_ANDIF_EXPR:
      /* In && or ||, warn if 2nd operand has no side effect.  */
      exp = TREE_OPERAND (exp, 1);
      goto restart;

    case COMPOUND_EXPR:
      if (warn_if_unused_value (TREE_OPERAND (exp, 0), locus))
	return 1;
      /* Let people do `(foo (), 0)' without a warning.  */
      if (TREE_CONSTANT (TREE_OPERAND (exp, 1)))
	return 0;
      exp = TREE_OPERAND (exp, 1);
      goto restart;

    case COND_EXPR:
      /* If this is an expression with side effects, don't warn; this
	 case commonly appears in macro expansions.  */
      if (TREE_SIDE_EFFECTS (exp))
	return 0;
      goto warn;

    case INDIRECT_REF:
      /* Don't warn about automatic dereferencing of references, since
	 the user cannot control it.  */
      if (TREE_CODE (TREE_TYPE (TREE_OPERAND (exp, 0))) == REFERENCE_TYPE)
	{
	  exp = TREE_OPERAND (exp, 0);
	  goto restart;
	}
      /* Fall through.  */

    default:
      /* Referencing a volatile value is a side effect, so don't warn.  */
      if ((DECL_P (exp) || REFERENCE_CLASS_P (exp))
	  && TREE_THIS_VOLATILE (exp))
	return 0;

      /* If this is an expression which has no operands, there is no value
	 to be unused.  There are no such language-independent codes,
	 but front ends may define such.  */
      if (EXPRESSION_CLASS_P (exp) && TREE_CODE_LENGTH (TREE_CODE (exp)) == 0)
	return 0;

    warn:
      warning (0, "%Hvalue computed is not used", &locus);
      return 1;
    }
}