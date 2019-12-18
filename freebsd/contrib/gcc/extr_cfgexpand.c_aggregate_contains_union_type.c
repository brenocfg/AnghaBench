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

__attribute__((used)) static bool
aggregate_contains_union_type (tree type)
{
  tree field;

  if (TREE_CODE (type) == UNION_TYPE
      || TREE_CODE (type) == QUAL_UNION_TYPE)
    return true;
  if (TREE_CODE (type) == ARRAY_TYPE)
    return aggregate_contains_union_type (TREE_TYPE (type));
  if (TREE_CODE (type) != RECORD_TYPE)
    return false;

  for (field = TYPE_FIELDS (type); field; field = TREE_CHAIN (field))
    if (TREE_CODE (field) == FIELD_DECL)
      if (aggregate_contains_union_type (TREE_TYPE (field)))
	return true;

  return false;
}