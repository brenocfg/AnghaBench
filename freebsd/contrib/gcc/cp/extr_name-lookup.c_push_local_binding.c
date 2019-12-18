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
typedef  int /*<<< orphan*/  tree ;
struct cp_binding_level {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IDENTIFIER_BINDING (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NULL_TREE ; 
 scalar_t__ OVERLOAD ; 
 int PUSH_USING ; 
 scalar_t__ TREE_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  add_decl_to_level (int /*<<< orphan*/ ,struct cp_binding_level*) ; 
 int /*<<< orphan*/  build_tree_list (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct cp_binding_level* innermost_nonclass_level () ; 
 scalar_t__ lookup_name_innermost_nonclass_level (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  push_binding (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct cp_binding_level*) ; 
 int /*<<< orphan*/  supplement_binding (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
push_local_binding (tree id, tree decl, int flags)
{
  struct cp_binding_level *b;

  /* Skip over any local classes.  This makes sense if we call
     push_local_binding with a friend decl of a local class.  */
  b = innermost_nonclass_level ();

  if (lookup_name_innermost_nonclass_level (id))
    {
      /* Supplement the existing binding.  */
      if (!supplement_binding (IDENTIFIER_BINDING (id), decl))
	/* It didn't work.  Something else must be bound at this
	   level.  Do not add DECL to the list of things to pop
	   later.  */
	return;
    }
  else
    /* Create a new binding.  */
    push_binding (id, decl, b);

  if (TREE_CODE (decl) == OVERLOAD || (flags & PUSH_USING))
    /* We must put the OVERLOAD into a TREE_LIST since the
       TREE_CHAIN of an OVERLOAD is already used.  Similarly for
       decls that got here through a using-declaration.  */
    decl = build_tree_list (NULL_TREE, decl);

  /* And put DECL on the list of things declared by the current
     binding level.  */
  add_decl_to_level (decl, b);
}