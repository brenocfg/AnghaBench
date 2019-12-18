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
 scalar_t__ DECL_ORIGINAL_TYPE (scalar_t__) ; 
 scalar_t__ NULL_TREE ; 
 scalar_t__ TREE_CODE (scalar_t__) ; 
 scalar_t__ TYPE_DECL ; 
 scalar_t__ TYPE_NAME (scalar_t__) ; 
 scalar_t__ cp_build_qualified_type (scalar_t__,int) ; 
 int cp_type_quals (scalar_t__) ; 
 scalar_t__ error_mark_node ; 

__attribute__((used)) static tree
original_type (tree t)
{
  int quals = cp_type_quals (t);
  while (t != error_mark_node
	 && TYPE_NAME (t) != NULL_TREE)
    {
      tree x = TYPE_NAME (t);
      if (TREE_CODE (x) != TYPE_DECL)
	break;
      x = DECL_ORIGINAL_TYPE (x);
      if (x == NULL_TREE)
	break;
      t = x;
    }
  return cp_build_qualified_type (t, quals);
}