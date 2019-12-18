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
 scalar_t__ TREE_TYPE (scalar_t__) ; 
 scalar_t__ is_bitfield_expr_with_lowered_type (scalar_t__) ; 

tree
unlowered_expr_type (tree exp)
{
  tree type;

  type = is_bitfield_expr_with_lowered_type (exp);
  if (!type)
    type = TREE_TYPE (exp);

  return type;
}