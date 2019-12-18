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
 scalar_t__ TREE_CHAIN (scalar_t__) ; 
 scalar_t__ TREE_TYPE (scalar_t__) ; 
 scalar_t__ TREE_VALUE (scalar_t__) ; 
 scalar_t__ TYPE_ARG_TYPES (scalar_t__) ; 
 int /*<<< orphan*/  TYPE_ATTRIBUTES (scalar_t__) ; 
 scalar_t__ TYPE_MODE (scalar_t__) ; 
 scalar_t__ build_function_type (scalar_t__,scalar_t__) ; 
 scalar_t__ build_type_attribute_variant (scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static tree
match_builtin_function_types (tree newtype, tree oldtype)
{
  tree newrettype, oldrettype;
  tree newargs, oldargs;
  tree trytype, tryargs;

  /* Accept the return type of the new declaration if same modes.  */
  oldrettype = TREE_TYPE (oldtype);
  newrettype = TREE_TYPE (newtype);

  if (TYPE_MODE (oldrettype) != TYPE_MODE (newrettype))
    return 0;

  oldargs = TYPE_ARG_TYPES (oldtype);
  newargs = TYPE_ARG_TYPES (newtype);
  tryargs = newargs;

  while (oldargs || newargs)
    {
      if (!oldargs
	  || !newargs
	  || !TREE_VALUE (oldargs)
	  || !TREE_VALUE (newargs)
	  || TYPE_MODE (TREE_VALUE (oldargs))
	     != TYPE_MODE (TREE_VALUE (newargs)))
	return 0;

      oldargs = TREE_CHAIN (oldargs);
      newargs = TREE_CHAIN (newargs);
    }

  trytype = build_function_type (newrettype, tryargs);
  return build_type_attribute_variant (trytype, TYPE_ATTRIBUTES (oldtype));
}