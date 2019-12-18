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
struct c_expr {int original_code; int /*<<< orphan*/  value; } ;
typedef  enum tree_code { ____Placeholder_tree_code } tree_code ;

/* Variables and functions */
 int EQ_EXPR ; 
 scalar_t__ ERROR_MARK ; 
 int NE_EXPR ; 
 int /*<<< orphan*/  OPT_Waddress ; 
 int STRING_CST ; 
 scalar_t__ TREE_CODE (int /*<<< orphan*/ ) ; 
 scalar_t__ TREE_CODE_CLASS (int) ; 
 scalar_t__ TREE_OVERFLOW_P (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  build_binary_op (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  integer_zerop (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  overflow_warning (int /*<<< orphan*/ ) ; 
 scalar_t__ tcc_comparison ; 
 int /*<<< orphan*/  warn_about_parentheses (int,int,int) ; 
 scalar_t__ warn_parentheses ; 
 int /*<<< orphan*/  warning (int /*<<< orphan*/ ,char*) ; 

struct c_expr
parser_build_binary_op (enum tree_code code, struct c_expr arg1,
			struct c_expr arg2)
{
  struct c_expr result;

  enum tree_code code1 = arg1.original_code;
  enum tree_code code2 = arg2.original_code;

  result.value = build_binary_op (code, arg1.value, arg2.value, 1);
  result.original_code = code;

  if (TREE_CODE (result.value) == ERROR_MARK)
    return result;

  /* Check for cases such as x+y<<z which users are likely
     to misinterpret.  */
  if (warn_parentheses)
    warn_about_parentheses (code, code1, code2);

  /* Warn about comparisons against string literals, with the exception
     of testing for equality or inequality of a string literal with NULL.  */
  if (code == EQ_EXPR || code == NE_EXPR)
    {
      if ((code1 == STRING_CST && !integer_zerop (arg2.value))
	  || (code2 == STRING_CST && !integer_zerop (arg1.value)))
	warning (OPT_Waddress, 
                 "comparison with string literal results in unspecified behaviour");
    }
  else if (TREE_CODE_CLASS (code) == tcc_comparison
	   && (code1 == STRING_CST || code2 == STRING_CST))
    warning (OPT_Waddress, 
             "comparison with string literal results in unspecified behaviour");

  if (TREE_OVERFLOW_P (result.value) 
      && !TREE_OVERFLOW_P (arg1.value) 
      && !TREE_OVERFLOW_P (arg2.value))
    overflow_warning (result.value);

  return result;
}