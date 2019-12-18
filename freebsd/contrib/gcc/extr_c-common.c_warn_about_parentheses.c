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
typedef  enum tree_code { ____Placeholder_tree_code } tree_code ;

/* Variables and functions */
 int BIT_AND_EXPR ; 
 int BIT_IOR_EXPR ; 
 int BIT_XOR_EXPR ; 
 int LSHIFT_EXPR ; 
 int MINUS_EXPR ; 
 int /*<<< orphan*/  OPT_Wparentheses ; 
 int PLUS_EXPR ; 
 int RSHIFT_EXPR ; 
 scalar_t__ TREE_CODE_CLASS (int) ; 
 int TRUTH_ANDIF_EXPR ; 
 int TRUTH_ORIF_EXPR ; 
 scalar_t__ tcc_comparison ; 
 int /*<<< orphan*/  warn_parentheses ; 
 int /*<<< orphan*/  warning (int /*<<< orphan*/ ,char*) ; 

void
warn_about_parentheses (enum tree_code code, enum tree_code code_left,
			enum tree_code code_right)
{
  if (!warn_parentheses)
    return;

  if (code == LSHIFT_EXPR || code == RSHIFT_EXPR)
    {
      if (code_left == PLUS_EXPR || code_left == MINUS_EXPR
	  || code_right == PLUS_EXPR || code_right == MINUS_EXPR)
	warning (OPT_Wparentheses,
		 "suggest parentheses around + or - inside shift");
    }

  if (code == TRUTH_ORIF_EXPR)
    {
      if (code_left == TRUTH_ANDIF_EXPR
	  || code_right == TRUTH_ANDIF_EXPR)
	warning (OPT_Wparentheses,
		 "suggest parentheses around && within ||");
    }

  if (code == BIT_IOR_EXPR)
    {
      if (code_left == BIT_AND_EXPR || code_left == BIT_XOR_EXPR
	  || code_left == PLUS_EXPR || code_left == MINUS_EXPR
	  || code_right == BIT_AND_EXPR || code_right == BIT_XOR_EXPR
	  || code_right == PLUS_EXPR || code_right == MINUS_EXPR)
	warning (OPT_Wparentheses,
		 "suggest parentheses around arithmetic in operand of |");
      /* Check cases like x|y==z */
      if (TREE_CODE_CLASS (code_left) == tcc_comparison
	  || TREE_CODE_CLASS (code_right) == tcc_comparison)
	warning (OPT_Wparentheses,
		 "suggest parentheses around comparison in operand of |");
    }

  if (code == BIT_XOR_EXPR)
    {
      if (code_left == BIT_AND_EXPR
	  || code_left == PLUS_EXPR || code_left == MINUS_EXPR
	  || code_right == BIT_AND_EXPR
	  || code_right == PLUS_EXPR || code_right == MINUS_EXPR)
	warning (OPT_Wparentheses,
		 "suggest parentheses around arithmetic in operand of ^");
      /* Check cases like x^y==z */
      if (TREE_CODE_CLASS (code_left) == tcc_comparison
	  || TREE_CODE_CLASS (code_right) == tcc_comparison)
	warning (OPT_Wparentheses,
		 "suggest parentheses around comparison in operand of ^");
    }

  if (code == BIT_AND_EXPR)
    {
      if (code_left == PLUS_EXPR || code_left == MINUS_EXPR
	  || code_right == PLUS_EXPR || code_right == MINUS_EXPR)
	warning (OPT_Wparentheses,
		 "suggest parentheses around + or - in operand of &");
      /* Check cases like x&y==z */
      if (TREE_CODE_CLASS (code_left) == tcc_comparison
	  || TREE_CODE_CLASS (code_right) == tcc_comparison)
	warning (OPT_Wparentheses,
		 "suggest parentheses around comparison in operand of &");
    }

  /* Similarly, check for cases like 1<=i<=10 that are probably errors.  */
  if (TREE_CODE_CLASS (code) == tcc_comparison
      && (TREE_CODE_CLASS (code_left) == tcc_comparison
	  || TREE_CODE_CLASS (code_right) == tcc_comparison))
    warning (OPT_Wparentheses, "comparisons like X<=Y<=Z do not "
	     "have their mathematical meaning");
}