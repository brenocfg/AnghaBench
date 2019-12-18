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
 scalar_t__ BINFO_BASE_ITERATE (scalar_t__,int,scalar_t__) ; 
 scalar_t__ BINFO_TYPE (scalar_t__) ; 
 scalar_t__ FIELD_DECL ; 
 scalar_t__ QUAL_UNION_TYPE ; 
 scalar_t__ RECORD_TYPE ; 
 scalar_t__ TREE_CHAIN (scalar_t__) ; 
 scalar_t__ TREE_CODE (scalar_t__) ; 
 scalar_t__ TREE_TYPE (scalar_t__) ; 
 scalar_t__ TYPE_BINFO (scalar_t__) ; 
 scalar_t__ TYPE_FIELDS (scalar_t__) ; 
 scalar_t__ UNION_TYPE ; 

__attribute__((used)) static bool
parent_type_p (tree parent, tree child)
{
  int i;
  tree binfo, base_binfo;
  if (TYPE_BINFO (parent)) 
    for (binfo = TYPE_BINFO (parent), i = 0;
	 BINFO_BASE_ITERATE (binfo, i, base_binfo); i++)
      {
	tree binfotype = BINFO_TYPE (base_binfo);
	if (binfotype == child) 
	  return true;
	else if (parent_type_p (binfotype, child))
	  return true;
      }
  if (TREE_CODE (parent) == UNION_TYPE
      || TREE_CODE (parent) == QUAL_UNION_TYPE) 
    {
      tree field;
      /* Search all of the variants in the union to see if one of them
	 is the child.  */
      for (field = TYPE_FIELDS (parent);
	   field;
	   field = TREE_CHAIN (field))
	{
	  tree field_type;
	  if (TREE_CODE (field) != FIELD_DECL)
	    continue;
	  
	  field_type = TREE_TYPE (field);
	  if (field_type == child) 
	    return true;
	}

      /* If we did not find it, recursively ask the variants if one of
	 their children is the child type.  */
      for (field = TYPE_FIELDS (parent);
	   field;
	   field = TREE_CHAIN (field))
	{
	  tree field_type;
	  if (TREE_CODE (field) != FIELD_DECL)
	    continue;
	  
	  field_type = TREE_TYPE (field);
	  if (TREE_CODE (field_type) == RECORD_TYPE 
	      || TREE_CODE (field_type) == QUAL_UNION_TYPE 
	      || TREE_CODE (field_type) == UNION_TYPE)
	    if (parent_type_p (field_type, child)) 
	      return true;
	}
    }
  
  if (TREE_CODE (parent) == RECORD_TYPE)
    {
      tree field;
      for (field = TYPE_FIELDS (parent);
	   field;
	   field = TREE_CHAIN (field))
	{
	  tree field_type;
	  if (TREE_CODE (field) != FIELD_DECL)
	    continue;
	  
	  field_type = TREE_TYPE (field);
	  if (field_type == child) 
	    return true;
	  /* You can only cast to the first field so if it does not
	     match, quit.  */
	  if (TREE_CODE (field_type) == RECORD_TYPE 
	      || TREE_CODE (field_type) == QUAL_UNION_TYPE 
	      || TREE_CODE (field_type) == UNION_TYPE)
	    {
	      if (parent_type_p (field_type, child)) 
		return true;
	      else 
		break;
	    }
	}
    }
  return false;
}