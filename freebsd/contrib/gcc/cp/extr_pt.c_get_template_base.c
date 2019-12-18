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
 int /*<<< orphan*/  BINFO_TYPE (scalar_t__) ; 
 int /*<<< orphan*/  IS_AGGR_TYPE_CODE (int /*<<< orphan*/ ) ; 
 scalar_t__ NULL_TREE ; 
 scalar_t__ TREE_CHAIN (scalar_t__) ; 
 int /*<<< orphan*/  TREE_CODE (scalar_t__) ; 
 scalar_t__ TYPE_BINFO (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  complete_type (scalar_t__) ; 
 int /*<<< orphan*/  gcc_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  same_type_p (scalar_t__,scalar_t__) ; 
 scalar_t__ try_class_unification (scalar_t__,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static tree
get_template_base (tree tparms, tree targs, tree parm, tree arg)
{
  tree rval = NULL_TREE;
  tree binfo;

  gcc_assert (IS_AGGR_TYPE_CODE (TREE_CODE (arg)));

  binfo = TYPE_BINFO (complete_type (arg));
  if (!binfo)
    /* The type could not be completed.  */
    return NULL_TREE;

  /* Walk in inheritance graph order.  The search order is not
     important, and this avoids multiple walks of virtual bases.  */
  for (binfo = TREE_CHAIN (binfo); binfo; binfo = TREE_CHAIN (binfo))
    {
      tree r = try_class_unification (tparms, targs, parm, BINFO_TYPE (binfo));

      if (r)
	{
	  /* If there is more than one satisfactory baseclass, then:

	       [temp.deduct.call]

	      If they yield more than one possible deduced A, the type
	      deduction fails.

	     applies.  */
	  if (rval && !same_type_p (r, rval))
	    return NULL_TREE;

	  rval = r;
	}
    }

  return rval;
}