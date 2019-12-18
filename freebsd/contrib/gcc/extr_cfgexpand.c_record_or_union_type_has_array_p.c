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
 scalar_t__ FIELD_DECL ; 
 scalar_t__ QUAL_UNION_TYPE ; 
 scalar_t__ RECORD_TYPE ; 
 scalar_t__ TREE_CHAIN (scalar_t__) ; 
 scalar_t__ TREE_CODE (scalar_t__) ; 
 scalar_t__ TREE_TYPE (scalar_t__) ; 
 scalar_t__ TYPE_FIELDS (scalar_t__) ; 
 scalar_t__ UNION_TYPE ; 

__attribute__((used)) static int
record_or_union_type_has_array_p (tree tree_type)
{
  tree fields = TYPE_FIELDS (tree_type);
  tree f;

  for (f = fields; f; f = TREE_CHAIN (f))
    if (TREE_CODE (f) == FIELD_DECL)
      {
	tree field_type = TREE_TYPE (f);
	if ((TREE_CODE (field_type) == RECORD_TYPE
	     || TREE_CODE (field_type) == UNION_TYPE
	     || TREE_CODE (field_type) == QUAL_UNION_TYPE)
	    && record_or_union_type_has_array_p (field_type))
	  return 1;
	if (TREE_CODE (field_type) == ARRAY_TYPE)
	  return 1;
      }
  return 0;
}