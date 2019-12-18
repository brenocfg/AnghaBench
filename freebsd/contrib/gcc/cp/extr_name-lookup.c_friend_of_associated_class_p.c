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
 scalar_t__ CLASS_TYPE_P (scalar_t__) ; 
 scalar_t__ ENUMERAL_TYPE ; 
 scalar_t__ TREE_CODE (scalar_t__) ; 
 scalar_t__ TREE_TYPE (scalar_t__) ; 
 scalar_t__ TYPE_BINFO (scalar_t__) ; 
 scalar_t__ TYPE_CONTEXT (scalar_t__) ; 
 scalar_t__ TYPE_P (scalar_t__) ; 
 scalar_t__ UNION_TYPE ; 
 scalar_t__ is_friend (scalar_t__,scalar_t__) ; 
 scalar_t__ type_unknown_p (scalar_t__) ; 

__attribute__((used)) static bool
friend_of_associated_class_p (tree arg, tree fn)
{
  tree type;

  if (TYPE_P (arg))
    type = arg;
  else if (type_unknown_p (arg))
    return false;
  else
    type = TREE_TYPE (arg);

  /* If TYPE is a class, the class itself and all base classes are
     associated classes.  */
  if (CLASS_TYPE_P (type))
    {
      if (is_friend (type, fn))
	return true;

      if (TYPE_BINFO (type))
	{
	  tree binfo, base_binfo;
	  int i;

	  for (binfo = TYPE_BINFO (type), i = 0;
	       BINFO_BASE_ITERATE (binfo, i, base_binfo);
	       i++)
	    if (is_friend (BINFO_TYPE (base_binfo), fn))
	      return true;
	}
    }

  /* If TYPE is a class member, the class of which it is a member is
     an associated class.  */
  if ((CLASS_TYPE_P (type)
       || TREE_CODE (type) == UNION_TYPE
       || TREE_CODE (type) == ENUMERAL_TYPE)
      && TYPE_CONTEXT (type)
      && CLASS_TYPE_P (TYPE_CONTEXT (type))
      && is_friend (TYPE_CONTEXT (type), fn))
    return true;

  return false;
}