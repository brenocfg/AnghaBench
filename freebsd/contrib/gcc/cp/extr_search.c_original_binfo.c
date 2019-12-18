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
typedef  int /*<<< orphan*/ * tree ;

/* Variables and functions */
 int /*<<< orphan*/ * BINFO_BASE_BINFO (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * BINFO_INHERITANCE_CHAIN (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BINFO_TYPE (int /*<<< orphan*/ *) ; 
 scalar_t__ BINFO_VIRTUAL_P (int /*<<< orphan*/ *) ; 
 scalar_t__ CLASSTYPE_VBASECLASSES (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * NULL_TREE ; 
 scalar_t__ SAME_BINFO_TYPE_P (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * binfo_for_vbase (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

tree
original_binfo (tree binfo, tree here)
{
  tree result = NULL;

  if (SAME_BINFO_TYPE_P (BINFO_TYPE (binfo), BINFO_TYPE (here)))
    result = here;
  else if (BINFO_VIRTUAL_P (binfo))
    result = (CLASSTYPE_VBASECLASSES (BINFO_TYPE (here))
	      ? binfo_for_vbase (BINFO_TYPE (binfo), BINFO_TYPE (here))
	      : NULL_TREE);
  else if (BINFO_INHERITANCE_CHAIN (binfo))
    {
      tree base_binfos;

      base_binfos = original_binfo (BINFO_INHERITANCE_CHAIN (binfo), here);
      if (base_binfos)
	{
	  int ix;
	  tree base_binfo;

	  for (ix = 0; (base_binfo = BINFO_BASE_BINFO (base_binfos, ix)); ix++)
	    if (SAME_BINFO_TYPE_P (BINFO_TYPE (base_binfo),
				   BINFO_TYPE (binfo)))
	      {
		result = base_binfo;
		break;
	      }
	}
    }

  return result;
}