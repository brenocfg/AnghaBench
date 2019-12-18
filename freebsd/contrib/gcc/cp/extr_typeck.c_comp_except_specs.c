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
 scalar_t__ NULL_TREE ; 
 scalar_t__ TREE_CHAIN (scalar_t__) ; 
 scalar_t__ TREE_VALUE (scalar_t__) ; 
 scalar_t__ comp_except_types (scalar_t__,scalar_t__,int) ; 
 int list_length (scalar_t__) ; 

bool
comp_except_specs (tree t1, tree t2, bool exact)
{
  tree probe;
  tree base;
  int  length = 0;

  if (t1 == t2)
    return true;

  if (t1 == NULL_TREE)			   /* T1 is ...  */
    return t2 == NULL_TREE || !exact;
  if (!TREE_VALUE (t1))			   /* t1 is EMPTY */
    return t2 != NULL_TREE && !TREE_VALUE (t2);
  if (t2 == NULL_TREE)			   /* T2 is ...  */
    return false;
  if (TREE_VALUE (t1) && !TREE_VALUE (t2)) /* T2 is EMPTY, T1 is not */
    return !exact;

  /* Neither set is ... or EMPTY, make sure each part of T2 is in T1.
     Count how many we find, to determine exactness. For exact matching and
     ordered T1, T2, this is an O(n) operation, otherwise its worst case is
     O(nm).  */
  for (base = t1; t2 != NULL_TREE; t2 = TREE_CHAIN (t2))
    {
      for (probe = base; probe != NULL_TREE; probe = TREE_CHAIN (probe))
	{
	  tree a = TREE_VALUE (probe);
	  tree b = TREE_VALUE (t2);

	  if (comp_except_types (a, b, exact))
	    {
	      if (probe == base && exact)
		base = TREE_CHAIN (probe);
	      length++;
	      break;
	    }
	}
      if (probe == NULL_TREE)
	return false;
    }
  return !exact || base == NULL_TREE || length == list_length (t1);
}