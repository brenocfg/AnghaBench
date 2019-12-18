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
struct z_candidate {int /*<<< orphan*/  fn; int /*<<< orphan*/  next; } ;

/* Variables and functions */
 int /*<<< orphan*/  DECL_NAME (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LOOKUP_NORMAL ; 
 int /*<<< orphan*/  OVL_CURRENT (char*) ; 
 scalar_t__ TEMPLATE_ID_EXPR ; 
 scalar_t__ TREE_CODE (char*) ; 
 char* TREE_OPERAND (char*,int /*<<< orphan*/ ) ; 
 char* build_function_call (int /*<<< orphan*/ ,char*) ; 
 char* build_over_call (struct z_candidate*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  conversion_obstack ; 
 void* conversion_obstack_alloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  error (char*,int /*<<< orphan*/ ,char*) ; 
 char* error_mark_node ; 
 int /*<<< orphan*/  obstack_free (int /*<<< orphan*/ *,void*) ; 
 struct z_candidate* perform_overload_resolution (char*,char*,struct z_candidate**,int*) ; 
 int /*<<< orphan*/  print_z_candidates (struct z_candidate*) ; 
 char* remove_hidden_names (char*) ; 
 char* resolve_args (char*) ; 

tree
build_new_function_call (tree fn, tree args, bool koenig_p)
{
  struct z_candidate *candidates, *cand;
  bool any_viable_p;
  void *p;
  tree result;

  args = resolve_args (args);
  if (args == error_mark_node)
    return error_mark_node;

  /* If this function was found without using argument dependent
     lookup, then we want to ignore any undeclared friend
     functions.  */
  if (!koenig_p)
    {
      tree orig_fn = fn;

      fn = remove_hidden_names (fn);
      if (!fn)
	{
	  error ("no matching function for call to %<%D(%A)%>",
		 DECL_NAME (OVL_CURRENT (orig_fn)), args);
	  return error_mark_node;
	}
    }

  /* Get the high-water mark for the CONVERSION_OBSTACK.  */
  p = conversion_obstack_alloc (0);

  cand = perform_overload_resolution (fn, args, &candidates, &any_viable_p);

  if (!cand)
    {
      if (!any_viable_p && candidates && ! candidates->next)
	return build_function_call (candidates->fn, args);
      if (TREE_CODE (fn) == TEMPLATE_ID_EXPR)
	fn = TREE_OPERAND (fn, 0);
      if (!any_viable_p)
	error ("no matching function for call to %<%D(%A)%>",
	       DECL_NAME (OVL_CURRENT (fn)), args);
      else
	error ("call of overloaded %<%D(%A)%> is ambiguous",
	       DECL_NAME (OVL_CURRENT (fn)), args);
      if (candidates)
	print_z_candidates (candidates);
      result = error_mark_node;
    }
  else
    result = build_over_call (cand, LOOKUP_NORMAL);

  /* Free all the conversions we allocated.  */
  obstack_free (&conversion_obstack, p);

  return result;
}