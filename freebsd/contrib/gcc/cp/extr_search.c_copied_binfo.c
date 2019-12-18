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
 scalar_t__ BINFO_BASE_ITERATE (scalar_t__,int,scalar_t__) ; 
 scalar_t__ BINFO_INHERITANCE_CHAIN (scalar_t__) ; 
 int /*<<< orphan*/  BINFO_TYPE (scalar_t__) ; 
 scalar_t__ BINFO_VIRTUAL_P (scalar_t__) ; 
 scalar_t__ NULL_TREE ; 
 scalar_t__ SAME_BINFO_TYPE_P (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ binfo_for_vbase (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gcc_assert (scalar_t__) ; 

tree
copied_binfo (tree binfo, tree here)
{
  tree result = NULL_TREE;

  if (BINFO_VIRTUAL_P (binfo))
    {
      tree t;

      for (t = here; BINFO_INHERITANCE_CHAIN (t);
	   t = BINFO_INHERITANCE_CHAIN (t))
	continue;

      result = binfo_for_vbase (BINFO_TYPE (binfo), BINFO_TYPE (t));
    }
  else if (BINFO_INHERITANCE_CHAIN (binfo))
    {
      tree cbinfo;
      tree base_binfo;
      int ix;

      cbinfo = copied_binfo (BINFO_INHERITANCE_CHAIN (binfo), here);
      for (ix = 0; BINFO_BASE_ITERATE (cbinfo, ix, base_binfo); ix++)
	if (SAME_BINFO_TYPE_P (BINFO_TYPE (base_binfo), BINFO_TYPE (binfo)))
	  {
	    result = base_binfo;
	    break;
	  }
    }
  else
    {
      gcc_assert (SAME_BINFO_TYPE_P (BINFO_TYPE (here), BINFO_TYPE (binfo)));
      result = here;
    }

  gcc_assert (result);
  return result;
}