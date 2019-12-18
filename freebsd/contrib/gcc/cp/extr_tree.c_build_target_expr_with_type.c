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

/* Variables and functions */
 scalar_t__ CLASS_TYPE_P (int /*<<< orphan*/ ) ; 
 scalar_t__ COND_EXPR ; 
 scalar_t__ CONSTRUCTOR ; 
 scalar_t__ TARGET_EXPR ; 
 scalar_t__ TREE_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TYPE_HAS_TRIVIAL_INIT_REF (int /*<<< orphan*/ ) ; 
 scalar_t__ VA_ARG_EXPR ; 
 int /*<<< orphan*/  VOID_TYPE_P (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  force_rvalue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  force_target_expr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gcc_assert (int) ; 

tree
build_target_expr_with_type (tree init, tree type)
{
  gcc_assert (!VOID_TYPE_P (type));

  if (TREE_CODE (init) == TARGET_EXPR)
    return init;
  else if (CLASS_TYPE_P (type) && !TYPE_HAS_TRIVIAL_INIT_REF (type)
	   && TREE_CODE (init) != COND_EXPR
	   && TREE_CODE (init) != CONSTRUCTOR
	   && TREE_CODE (init) != VA_ARG_EXPR)
    /* We need to build up a copy constructor call.  COND_EXPR is a special
       case because we already have copies on the arms and we don't want
       another one here.  A CONSTRUCTOR is aggregate initialization, which
       is handled separately.  A VA_ARG_EXPR is magic creation of an
       aggregate; there's no additional work to be done.  */
    return force_rvalue (init);

  return force_target_expr (type, init);
}