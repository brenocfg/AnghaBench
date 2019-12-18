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
 int /*<<< orphan*/  ADDR_EXPR ; 
 scalar_t__ BASELINK_FUNCTIONS (scalar_t__) ; 
 scalar_t__ CLASS_TYPE_P (scalar_t__) ; 
 int /*<<< orphan*/  CLEANUP_POINT_EXPR ; 
 int /*<<< orphan*/  COMPOUND_EXPR ; 
 int /*<<< orphan*/  INIT_EXPR ; 
 int LOOKUP_NORMAL ; 
 int LOOKUP_ONLYCONVERTING ; 
 int /*<<< orphan*/  MUST_NOT_THROW_EXPR ; 
 scalar_t__ NULL_TREE ; 
 scalar_t__ OVL_CURRENT (scalar_t__) ; 
 scalar_t__ TARGET_EXPR ; 
 scalar_t__ TARGET_EXPR_SLOT (scalar_t__) ; 
 int /*<<< orphan*/  THROW_EXPR ; 
 scalar_t__ TREE_CODE (scalar_t__) ; 
 scalar_t__ TREE_TYPE (scalar_t__) ; 
 int /*<<< orphan*/  TRY_CATCH_EXPR ; 
 int /*<<< orphan*/  TYPE_BINFO (scalar_t__) ; 
 scalar_t__ TYPE_HAS_NONTRIVIAL_DESTRUCTOR (scalar_t__) ; 
 int /*<<< orphan*/  TYPE_MAIN_VARIANT (scalar_t__) ; 
 scalar_t__ build1 (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 scalar_t__ build2 (int /*<<< orphan*/ ,scalar_t__,scalar_t__,scalar_t__) ; 
 scalar_t__ build_eh_type_type (int /*<<< orphan*/ ) ; 
 scalar_t__ build_function_call (scalar_t__,scalar_t__) ; 
 scalar_t__ build_function_type (scalar_t__,scalar_t__) ; 
 scalar_t__ build_indirect_ref (scalar_t__,int /*<<< orphan*/ *) ; 
 scalar_t__ build_int_cst (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ build_min (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 scalar_t__ build_nop (scalar_t__,scalar_t__) ; 
 scalar_t__ build_pointer_type (scalar_t__) ; 
 scalar_t__ build_special_member_call (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int) ; 
 int /*<<< orphan*/  build_tree_list (scalar_t__,scalar_t__) ; 
 scalar_t__ cfun ; 
 scalar_t__ cleanup_type ; 
 int /*<<< orphan*/  complete_ctor_identifier ; 
 int /*<<< orphan*/  complete_dtor_identifier ; 
 int current_function_returns_abnormally ; 
 int /*<<< orphan*/  cxx_mark_addressable (scalar_t__) ; 
 scalar_t__ decay_conversion (scalar_t__) ; 
 scalar_t__ decl_is_java_type (scalar_t__,int) ; 
 scalar_t__ do_allocate_exception (scalar_t__) ; 
 scalar_t__ do_free_exception (scalar_t__) ; 
 int /*<<< orphan*/  doing_eh (int) ; 
 int /*<<< orphan*/  error (char*,...) ; 
 scalar_t__ error_mark_node ; 
 int /*<<< orphan*/  get_global_value_if_present (scalar_t__,scalar_t__*) ; 
 scalar_t__ get_identifier (char*) ; 
 scalar_t__ get_target_expr (scalar_t__) ; 
 int /*<<< orphan*/  is_admissible_throw_operand (scalar_t__) ; 
 scalar_t__ is_bitfield_expr_with_lowered_type (scalar_t__) ; 
 scalar_t__ lookup_fnfields (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mark_used (scalar_t__) ; 
 scalar_t__ null_node ; 
 int /*<<< orphan*/  prepare_eh_type (scalar_t__) ; 
 scalar_t__ processing_template_decl ; 
 scalar_t__ ptr_type_node ; 
 scalar_t__ push_throw_library_fn (scalar_t__,scalar_t__) ; 
 scalar_t__ really_overloaded_fn (scalar_t__) ; 
 int /*<<< orphan*/  stabilize_init (scalar_t__,scalar_t__*) ; 
 scalar_t__ tree_cons (scalar_t__,scalar_t__,scalar_t__) ; 
 scalar_t__ type_decays_to (int /*<<< orphan*/ ) ; 
 scalar_t__ void_list_node ; 
 scalar_t__ void_type_node ; 
 int /*<<< orphan*/  walk_tree_without_duplicates (scalar_t__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  warning (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  wrap_cleanups_r ; 

tree
build_throw (tree exp)
{
  tree fn;

  if (exp == error_mark_node)
    return exp;

  if (processing_template_decl)
    {
      if (cfun)
	current_function_returns_abnormally = 1;
      return build_min (THROW_EXPR, void_type_node, exp);
    }

  if (exp == null_node)
    warning (0, "throwing NULL, which has integral, not pointer type");

  if (exp != NULL_TREE)
    {
      if (!is_admissible_throw_operand (exp))
	return error_mark_node;
    }

  if (! doing_eh (1))
    return error_mark_node;

  if (exp && decl_is_java_type (TREE_TYPE (exp), 1))
    {
      tree fn = get_identifier ("_Jv_Throw");
      if (!get_global_value_if_present (fn, &fn))
	{
	  /* Declare void _Jv_Throw (void *).  */
	  tree tmp = tree_cons (NULL_TREE, ptr_type_node, void_list_node);
	  tmp = build_function_type (ptr_type_node, tmp);
	  fn = push_throw_library_fn (fn, tmp);
	}
      else if (really_overloaded_fn (fn))
	{
	  error ("%qD should never be overloaded", fn);
	  return error_mark_node;
	}
      fn = OVL_CURRENT (fn);
      exp = build_function_call (fn, tree_cons (NULL_TREE, exp, NULL_TREE));
    }
  else if (exp)
    {
      tree throw_type;
      tree temp_type;
      tree cleanup;
      tree object, ptr;
      tree tmp;
      tree temp_expr, allocate_expr;
      bool elided;

      /* The CLEANUP_TYPE is the internal type of a destructor.  */
      if (!cleanup_type)
	{
	  tmp = void_list_node;
	  tmp = tree_cons (NULL_TREE, ptr_type_node, tmp);
	  tmp = build_function_type (void_type_node, tmp);
	  cleanup_type = build_pointer_type (tmp);
	}

      fn = get_identifier ("__cxa_throw");
      if (!get_global_value_if_present (fn, &fn))
	{
	  /* Declare void __cxa_throw (void*, void*, void (*)(void*)).  */
	  /* ??? Second argument is supposed to be "std::type_info*".  */
	  tmp = void_list_node;
	  tmp = tree_cons (NULL_TREE, cleanup_type, tmp);
	  tmp = tree_cons (NULL_TREE, ptr_type_node, tmp);
	  tmp = tree_cons (NULL_TREE, ptr_type_node, tmp);
	  tmp = build_function_type (void_type_node, tmp);
	  fn = push_throw_library_fn (fn, tmp);
	}

      /* [except.throw]

	 A throw-expression initializes a temporary object, the type
	 of which is determined by removing any top-level
	 cv-qualifiers from the static type of the operand of throw
	 and adjusting the type from "array of T" or "function return
	 T" to "pointer to T" or "pointer to function returning T"
	 respectively.  */
      temp_type = is_bitfield_expr_with_lowered_type (exp);
      if (!temp_type)
	temp_type = type_decays_to (TYPE_MAIN_VARIANT (TREE_TYPE (exp)));

      /* OK, this is kind of wacky.  The standard says that we call
	 terminate when the exception handling mechanism, after
	 completing evaluation of the expression to be thrown but
	 before the exception is caught (_except.throw_), calls a
	 user function that exits via an uncaught exception.

	 So we have to protect the actual initialization of the
	 exception object with terminate(), but evaluate the
	 expression first.  Since there could be temps in the
	 expression, we need to handle that, too.  We also expand
	 the call to __cxa_allocate_exception first (which doesn't
	 matter, since it can't throw).  */

      /* Allocate the space for the exception.  */
      allocate_expr = do_allocate_exception (temp_type);
      allocate_expr = get_target_expr (allocate_expr);
      ptr = TARGET_EXPR_SLOT (allocate_expr);
      object = build_nop (build_pointer_type (temp_type), ptr);
      object = build_indirect_ref (object, NULL);

      elided = (TREE_CODE (exp) == TARGET_EXPR);

      /* And initialize the exception object.  */
      if (CLASS_TYPE_P (temp_type))
	{
	  /* Call the copy constructor.  */
	  exp = (build_special_member_call
		 (object, complete_ctor_identifier,
		  build_tree_list (NULL_TREE, exp),
		  TREE_TYPE (object),
		  LOOKUP_NORMAL | LOOKUP_ONLYCONVERTING));
	  if (exp == error_mark_node)
	    {
	      error ("  in thrown expression");
	      return error_mark_node;
	    }
	}
      else
	exp = build2 (INIT_EXPR, temp_type, object,
		      decay_conversion (exp));

      /* Pre-evaluate the thrown expression first, since if we allocated
	 the space first we would have to deal with cleaning it up if
	 evaluating this expression throws.

	 The case where EXP the initializer is a cast or a function
	 returning a class is a bit of a grey area in the standard; it's
	 unclear whether or not it should be allowed to throw.  We used to
	 say no, as that allowed us to optimize this case without worrying
	 about deallocating the exception object if it does.  But that
	 conflicted with expectations (PR 13944) and the EDG compiler; now
	 we wrap the initialization in a TRY_CATCH_EXPR to call
	 do_free_exception rather than in a MUST_NOT_THROW_EXPR, for this
	 case only.

	 BUT: Issue 475 may do away with this inconsistency by removing the
	 terminate() in this situation.

	 Note that we don't check the return value from stabilize_init
	 because it will only return false in cases where elided is true,
	 and therefore we don't need to work around the failure to
	 preevaluate.  */
      temp_expr = NULL_TREE;
      stabilize_init (exp, &temp_expr);

      /* Wrap the initialization in a CLEANUP_POINT_EXPR so that cleanups
	 for temporaries within the initialization are run before the one
	 for the exception object, preserving LIFO order.  */
      exp = build1 (CLEANUP_POINT_EXPR, void_type_node, exp);

      if (elided)
	exp = build2 (TRY_CATCH_EXPR, void_type_node, exp,
		      do_free_exception (ptr));
      else
	exp = build1 (MUST_NOT_THROW_EXPR, void_type_node, exp);

      /* Prepend the allocation.  */
      exp = build2 (COMPOUND_EXPR, TREE_TYPE (exp), allocate_expr, exp);
      if (temp_expr)
	{
	  /* Prepend the calculation of the throw expression.  Also, force
	     any cleanups from the expression to be evaluated here so that
	     we don't have to do them during unwinding.  But first wrap
	     them in MUST_NOT_THROW_EXPR, since they are run after the
	     exception object is initialized.  */
	  walk_tree_without_duplicates (&temp_expr, wrap_cleanups_r, 0);
	  exp = build2 (COMPOUND_EXPR, TREE_TYPE (exp), temp_expr, exp);
	  exp = build1 (CLEANUP_POINT_EXPR, TREE_TYPE (exp), exp);
	}

      throw_type = build_eh_type_type (prepare_eh_type (TREE_TYPE (object)));

      if (TYPE_HAS_NONTRIVIAL_DESTRUCTOR (TREE_TYPE (object)))
	{
	  cleanup = lookup_fnfields (TYPE_BINFO (TREE_TYPE (object)),
				     complete_dtor_identifier, 0);
	  cleanup = BASELINK_FUNCTIONS (cleanup);
	  mark_used (cleanup);
	  cxx_mark_addressable (cleanup);
	  /* Pretend it's a normal function.  */
	  cleanup = build1 (ADDR_EXPR, cleanup_type, cleanup);
	}
      else
	cleanup = build_int_cst (cleanup_type, 0);

      tmp = tree_cons (NULL_TREE, cleanup, NULL_TREE);
      tmp = tree_cons (NULL_TREE, throw_type, tmp);
      tmp = tree_cons (NULL_TREE, ptr, tmp);
      /* ??? Indicate that this function call throws throw_type.  */
      tmp = build_function_call (fn, tmp);

      /* Tack on the initialization stuff.  */
      exp = build2 (COMPOUND_EXPR, TREE_TYPE (tmp), exp, tmp);
    }
  else
    {
      /* Rethrow current exception.  */

      tree fn = get_identifier ("__cxa_rethrow");
      if (!get_global_value_if_present (fn, &fn))
	{
	  /* Declare void __cxa_rethrow (void).  */
	  fn = push_throw_library_fn
	    (fn, build_function_type (void_type_node, void_list_node));
	}

      /* ??? Indicate that this function call allows exceptions of the type
	 of the enclosing catch block (if known).  */
      exp = build_function_call (fn, NULL_TREE);
    }

  exp = build1 (THROW_EXPR, void_type_node, exp);

  return exp;
}