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
 scalar_t__ SSA_NAME ; 
 scalar_t__ SSA_NAME_VALUE (scalar_t__) ; 
 scalar_t__ TREE_CODE (scalar_t__) ; 
 int /*<<< orphan*/  record_const_or_copy_1 (scalar_t__,scalar_t__,scalar_t__) ; 

__attribute__((used)) static void
record_const_or_copy (tree x, tree y)
{
  tree prev_x = SSA_NAME_VALUE (x);

  if (TREE_CODE (y) == SSA_NAME)
    {
      tree tmp = SSA_NAME_VALUE (y);
      if (tmp)
	y = tmp;
    }

  record_const_or_copy_1 (x, y, prev_x);
}