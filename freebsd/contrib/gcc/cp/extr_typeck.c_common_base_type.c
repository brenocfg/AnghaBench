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
 int /*<<< orphan*/  BINFO_BASE_BINFO (int /*<<< orphan*/ ,int) ; 
 int BINFO_N_BASE_BINFOS (int /*<<< orphan*/ ) ; 
 scalar_t__ BINFO_TYPE (int /*<<< orphan*/ ) ; 
 scalar_t__ NULL_TREE ; 
 int /*<<< orphan*/  TYPE_BINFO (scalar_t__) ; 
 scalar_t__ UNIQUELY_DERIVED_FROM_P (scalar_t__,scalar_t__) ; 
 scalar_t__ error_mark_node ; 

__attribute__((used)) static tree
common_base_type (tree tt1, tree tt2)
{
  tree best = NULL_TREE;
  int i;

  /* If one is a baseclass of another, that's good enough.  */
  if (UNIQUELY_DERIVED_FROM_P (tt1, tt2))
    return tt1;
  if (UNIQUELY_DERIVED_FROM_P (tt2, tt1))
    return tt2;

  /* Otherwise, try to find a unique baseclass of TT1
     that is shared by TT2, and follow that down.  */
  for (i = BINFO_N_BASE_BINFOS (TYPE_BINFO (tt1))-1; i >= 0; i--)
    {
      tree basetype = BINFO_TYPE (BINFO_BASE_BINFO (TYPE_BINFO (tt1), i));
      tree trial = common_base_type (basetype, tt2);

      if (trial)
	{
	  if (trial == error_mark_node)
	    return trial;
	  if (best == NULL_TREE)
	    best = trial;
	  else if (best != trial)
	    return error_mark_node;
	}
    }

  /* Same for TT2.  */
  for (i = BINFO_N_BASE_BINFOS (TYPE_BINFO (tt2))-1; i >= 0; i--)
    {
      tree basetype = BINFO_TYPE (BINFO_BASE_BINFO (TYPE_BINFO (tt2), i));
      tree trial = common_base_type (tt1, basetype);

      if (trial)
	{
	  if (trial == error_mark_node)
	    return trial;
	  if (best == NULL_TREE)
	    best = trial;
	  else if (best != trial)
	    return error_mark_node;
	}
    }
  return best;
}