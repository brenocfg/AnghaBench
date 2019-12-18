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
struct c_expr {scalar_t__ value; void* original_code; } ;

/* Variables and functions */
 int /*<<< orphan*/  COMPOUND_EXPR ; 
 int C_TYPE_VARIABLE_SIZE (int /*<<< orphan*/ ) ; 
 void* ERROR_MARK ; 
 int /*<<< orphan*/  TREE_TYPE (scalar_t__) ; 
 scalar_t__ build2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 scalar_t__ c_sizeof (int /*<<< orphan*/ ) ; 
 scalar_t__ c_vla_type_p (int /*<<< orphan*/ ) ; 
 scalar_t__ error_mark_node ; 
 int /*<<< orphan*/  pop_maybe_used (int) ; 

struct c_expr
c_expr_sizeof_expr (struct c_expr expr)
{
  struct c_expr ret;
  if (expr.value == error_mark_node)
    {
      ret.value = error_mark_node;
      ret.original_code = ERROR_MARK;
      pop_maybe_used (false);
    }
  else
    {
      ret.value = c_sizeof (TREE_TYPE (expr.value));
      ret.original_code = ERROR_MARK;
      if (c_vla_type_p (TREE_TYPE (expr.value)))
	{
	  /* sizeof is evaluated when given a vla (C99 6.5.3.4p2).  */
	  ret.value = build2 (COMPOUND_EXPR, TREE_TYPE (ret.value), expr.value, ret.value);
	}
      pop_maybe_used (C_TYPE_VARIABLE_SIZE (TREE_TYPE (expr.value)));
    }
  return ret;
}