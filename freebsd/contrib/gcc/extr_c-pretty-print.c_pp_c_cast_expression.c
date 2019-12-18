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
typedef  int /*<<< orphan*/  c_pretty_printer ;

/* Variables and functions */
#define  CONVERT_EXPR 131 
#define  FIX_TRUNC_EXPR 130 
#define  FLOAT_EXPR 129 
#define  NOP_EXPR 128 
 int TREE_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_OPERAND (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_TYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pp_c_type_cast (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pp_unary_expression (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void
pp_c_cast_expression (c_pretty_printer *pp, tree e)
{
  switch (TREE_CODE (e))
    {
    case FLOAT_EXPR:
    case FIX_TRUNC_EXPR:
    case CONVERT_EXPR:
    case NOP_EXPR:
      pp_c_type_cast (pp, TREE_TYPE (e));
      pp_c_cast_expression (pp, TREE_OPERAND (e, 0));
      break;

    default:
      pp_unary_expression (pp, e);
    }
}