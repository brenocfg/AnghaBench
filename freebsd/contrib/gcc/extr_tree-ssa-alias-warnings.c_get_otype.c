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
 int /*<<< orphan*/  POINTER_TYPE_P (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_TYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gcc_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_main_type (int /*<<< orphan*/ ) ; 

__attribute__((used)) static tree
get_otype (tree object, bool is_ptr)
{
  tree otype = TREE_TYPE (object);

  if (is_ptr)
    {
      gcc_assert (POINTER_TYPE_P (otype));
      otype = TREE_TYPE (otype);
    }
  return get_main_type (otype);
}