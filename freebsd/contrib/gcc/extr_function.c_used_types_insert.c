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
 scalar_t__ ARRAY_TYPE ; 
 scalar_t__ DINFO_LEVEL_NONE ; 
 scalar_t__ POINTER_TYPE_P (int /*<<< orphan*/ ) ; 
 scalar_t__ TREE_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_TYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TYPE_MAIN_VARIANT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cfun ; 
 scalar_t__ debug_info_level ; 
 int /*<<< orphan*/  used_types_insert_helper (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
used_types_insert (tree t)
{
  while (POINTER_TYPE_P (t) || TREE_CODE (t) == ARRAY_TYPE)
    t = TREE_TYPE (t);
  t = TYPE_MAIN_VARIANT (t);
  if (debug_info_level > DINFO_LEVEL_NONE)
    used_types_insert_helper (t, cfun);
}