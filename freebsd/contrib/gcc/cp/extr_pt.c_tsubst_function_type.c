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
typedef  int tsubst_flags_t ;
typedef  scalar_t__ tree ;

/* Variables and functions */
 scalar_t__ ARRAY_TYPE ; 
 scalar_t__ FUNCTION_TYPE ; 
 int /*<<< orphan*/  IS_AGGR_TYPE (scalar_t__) ; 
 scalar_t__ NULL_TREE ; 
 int /*<<< orphan*/  TREE_CHAIN (scalar_t__) ; 
 scalar_t__ TREE_CODE (scalar_t__) ; 
 scalar_t__ TREE_TYPE (scalar_t__) ; 
 scalar_t__ TREE_VALUE (scalar_t__) ; 
 int /*<<< orphan*/  TYPE_ARG_TYPES (scalar_t__) ; 
 int /*<<< orphan*/  TYPE_ATTRIBUTES (scalar_t__) ; 
 scalar_t__ TYPE_CONTEXT (scalar_t__) ; 
 int /*<<< orphan*/  TYPE_QUALS (scalar_t__) ; 
 scalar_t__ build_function_type (scalar_t__,scalar_t__) ; 
 scalar_t__ build_method_type_directly (scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ cp_build_qualified_type_real (scalar_t__,int /*<<< orphan*/ ,int) ; 
 scalar_t__ cp_build_type_attribute_variant (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  error (char*,...) ; 
 scalar_t__ error_mark_node ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 int tf_error ; 
 scalar_t__ tsubst (scalar_t__,scalar_t__,int,scalar_t__) ; 
 scalar_t__ tsubst_arg_types (int /*<<< orphan*/ ,scalar_t__,int,scalar_t__) ; 

__attribute__((used)) static tree
tsubst_function_type (tree t,
		      tree args,
		      tsubst_flags_t complain,
		      tree in_decl)
{
  tree return_type;
  tree arg_types;
  tree fntype;

  /* The TYPE_CONTEXT is not used for function/method types.  */
  gcc_assert (TYPE_CONTEXT (t) == NULL_TREE);

  /* Substitute the return type.  */
  return_type = tsubst (TREE_TYPE (t), args, complain, in_decl);
  if (return_type == error_mark_node)
    return error_mark_node;
  /* The standard does not presently indicate that creation of a
     function type with an invalid return type is a deduction failure.
     However, that is clearly analogous to creating an array of "void"
     or a reference to a reference.  This is core issue #486.  */
  if (TREE_CODE (return_type) == ARRAY_TYPE
      || TREE_CODE (return_type) == FUNCTION_TYPE)
    {
      if (complain & tf_error)
	{
	  if (TREE_CODE (return_type) == ARRAY_TYPE)
	    error ("function returning an array");
	  else
	    error ("function returning a function");
	}
      return error_mark_node;
    }

  /* Substitute the argument types.  */
  arg_types = tsubst_arg_types (TYPE_ARG_TYPES (t), args,
				complain, in_decl);
  if (arg_types == error_mark_node)
    return error_mark_node;

  /* Construct a new type node and return it.  */
  if (TREE_CODE (t) == FUNCTION_TYPE)
    fntype = build_function_type (return_type, arg_types);
  else
    {
      tree r = TREE_TYPE (TREE_VALUE (arg_types));
      if (! IS_AGGR_TYPE (r))
	{
	  /* [temp.deduct]

	     Type deduction may fail for any of the following
	     reasons:

	     -- Attempting to create "pointer to member of T" when T
	     is not a class type.  */
	  if (complain & tf_error)
	    error ("creating pointer to member function of non-class type %qT",
		      r);
	  return error_mark_node;
	}

      fntype = build_method_type_directly (r, return_type,
					   TREE_CHAIN (arg_types));
    }
  fntype = cp_build_qualified_type_real (fntype, TYPE_QUALS (t), complain);
  fntype = cp_build_type_attribute_variant (fntype, TYPE_ATTRIBUTES (t));

  return fntype;
}