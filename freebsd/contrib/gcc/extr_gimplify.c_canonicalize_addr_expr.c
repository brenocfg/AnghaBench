#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tree ;
struct TYPE_2__ {int /*<<< orphan*/  (* types_compatible_p ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  ADDR_EXPR ; 
 int /*<<< orphan*/  ARRAY_REF ; 
 scalar_t__ ARRAY_TYPE ; 
 scalar_t__ INTEGER_CST ; 
 int /*<<< orphan*/  NULL_TREE ; 
 int /*<<< orphan*/  POINTER_TYPE_P (int /*<<< orphan*/ ) ; 
 scalar_t__ TREE_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_OPERAND (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_TYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TYPE_DOMAIN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TYPE_MIN_VALUE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TYPE_SIZE_UNIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  build1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  build4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__ lang_hooks ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
canonicalize_addr_expr (tree *expr_p)
{
  tree expr = *expr_p;
  tree ctype = TREE_TYPE (expr);
  tree addr_expr = TREE_OPERAND (expr, 0);
  tree atype = TREE_TYPE (addr_expr);
  tree dctype, datype, ddatype, otype, obj_expr;

  /* Both cast and addr_expr types should be pointers.  */
  if (!POINTER_TYPE_P (ctype) || !POINTER_TYPE_P (atype))
    return;

  /* The addr_expr type should be a pointer to an array.  */
  datype = TREE_TYPE (atype);
  if (TREE_CODE (datype) != ARRAY_TYPE)
    return;

  /* Both cast and addr_expr types should address the same object type.  */
  dctype = TREE_TYPE (ctype);
  ddatype = TREE_TYPE (datype);
  if (!lang_hooks.types_compatible_p (ddatype, dctype))
    return;

  /* The addr_expr and the object type should match.  */
  obj_expr = TREE_OPERAND (addr_expr, 0);
  otype = TREE_TYPE (obj_expr);
  if (!lang_hooks.types_compatible_p (otype, datype))
    return;

  /* The lower bound and element sizes must be constant.  */
  if (!TYPE_SIZE_UNIT (dctype)
      || TREE_CODE (TYPE_SIZE_UNIT (dctype)) != INTEGER_CST
      || !TYPE_DOMAIN (datype) || !TYPE_MIN_VALUE (TYPE_DOMAIN (datype))
      || TREE_CODE (TYPE_MIN_VALUE (TYPE_DOMAIN (datype))) != INTEGER_CST)
    return;

  /* All checks succeeded.  Build a new node to merge the cast.  */
  *expr_p = build4 (ARRAY_REF, dctype, obj_expr,
		    TYPE_MIN_VALUE (TYPE_DOMAIN (datype)),
		    NULL_TREE, NULL_TREE);
  *expr_p = build1 (ADDR_EXPR, ctype, *expr_p);
}