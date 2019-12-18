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
 scalar_t__ DECL_INITIAL (scalar_t__) ; 
 scalar_t__ FUNCTION_DECL ; 
 scalar_t__ TREE_CHAIN (scalar_t__) ; 
 scalar_t__ TREE_CODE (scalar_t__) ; 
 int /*<<< orphan*/  TREE_TYPE (scalar_t__) ; 
 scalar_t__ TREE_VALUE (scalar_t__) ; 
 scalar_t__ TYPE_ARG_TYPES (scalar_t__) ; 
 scalar_t__ TYPE_MAIN_VARIANT (scalar_t__) ; 
 scalar_t__ c_type_promotes_to (scalar_t__) ; 
 int /*<<< orphan*/  comptypes (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inform (char*) ; 
 scalar_t__ void_type_node ; 

__attribute__((used)) static void
diagnose_arglist_conflict (tree newdecl, tree olddecl,
			   tree newtype, tree oldtype)
{
  tree t;

  if (TREE_CODE (olddecl) != FUNCTION_DECL
      || !comptypes (TREE_TYPE (oldtype), TREE_TYPE (newtype))
      || !((TYPE_ARG_TYPES (oldtype) == 0 && DECL_INITIAL (olddecl) == 0)
	   ||
	   (TYPE_ARG_TYPES (newtype) == 0 && DECL_INITIAL (newdecl) == 0)))
    return;

  t = TYPE_ARG_TYPES (oldtype);
  if (t == 0)
    t = TYPE_ARG_TYPES (newtype);
  for (; t; t = TREE_CHAIN (t))
    {
      tree type = TREE_VALUE (t);

      if (TREE_CHAIN (t) == 0
	  && TYPE_MAIN_VARIANT (type) != void_type_node)
	{
	  inform ("a parameter list with an ellipsis can%'t match "
		  "an empty parameter name list declaration");
	  break;
	}

      if (c_type_promotes_to (type) != type)
	{
	  inform ("an argument type that has a default promotion can%'t match "
		  "an empty parameter name list declaration");
	  break;
	}
    }
}