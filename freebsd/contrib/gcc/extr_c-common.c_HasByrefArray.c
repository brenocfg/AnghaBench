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
 scalar_t__ ARRAY_TYPE ; 
 scalar_t__ RECORD_TYPE ; 
 scalar_t__ TREE_CHAIN (scalar_t__) ; 
 scalar_t__ TREE_CODE (scalar_t__) ; 
 scalar_t__ TREE_TYPE (scalar_t__) ; 
 scalar_t__ TYPE_FIELDS (scalar_t__) ; 

int HasByrefArray(tree byrefType)
{
  tree s1;
  /* Check for possibility of an error condition. */
  if (TREE_CODE(byrefType) != RECORD_TYPE)
    return 0;

  for (s1 = TYPE_FIELDS (byrefType); s1; s1 = TREE_CHAIN (s1))
    {
      if (TREE_CODE(TREE_TYPE(s1)) == ARRAY_TYPE)
	 return 1;
    }
  return 0;
}