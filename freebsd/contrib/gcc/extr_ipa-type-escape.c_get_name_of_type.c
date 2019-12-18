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
 scalar_t__ DECL_NAME (scalar_t__) ; 
 scalar_t__ IDENTIFIER_NODE ; 
 scalar_t__ IDENTIFIER_POINTER (scalar_t__) ; 
 scalar_t__ TREE_CODE (scalar_t__) ; 
 scalar_t__ TYPE_DECL ; 
 scalar_t__ TYPE_NAME (scalar_t__) ; 

__attribute__((used)) static char*
get_name_of_type (tree type)
{
  tree name = TYPE_NAME (type);
  
  if (!name)
    /* Unnamed type, do what you like here.  */
    return (char*)"<UNNAMED>";
  
  /* It will be a TYPE_DECL in the case of a typedef, otherwise, an
     identifier_node */
  if (TREE_CODE (name) == TYPE_DECL)
    {
      /*  Each DECL has a DECL_NAME field which contains an
	  IDENTIFIER_NODE.  (Some decls, most often labels, may have
	  zero as the DECL_NAME).  */
      if (DECL_NAME (name))
	return (char*)IDENTIFIER_POINTER (DECL_NAME (name));
      else
	/* Unnamed type, do what you like here.  */
	return (char*)"<UNNAMED>";
    }
  else if (TREE_CODE (name) == IDENTIFIER_NODE)
    return (char*)IDENTIFIER_POINTER (name);
  else 
    return (char*)"<UNNAMED>";
}