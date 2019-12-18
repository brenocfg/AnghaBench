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
 scalar_t__ TREE_CHAIN (scalar_t__) ; 
 int /*<<< orphan*/  TREE_VALUE (scalar_t__) ; 
 int /*<<< orphan*/  same_type_p (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

bool
compparms (tree parms1, tree parms2)
{
  tree t1, t2;

  /* An unspecified parmlist matches any specified parmlist
     whose argument types don't need default promotions.  */

  for (t1 = parms1, t2 = parms2;
       t1 || t2;
       t1 = TREE_CHAIN (t1), t2 = TREE_CHAIN (t2))
    {
      /* If one parmlist is shorter than the other,
	 they fail to match.  */
      if (!t1 || !t2)
	return false;
      if (!same_type_p (TREE_VALUE (t1), TREE_VALUE (t2)))
	return false;
    }
  return true;
}