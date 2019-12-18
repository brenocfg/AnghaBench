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
typedef  enum tree_code { ____Placeholder_tree_code } tree_code ;
typedef  int /*<<< orphan*/  double_int ;

/* Variables and functions */
 int /*<<< orphan*/  FLOOR_DIV_EXPR ; 
#define  INTEGER_CST 131 
#define  MINUS_EXPR 130 
#define  MULT_EXPR 129 
#define  PLUS_EXPR 128 
 int /*<<< orphan*/  STRIP_NOPS (int /*<<< orphan*/ ) ; 
 int const TREE_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_OPERAND (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  TREE_TYPE (int /*<<< orphan*/ ) ; 
 unsigned int TYPE_PRECISION (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  double_int_add (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  double_int_mul (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  double_int_neg (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  double_int_one ; 
 int /*<<< orphan*/  double_int_sdivmod (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  double_int_sext (int /*<<< orphan*/ ,unsigned int) ; 
 int double_int_zero_p (int /*<<< orphan*/ ) ; 
 scalar_t__ operand_equal_p (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tree_to_double_int (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
constant_multiple_of (tree top, tree bot, double_int *mul)
{
  tree mby;
  enum tree_code code;
  double_int res, p0, p1;
  unsigned precision = TYPE_PRECISION (TREE_TYPE (top));

  STRIP_NOPS (top);
  STRIP_NOPS (bot);

  if (operand_equal_p (top, bot, 0))
    {
      *mul = double_int_one;
      return true;
    }

  code = TREE_CODE (top);
  switch (code)
    {
    case MULT_EXPR:
      mby = TREE_OPERAND (top, 1);
      if (TREE_CODE (mby) != INTEGER_CST)
	return false;

      if (!constant_multiple_of (TREE_OPERAND (top, 0), bot, &res))
	return false;

      *mul = double_int_sext (double_int_mul (res, tree_to_double_int (mby)),
			      precision);
      return true;

    case PLUS_EXPR:
    case MINUS_EXPR:
      if (!constant_multiple_of (TREE_OPERAND (top, 0), bot, &p0)
	  || !constant_multiple_of (TREE_OPERAND (top, 1), bot, &p1))
	return false;

      if (code == MINUS_EXPR)
	p1 = double_int_neg (p1);
      *mul = double_int_sext (double_int_add (p0, p1), precision);
      return true;

    case INTEGER_CST:
      if (TREE_CODE (bot) != INTEGER_CST)
	return false;

      p0 = double_int_sext (tree_to_double_int (bot), precision);
      p1 = double_int_sext (tree_to_double_int (top), precision);
      if (double_int_zero_p (p1))
	return false;
      *mul = double_int_sext (double_int_sdivmod (p0, p1, FLOOR_DIV_EXPR, &res),
			      precision);
      return double_int_zero_p (res);

    default:
      return false;
    }
}