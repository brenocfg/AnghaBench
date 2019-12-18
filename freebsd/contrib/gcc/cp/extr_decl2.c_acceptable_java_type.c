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
 int /*<<< orphan*/  CLASSTYPE_TEMPLATE_INFO (scalar_t__) ; 
 scalar_t__ CLASSTYPE_TI_ARGS (scalar_t__) ; 
 scalar_t__ POINTER_TYPE ; 
 scalar_t__ RECORD_TYPE ; 
 scalar_t__ REFERENCE_TYPE ; 
 scalar_t__ TREE_CODE (scalar_t__) ; 
 scalar_t__ TREE_TYPE (scalar_t__) ; 
 scalar_t__ TREE_VEC_ELT (scalar_t__,int) ; 
 int TREE_VEC_LENGTH (scalar_t__) ; 
 scalar_t__ TYPE_FOR_JAVA (scalar_t__) ; 
 scalar_t__ VOID_TYPE ; 
 scalar_t__ error_mark_node ; 

__attribute__((used)) static bool
acceptable_java_type (tree type)
{
  if (type == error_mark_node)
    return false;

  if (TREE_CODE (type) == VOID_TYPE || TYPE_FOR_JAVA (type))
    return true;
  if (TREE_CODE (type) == POINTER_TYPE || TREE_CODE (type) == REFERENCE_TYPE)
    {
      type = TREE_TYPE (type);
      if (TREE_CODE (type) == RECORD_TYPE)
	{
	  tree args;  int i;
	  if (! TYPE_FOR_JAVA (type))
	    return false;
	  if (! CLASSTYPE_TEMPLATE_INFO (type))
	    return true;
	  args = CLASSTYPE_TI_ARGS (type);
	  i = TREE_VEC_LENGTH (args);
	  while (--i >= 0)
	    {
	      type = TREE_VEC_ELT (args, i);
	      if (TREE_CODE (type) == POINTER_TYPE)
		type = TREE_TYPE (type);
	      if (! TYPE_FOR_JAVA (type))
		return false;
	    }
	  return true;
	}
    }
  return false;
}