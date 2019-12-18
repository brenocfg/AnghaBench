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
typedef  int /*<<< orphan*/  HOST_WIDE_INT ;

/* Variables and functions */
 scalar_t__ TYPE_VOLATILE (scalar_t__) ; 
 int /*<<< orphan*/  get_alias_set (scalar_t__) ; 

int
objects_must_conflict_p (tree t1, tree t2)
{
  HOST_WIDE_INT set1, set2;

  /* If neither has a type specified, we don't know if they'll conflict
     because we may be using them to store objects of various types, for
     example the argument and local variables areas of inlined functions.  */
  if (t1 == 0 && t2 == 0)
    return 0;

  /* If they are the same type, they must conflict.  */
  if (t1 == t2
      /* Likewise if both are volatile.  */
      || (t1 != 0 && TYPE_VOLATILE (t1) && t2 != 0 && TYPE_VOLATILE (t2)))
    return 1;

  set1 = t1 ? get_alias_set (t1) : 0;
  set2 = t2 ? get_alias_set (t2) : 0;

  /* Otherwise they conflict if they have no alias set or the same. We
     can't simply use alias_sets_conflict_p here, because we must make
     sure that every subtype of t1 will conflict with every subtype of
     t2 for which a pair of subobjects of these respective subtypes
     overlaps on the stack.  */
  return set1 == 0 || set2 == 0 || set1 == set2;
}