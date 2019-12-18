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
struct arg_lookup {scalar_t__ args; int /*<<< orphan*/  name; int /*<<< orphan*/  namespaces; } ;

/* Variables and functions */
 scalar_t__ DECL_NAMESPACE_ASSOCIATIONS (scalar_t__) ; 
 int /*<<< orphan*/  NULL_TREE ; 
 int /*<<< orphan*/  OVL_CURRENT (scalar_t__) ; 
 scalar_t__ OVL_NEXT (scalar_t__) ; 
 scalar_t__ TREE_CHAIN (scalar_t__) ; 
 scalar_t__ TREE_PURPOSE (scalar_t__) ; 
 int /*<<< orphan*/  TREE_VALUE (scalar_t__) ; 
 scalar_t__ add_function (struct arg_lookup*,int /*<<< orphan*/ ) ; 
 scalar_t__ friend_of_associated_class_p (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ hidden_name_p (int /*<<< orphan*/ ) ; 
 scalar_t__ namespace_binding (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ purpose_member (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tree_cons (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
arg_assoc_namespace (struct arg_lookup *k, tree scope)
{
  tree value;

  if (purpose_member (scope, k->namespaces))
    return 0;
  k->namespaces = tree_cons (scope, NULL_TREE, k->namespaces);

  /* Check out our super-users.  */
  for (value = DECL_NAMESPACE_ASSOCIATIONS (scope); value;
       value = TREE_CHAIN (value))
    if (arg_assoc_namespace (k, TREE_PURPOSE (value)))
      return true;

  value = namespace_binding (k->name, scope);
  if (!value)
    return false;

  for (; value; value = OVL_NEXT (value))
    {
      /* We don't want to find arbitrary hidden functions via argument
	 dependent lookup.  We only want to find friends of associated
	 classes.  */
      if (hidden_name_p (OVL_CURRENT (value)))
	{
	  tree args;

	  for (args = k->args; args; args = TREE_CHAIN (args))
	    if (friend_of_associated_class_p (TREE_VALUE (args),
					      OVL_CURRENT (value)))
	      break;
	  if (!args)
	    continue;
	}

      if (add_function (k, OVL_CURRENT (value)))
	return true;
    }

  return false;
}