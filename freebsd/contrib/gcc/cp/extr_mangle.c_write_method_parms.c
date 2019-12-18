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
 int /*<<< orphan*/ * DECL_ARGUMENTS (scalar_t__ const) ; 
 scalar_t__ DECL_ARTIFICIAL (scalar_t__) ; 
 int /*<<< orphan*/ * NULL_TREE ; 
 int /*<<< orphan*/ * TREE_CHAIN (scalar_t__) ; 
 scalar_t__ TREE_VALUE (scalar_t__) ; 
 int /*<<< orphan*/  gcc_assert (int /*<<< orphan*/ ) ; 
 scalar_t__ void_type_node ; 
 int /*<<< orphan*/  write_char (char) ; 
 int /*<<< orphan*/  write_type (scalar_t__) ; 

__attribute__((used)) static void
write_method_parms (tree parm_types, const int method_p, const tree decl)
{
  tree first_parm_type;
  tree parm_decl = decl ? DECL_ARGUMENTS (decl) : NULL_TREE;

  /* Assume this parameter type list is variable-length.  If it ends
     with a void type, then it's not.  */
  int varargs_p = 1;

  /* If this is a member function, skip the first arg, which is the
     this pointer.
       "Member functions do not encode the type of their implicit this
       parameter."

     Similarly, there's no need to mangle artificial parameters, like
     the VTT parameters for constructors and destructors.  */
  if (method_p)
    {
      parm_types = TREE_CHAIN (parm_types);
      parm_decl = parm_decl ? TREE_CHAIN (parm_decl) : NULL_TREE;

      while (parm_decl && DECL_ARTIFICIAL (parm_decl))
	{
	  parm_types = TREE_CHAIN (parm_types);
	  parm_decl = TREE_CHAIN (parm_decl);
	}
    }

  for (first_parm_type = parm_types;
       parm_types;
       parm_types = TREE_CHAIN (parm_types))
    {
      tree parm = TREE_VALUE (parm_types);
      if (parm == void_type_node)
	{
	  /* "Empty parameter lists, whether declared as () or
	     conventionally as (void), are encoded with a void parameter
	     (v)."  */
	  if (parm_types == first_parm_type)
	    write_type (parm);
	  /* If the parm list is terminated with a void type, it's
	     fixed-length.  */
	  varargs_p = 0;
	  /* A void type better be the last one.  */
	  gcc_assert (TREE_CHAIN (parm_types) == NULL);
	}
      else
	write_type (parm);
    }

  if (varargs_p)
    /* <builtin-type> ::= z  # ellipsis  */
    write_char ('z');
}