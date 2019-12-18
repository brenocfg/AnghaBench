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
 scalar_t__ BLKmode ; 
 scalar_t__ DECL_MODE (scalar_t__) ; 
 scalar_t__ TREE_STATIC (scalar_t__) ; 
 scalar_t__ decl_constant_value (scalar_t__) ; 
 scalar_t__ pedantic ; 
 scalar_t__ unshare_expr (scalar_t__) ; 

__attribute__((used)) static tree
decl_constant_value_for_broken_optimization (tree decl)
{
  tree ret;

  if (pedantic || DECL_MODE (decl) == BLKmode)
    return decl;

  ret = decl_constant_value (decl);
  /* Avoid unwanted tree sharing between the initializer and current
     function's body where the tree can be modified e.g. by the
     gimplifier.  */
  if (ret != decl && TREE_STATIC (decl))
    ret = unshare_expr (ret);
  return ret;
}