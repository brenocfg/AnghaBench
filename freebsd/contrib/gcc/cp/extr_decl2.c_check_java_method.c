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
typedef  char* tree ;

/* Variables and functions */
 scalar_t__ DECL_HAS_IN_CHARGE_PARM_P (char*) ; 
 scalar_t__ DECL_HAS_VTT_PARM_P (char*) ; 
 char* NULL_TREE ; 
 char* TREE_CHAIN (char*) ; 
 char* TREE_TYPE (char*) ; 
 char* TREE_VALUE (char*) ; 
 char* TYPE_ARG_TYPES (char*) ; 
 int /*<<< orphan*/  acceptable_java_type (char*) ; 
 int /*<<< orphan*/  error (char*,char*,char*) ; 
 char* error_mark_node ; 

bool
check_java_method (tree method)
{
  bool jerr = false;
  tree arg_types = TYPE_ARG_TYPES (TREE_TYPE (method));
  tree ret_type = TREE_TYPE (TREE_TYPE (method));

  if (!acceptable_java_type (ret_type))
    {
      error ("Java method %qD has non-Java return type %qT",
	     method, ret_type);
      jerr = true;
    }

  arg_types = TREE_CHAIN (arg_types);
  if (DECL_HAS_IN_CHARGE_PARM_P (method))
    arg_types = TREE_CHAIN (arg_types);
  if (DECL_HAS_VTT_PARM_P (method))
    arg_types = TREE_CHAIN (arg_types);

  for (; arg_types != NULL_TREE; arg_types = TREE_CHAIN (arg_types))
    {
      tree type = TREE_VALUE (arg_types);
      if (!acceptable_java_type (type))
	{
          if (type != error_mark_node)
	    error ("Java method %qD has non-Java parameter type %qT",
		   method, type);
	  jerr = true;
	}
    }
  return !jerr;
}