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
 scalar_t__ POINTER_TYPE_P (scalar_t__) ; 
 scalar_t__ QUAL_UNION_TYPE ; 
 scalar_t__ RECORD_TYPE ; 
 scalar_t__ TREE_CODE (scalar_t__) ; 
 scalar_t__ TREE_TYPE (scalar_t__) ; 
 scalar_t__ TYPE_MAIN_VARIANT (scalar_t__) ; 
 scalar_t__ UNION_TYPE ; 

int
ipa_type_escape_star_count_of_interesting_type (tree type) 
{
  int count = 0;
  /* Strip the *'s off.  */
  if (!type)
    return -1;
  type = TYPE_MAIN_VARIANT (type);
  while (POINTER_TYPE_P (type))
    {
      type = TYPE_MAIN_VARIANT (TREE_TYPE (type));
      count++;
    }

  /* We are interested in records, and unions only.  */
  if (TREE_CODE (type) == RECORD_TYPE 
      || TREE_CODE (type) == QUAL_UNION_TYPE 
      || TREE_CODE (type) == UNION_TYPE)
    return count;
  else 
    return -1;
}