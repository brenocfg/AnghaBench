#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ tree ;
typedef  enum tree_code { ____Placeholder_tree_code } tree_code ;
struct TYPE_2__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 scalar_t__ BASELINK_FUNCTIONS (scalar_t__) ; 
 scalar_t__ BASELINK_P (scalar_t__) ; 
 scalar_t__ CLASS_TYPE_P (scalar_t__) ; 
 scalar_t__ COMPLETE_TYPE_P (int /*<<< orphan*/ ) ; 
 scalar_t__ DECL_CLASS_SCOPE_P (scalar_t__) ; 
 scalar_t__ NULL_TREE ; 
 scalar_t__ OVL_CURRENT (scalar_t__) ; 
 scalar_t__ OVL_NEXT (scalar_t__) ; 
 scalar_t__ TREE_CHAIN (scalar_t__) ; 
 scalar_t__ TREE_OPERAND (scalar_t__,int) ; 
 scalar_t__ TREE_TYPE (scalar_t__) ; 
 int /*<<< orphan*/  TREE_VALUE (scalar_t__) ; 
 scalar_t__ TYPE_ARG_TYPES (scalar_t__) ; 
 int /*<<< orphan*/  TYPE_BINFO (scalar_t__) ; 
 scalar_t__ ansi_opname (int) ; 
 scalar_t__ build_cxx_call (scalar_t__,scalar_t__) ; 
 scalar_t__ build_function_call (scalar_t__,scalar_t__) ; 
 scalar_t__ build_tree_list (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  complete_type (scalar_t__) ; 
 scalar_t__ cp_convert (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  error (char*,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ error_mark_node ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 scalar_t__ lookup_fnfields (int /*<<< orphan*/ ,scalar_t__,int) ; 
 scalar_t__ lookup_name_nonclass (scalar_t__) ; 
 int /*<<< orphan*/  mark_used (scalar_t__) ; 
 TYPE_1__* operator_name_info ; 
 int /*<<< orphan*/  perform_or_defer_access_check (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  ptr_type_node ; 
 scalar_t__ same_type_p (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sizetype ; 
 scalar_t__ strip_array_types (scalar_t__) ; 
 scalar_t__ tree_cons (scalar_t__,scalar_t__,scalar_t__) ; 
 scalar_t__ void_list_node ; 
 int /*<<< orphan*/  warning (int /*<<< orphan*/ ,char*,scalar_t__) ; 

tree
build_op_delete_call (enum tree_code code, tree addr, tree size,
		      bool global_p, tree placement,
		      tree alloc_fn)
{
  tree fn = NULL_TREE;
  tree fns, fnname, argtypes, args, type;
  int pass;

  if (addr == error_mark_node)
    return error_mark_node;

  type = strip_array_types (TREE_TYPE (TREE_TYPE (addr)));

  fnname = ansi_opname (code);

  if (CLASS_TYPE_P (type)
      && COMPLETE_TYPE_P (complete_type (type))
      && !global_p)
    /* In [class.free]

       If the result of the lookup is ambiguous or inaccessible, or if
       the lookup selects a placement deallocation function, the
       program is ill-formed.

       Therefore, we ask lookup_fnfields to complain about ambiguity.  */
    {
      fns = lookup_fnfields (TYPE_BINFO (type), fnname, 1);
      if (fns == error_mark_node)
	return error_mark_node;
    }
  else
    fns = NULL_TREE;

  if (fns == NULL_TREE)
    fns = lookup_name_nonclass (fnname);

  if (placement)
    {
      /* Get the parameter types for the allocation function that is
	 being called.  */
      gcc_assert (alloc_fn != NULL_TREE);
      argtypes = TREE_CHAIN (TYPE_ARG_TYPES (TREE_TYPE (alloc_fn)));
      /* Also the second argument.  */
      args = TREE_CHAIN (TREE_OPERAND (placement, 1));
    }
  else
    {
      /* First try it without the size argument.  */
      argtypes = void_list_node;
      args = NULL_TREE;
    }

  /* Strip const and volatile from addr.  */
  addr = cp_convert (ptr_type_node, addr);

  /* We make two tries at finding a matching `operator delete'.  On
     the first pass, we look for a one-operator (or placement)
     operator delete.  If we're not doing placement delete, then on
     the second pass we look for a two-argument delete.  */
  for (pass = 0; pass < (placement ? 1 : 2); ++pass)
    {
      /* Go through the `operator delete' functions looking for one
	 with a matching type.  */
      for (fn = BASELINK_P (fns) ? BASELINK_FUNCTIONS (fns) : fns;
	   fn;
	   fn = OVL_NEXT (fn))
	{
	  tree t;

	  /* The first argument must be "void *".  */
	  t = TYPE_ARG_TYPES (TREE_TYPE (OVL_CURRENT (fn)));
	  if (!same_type_p (TREE_VALUE (t), ptr_type_node))
	    continue;
	  t = TREE_CHAIN (t);
	  /* On the first pass, check the rest of the arguments.  */
	  if (pass == 0)
	    {
	      tree a = argtypes;
	      while (a && t)
		{
		  if (!same_type_p (TREE_VALUE (a), TREE_VALUE (t)))
		    break;
		  a = TREE_CHAIN (a);
		  t = TREE_CHAIN (t);
		}
	      if (!a && !t)
		break;
	    }
	  /* On the second pass, look for a function with exactly two
	     arguments: "void *" and "size_t".  */
	  else if (pass == 1
		   /* For "operator delete(void *, ...)" there will be
		      no second argument, but we will not get an exact
		      match above.  */
		   && t
		   && same_type_p (TREE_VALUE (t), sizetype)
		   && TREE_CHAIN (t) == void_list_node)
	    break;
	}

      /* If we found a match, we're done.  */
      if (fn)
	break;
    }

  /* If we have a matching function, call it.  */
  if (fn)
    {
      /* Make sure we have the actual function, and not an
	 OVERLOAD.  */
      fn = OVL_CURRENT (fn);

      /* If the FN is a member function, make sure that it is
	 accessible.  */
      if (DECL_CLASS_SCOPE_P (fn))
	perform_or_defer_access_check (TYPE_BINFO (type), fn, fn);

      if (pass == 0)
	args = tree_cons (NULL_TREE, addr, args);
      else
	args = tree_cons (NULL_TREE, addr,
			  build_tree_list (NULL_TREE, size));

      if (placement)
	{
	  /* The placement args might not be suitable for overload
	     resolution at this point, so build the call directly.  */
	  mark_used (fn);
	  return build_cxx_call (fn, args);
	}
      else
	return build_function_call (fn, args);
    }

  /* [expr.new]

     If no unambiguous matching deallocation function can be found,
     propagating the exception does not cause the object's memory to
     be freed.  */
  if (alloc_fn)
    {
      if (!placement)
	warning (0, "no corresponding deallocation function for `%D'", 
		 alloc_fn);
      return NULL_TREE;
    }

  error ("no suitable %<operator %s%> for %qT",
	 operator_name_info[(int)code].name, type);
  return error_mark_node;
}