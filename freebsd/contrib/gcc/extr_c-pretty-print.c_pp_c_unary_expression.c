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
typedef  int /*<<< orphan*/  c_pretty_printer ;

/* Variables and functions */
#define  ADDR_EXPR 137 
#define  BIT_NOT_EXPR 136 
#define  CONJ_EXPR 135 
#define  IMAGPART_EXPR 134 
#define  INDIRECT_REF 133 
#define  NEGATE_EXPR 132 
#define  PREDECREMENT_EXPR 131 
#define  PREINCREMENT_EXPR 130 
#define  REALPART_EXPR 129 
 int STRING_CST ; 
 int TREE_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_OPERAND (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
#define  TRUTH_NOT_EXPR 128 
 int /*<<< orphan*/  pp_ampersand (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pp_c_cast_expression (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pp_c_identifier (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  pp_c_star (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pp_c_whitespace (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pp_complement (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pp_exclamation (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pp_identifier (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  pp_minus (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pp_postfix_expression (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pp_unary_expression (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void
pp_c_unary_expression (c_pretty_printer *pp, tree e)
{
  enum tree_code code = TREE_CODE (e);
  switch (code)
    {
    case PREINCREMENT_EXPR:
    case PREDECREMENT_EXPR:
      pp_identifier (pp, code == PREINCREMENT_EXPR ? "++" : "--");
      pp_c_unary_expression (pp, TREE_OPERAND (e, 0));
      break;

    case ADDR_EXPR:
    case INDIRECT_REF:
    case NEGATE_EXPR:
    case BIT_NOT_EXPR:
    case TRUTH_NOT_EXPR:
    case CONJ_EXPR:
      /* String literal are used by address.  */
      if (code == ADDR_EXPR && TREE_CODE (TREE_OPERAND (e, 0)) != STRING_CST)
	pp_ampersand (pp);
      else if (code == INDIRECT_REF)
	pp_c_star (pp);
      else if (code == NEGATE_EXPR)
	pp_minus (pp);
      else if (code == BIT_NOT_EXPR || code == CONJ_EXPR)
	pp_complement (pp);
      else if (code == TRUTH_NOT_EXPR)
	pp_exclamation (pp);
      pp_c_cast_expression (pp, TREE_OPERAND (e, 0));
      break;

    case REALPART_EXPR:
    case IMAGPART_EXPR:
      pp_c_identifier (pp, code == REALPART_EXPR ? "__real__" : "__imag__");
      pp_c_whitespace (pp);
      pp_unary_expression (pp, TREE_OPERAND (e, 0));
      break;

    default:
      pp_postfix_expression (pp, e);
      break;
    }
}