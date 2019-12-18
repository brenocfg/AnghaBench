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
 scalar_t__ TEMPLATE_PARM_INDEX ; 
 int TEMPLATE_PARM_LEVEL (int /*<<< orphan*/ ) ; 
 int TEMPLATE_TYPE_LEVEL (int /*<<< orphan*/ ) ; 
 scalar_t__ TREE_CODE (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
template_parm_this_level_p (tree t, void* data)
{
  int this_level = *(int *)data;
  int level;

  if (TREE_CODE (t) == TEMPLATE_PARM_INDEX)
    level = TEMPLATE_PARM_LEVEL (t);
  else
    level = TEMPLATE_TYPE_LEVEL (t);
  return level == this_level;
}