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
 scalar_t__ FUNCTION_DECL ; 
 scalar_t__ NULL_TREE ; 
 scalar_t__ OVERLOAD ; 
 scalar_t__ OVL_CURRENT (scalar_t__) ; 
 scalar_t__ OVL_NEXT (scalar_t__) ; 
 scalar_t__ TREE_CODE (scalar_t__) ; 
 scalar_t__ build_overload (scalar_t__,scalar_t__) ; 
 scalar_t__ hidden_name_p (scalar_t__) ; 

tree
remove_hidden_names (tree fns)
{
  if (!fns)
    return fns;

  if (TREE_CODE (fns) == FUNCTION_DECL && hidden_name_p (fns))
    fns = NULL_TREE;
  else if (TREE_CODE (fns) == OVERLOAD)
    {
      tree o;

      for (o = fns; o; o = OVL_NEXT (o))
	if (hidden_name_p (OVL_CURRENT (o)))
	  break;
      if (o)
	{
	  tree n = NULL_TREE;

	  for (o = fns; o; o = OVL_NEXT (o))
	    if (!hidden_name_p (OVL_CURRENT (o)))
	      n = build_overload (OVL_CURRENT (o), n);
	  fns = n;
	}
    }

  return fns;
}