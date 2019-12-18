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

/* Variables and functions */
 int /*<<< orphan*/  CONV_OLD_CONVERT ; 
 int LOOKUP_NORMAL ; 
 int LOOKUP_NO_CONVERSION ; 
 scalar_t__ POINTER_TYPE_P (scalar_t__) ; 
 scalar_t__ TREE_TYPE (scalar_t__) ; 
 int /*<<< orphan*/  build_nop (scalar_t__,scalar_t__) ; 
 scalar_t__ error_mark_node ; 
 scalar_t__ fold_if_not_in_template (int /*<<< orphan*/ ) ; 
 scalar_t__ ocp_convert (scalar_t__,scalar_t__,int /*<<< orphan*/ ,int) ; 

tree
convert (tree type, tree expr)
{
  tree intype;

  if (type == error_mark_node || expr == error_mark_node)
    return error_mark_node;

  intype = TREE_TYPE (expr);

  if (POINTER_TYPE_P (type) && POINTER_TYPE_P (intype))
    return fold_if_not_in_template (build_nop (type, expr));

  return ocp_convert (type, expr, CONV_OLD_CONVERT,
		      LOOKUP_NORMAL|LOOKUP_NO_CONVERSION);
}