#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ tree ;
struct TYPE_3__ {scalar_t__ (* type_for_size ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
struct TYPE_4__ {TYPE_1__ types; } ;

/* Variables and functions */
#define  BLOCK_POINTER_TYPE 133 
#define  BOOLEAN_TYPE 132 
 int /*<<< orphan*/  CONVERT_EXPR ; 
#define  ENUMERAL_TYPE 131 
#define  INTEGER_TYPE 130 
 int /*<<< orphan*/  NOP_EXPR ; 
 int /*<<< orphan*/  POINTER_SIZE ; 
#define  POINTER_TYPE 129 
#define  REFERENCE_TYPE 128 
 int const TREE_CODE (scalar_t__) ; 
 scalar_t__ TREE_CONSTANT_OVERFLOW (scalar_t__) ; 
 scalar_t__ TREE_OVERFLOW (scalar_t__) ; 
 scalar_t__ TREE_TYPE (scalar_t__) ; 
 int /*<<< orphan*/  TYPE_PRECISION (scalar_t__) ; 
 int /*<<< orphan*/  VOID_TYPE_P (scalar_t__) ; 
 scalar_t__ build_int_cst (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  error (char*) ; 
 scalar_t__ fold_build1 (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 scalar_t__ force_fit_type (scalar_t__,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 scalar_t__ integer_zero_node ; 
 scalar_t__ integer_zerop (scalar_t__) ; 
 TYPE_2__ lang_hooks ; 
 int /*<<< orphan*/  objc_is_id (scalar_t__) ; 
 scalar_t__ stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

tree
convert_to_pointer (tree type, tree expr)
{
  if (TREE_TYPE (expr) == type)
    return expr;

  if (integer_zerop (expr))
    {
      tree t = build_int_cst (type, 0);
      if (TREE_OVERFLOW (expr) || TREE_CONSTANT_OVERFLOW (expr))
	t = force_fit_type (t, 0, TREE_OVERFLOW (expr),
			    TREE_CONSTANT_OVERFLOW (expr));
      return t;
    }

  switch (TREE_CODE (TREE_TYPE (expr)))
    {
    case POINTER_TYPE:
    case REFERENCE_TYPE:
      return fold_build1 (NOP_EXPR, type, expr);

    case INTEGER_TYPE:
    case ENUMERAL_TYPE:
    case BOOLEAN_TYPE:
      if (TYPE_PRECISION (TREE_TYPE (expr)) != POINTER_SIZE)
	expr = fold_build1 (NOP_EXPR,
			     lang_hooks.types.type_for_size (POINTER_SIZE, 0),
			    expr);
      return fold_build1 (CONVERT_EXPR, type, expr);

	/* APPLE LOCAL begin blocks (C++ ck) */
    case BLOCK_POINTER_TYPE:
	/* APPLE LOCAL begin radar 5809099 */
	if (objc_is_id (type)
		|| (TREE_CODE (type) == POINTER_TYPE && VOID_TYPE_P (TREE_TYPE (type))))
	/* APPLE LOCAL end radar 5809099 */
		return fold_build1 (NOP_EXPR, type, expr);
	/* APPLE LOCAL end blocks (C++ ck) */
      default:
	error ("cannot convert to a pointer type");
	return convert_to_pointer (type, integer_zero_node);
    }
}