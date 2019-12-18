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
struct z_candidate {int dummy; } ;

/* Variables and functions */
 scalar_t__ BINFO_TYPE (scalar_t__) ; 
 scalar_t__ DECL_NONSTATIC_MEMBER_FUNCTION_P (scalar_t__) ; 
 int /*<<< orphan*/  DEDUCE_CALL ; 
 scalar_t__ NULL_TREE ; 
 scalar_t__ OVL_CURRENT (scalar_t__) ; 
 scalar_t__ OVL_NEXT (scalar_t__) ; 
 scalar_t__ TEMPLATE_DECL ; 
 int /*<<< orphan*/  TREE_CHAIN (scalar_t__) ; 
 scalar_t__ TREE_CODE (scalar_t__) ; 
 int /*<<< orphan*/  TREE_VALUE (scalar_t__) ; 
 int /*<<< orphan*/  add_function_candidate (struct z_candidate**,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,int) ; 
 int /*<<< orphan*/  add_template_candidate (struct z_candidate**,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  build_this (int /*<<< orphan*/ ) ; 
 scalar_t__ tree_cons (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
add_candidates (tree fns, tree args,
		tree explicit_targs, bool template_only,
		tree conversion_path, tree access_path,
		int flags,
		struct z_candidate **candidates)
{
  tree ctype;
  tree non_static_args;

  ctype = conversion_path ? BINFO_TYPE (conversion_path) : NULL_TREE;
  /* Delay creating the implicit this parameter until it is needed.  */
  non_static_args = NULL_TREE;

  while (fns)
    {
      tree fn;
      tree fn_args;

      fn = OVL_CURRENT (fns);
      /* Figure out which set of arguments to use.  */
      if (DECL_NONSTATIC_MEMBER_FUNCTION_P (fn))
	{
	  /* If this function is a non-static member, prepend the implicit
	     object parameter.  */
	  if (!non_static_args)
	    non_static_args = tree_cons (NULL_TREE,
					 build_this (TREE_VALUE (args)),
					 TREE_CHAIN (args));
	  fn_args = non_static_args;
	}
      else
	/* Otherwise, just use the list of arguments provided.  */
	fn_args = args;

      if (TREE_CODE (fn) == TEMPLATE_DECL)
	add_template_candidate (candidates,
				fn,
				ctype,
				explicit_targs,
				fn_args,
				NULL_TREE,
				access_path,
				conversion_path,
				flags,
				DEDUCE_CALL);
      else if (!template_only)
	add_function_candidate (candidates,
				fn,
				ctype,
				fn_args,
				access_path,
				conversion_path,
				flags);
      fns = OVL_NEXT (fns);
    }
}