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
 scalar_t__ DECL_P (scalar_t__) ; 
 scalar_t__ DECL_SIZE_UNIT (scalar_t__) ; 
 int /*<<< orphan*/  TREE_TYPE (scalar_t__) ; 
 scalar_t__ size_in_bytes (int /*<<< orphan*/ ) ; 

tree
lhd_expr_size (tree exp)
{
  if (DECL_P (exp)
      && DECL_SIZE_UNIT (exp) != 0)
    return DECL_SIZE_UNIT (exp);
  else
    return size_in_bytes (TREE_TYPE (exp));
}