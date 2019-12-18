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
typedef  int TREE_SIDE_EFFECTS ;

/* Variables and functions */
 scalar_t__ NOP_EXPR ; 
 scalar_t__ REFERENCE_TYPE ; 
 int /*<<< orphan*/  STATIC_CAST_EXPR ; 
 scalar_t__ TREE_CODE (scalar_t__) ; 
 scalar_t__ TREE_OPERAND (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ TREE_TYPE (scalar_t__) ; 
 scalar_t__ build_min (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 scalar_t__ build_static_cast_1 (scalar_t__,scalar_t__,int,int*) ; 
 scalar_t__ convert_from_reference (int) ; 
 int /*<<< orphan*/  error (char*,scalar_t__,scalar_t__) ; 
 scalar_t__ error_mark_node ; 
 scalar_t__ processing_template_decl ; 

tree
build_static_cast (tree type, tree expr)
{
  tree result;
  bool valid_p;

  if (type == error_mark_node || expr == error_mark_node)
    return error_mark_node;

  if (processing_template_decl)
    {
      expr = build_min (STATIC_CAST_EXPR, type, expr);
      /* We don't know if it will or will not have side effects.  */
      TREE_SIDE_EFFECTS (expr) = 1;
      return convert_from_reference (expr);
    }

  /* build_c_cast puts on a NOP_EXPR to make the result not an lvalue.
     Strip such NOP_EXPRs if VALUE is being used in non-lvalue context.  */
  if (TREE_CODE (type) != REFERENCE_TYPE
      && TREE_CODE (expr) == NOP_EXPR
      && TREE_TYPE (expr) == TREE_TYPE (TREE_OPERAND (expr, 0)))
    expr = TREE_OPERAND (expr, 0);

  result = build_static_cast_1 (type, expr, /*c_cast_p=*/false, &valid_p);
  if (valid_p)
    return result;

  error ("invalid static_cast from type %qT to type %qT",
	 TREE_TYPE (expr), type);
  return error_mark_node;
}