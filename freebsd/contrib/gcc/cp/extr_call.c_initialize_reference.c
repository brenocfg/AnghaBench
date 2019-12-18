#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ tree ;
struct TYPE_6__ {TYPE_2__* next; } ;
struct TYPE_7__ {scalar_t__ kind; scalar_t__ type; TYPE_1__ u; scalar_t__ check_copy_constructor_p; scalar_t__ bad_p; } ;
typedef  TYPE_2__ conversion ;

/* Variables and functions */
 int /*<<< orphan*/  ADDR_EXPR ; 
 int /*<<< orphan*/  COMPOUND_EXPR ; 
 int /*<<< orphan*/  INIT_EXPR ; 
 int /*<<< orphan*/  LOOKUP_NORMAL ; 
 scalar_t__ NULL_TREE ; 
 scalar_t__ TARGET_EXPR ; 
 scalar_t__ TREE_CODE (scalar_t__) ; 
 scalar_t__ TREE_TYPE (scalar_t__) ; 
 scalar_t__ TYPE_HAS_NONTRIVIAL_DESTRUCTOR (scalar_t__) ; 
 int TYPE_QUALS (scalar_t__) ; 
 int TYPE_QUAL_CONST ; 
 int /*<<< orphan*/  add_decl_expr (scalar_t__) ; 
 int /*<<< orphan*/  at_eof ; 
 scalar_t__ at_function_scope_p () ; 
 scalar_t__ build2 (int /*<<< orphan*/ ,scalar_t__,scalar_t__,scalar_t__) ; 
 scalar_t__ build_address (scalar_t__) ; 
 scalar_t__ build_nop (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  build_pointer_type (scalar_t__) ; 
 scalar_t__ build_unary_op (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  check_constructor_callable (scalar_t__,scalar_t__) ; 
 scalar_t__ ck_base ; 
 scalar_t__ ck_ref_bind ; 
 int /*<<< orphan*/  conversion_obstack ; 
 void* conversion_obstack_alloc (int /*<<< orphan*/ ) ; 
 scalar_t__ convert_like (TYPE_2__*,scalar_t__) ; 
 scalar_t__ convert_like_real (TYPE_2__*,scalar_t__,scalar_t__,int /*<<< orphan*/ ,int,int,int) ; 
 scalar_t__ convert_to_base (scalar_t__,int /*<<< orphan*/ ,int,int) ; 
 scalar_t__ cxx_maybe_build_cleanup (scalar_t__) ; 
 int /*<<< orphan*/  error (char*,scalar_t__,scalar_t__) ; 
 scalar_t__ error_mark_node ; 
 scalar_t__ error_operand_p (scalar_t__) ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 scalar_t__ get_target_expr (scalar_t__) ; 
 int /*<<< orphan*/  layout_decl (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ make_temporary_var_for_ref_to_temp (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  obstack_free (int /*<<< orphan*/ *,void*) ; 
 scalar_t__ perform_implicit_conversion (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  real_lvalue_p (scalar_t__) ; 
 TYPE_2__* reference_binding (scalar_t__,scalar_t__,scalar_t__,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rest_of_decl_compilation (scalar_t__,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  static_aggregates ; 
 int /*<<< orphan*/  tree_cons (scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 

tree
initialize_reference (tree type, tree expr, tree decl, tree *cleanup)
{
  conversion *conv;
  void *p;

  if (type == error_mark_node || error_operand_p (expr))
    return error_mark_node;

  /* Get the high-water mark for the CONVERSION_OBSTACK.  */
  p = conversion_obstack_alloc (0);

  conv = reference_binding (type, TREE_TYPE (expr), expr, /*c_cast_p=*/false,
			    LOOKUP_NORMAL);
  if (!conv || conv->bad_p)
    {
      if (!(TYPE_QUALS (TREE_TYPE (type)) & TYPE_QUAL_CONST)
	  && !real_lvalue_p (expr))
	error ("invalid initialization of non-const reference of "
	       "type %qT from a temporary of type %qT",
	       type, TREE_TYPE (expr));
      else
	error ("invalid initialization of reference of type "
	       "%qT from expression of type %qT", type,
	       TREE_TYPE (expr));
      return error_mark_node;
    }

  /* If DECL is non-NULL, then this special rule applies:

       [class.temporary]

       The temporary to which the reference is bound or the temporary
       that is the complete object to which the reference is bound
       persists for the lifetime of the reference.

       The temporaries created during the evaluation of the expression
       initializing the reference, except the temporary to which the
       reference is bound, are destroyed at the end of the
       full-expression in which they are created.

     In that case, we store the converted expression into a new
     VAR_DECL in a new scope.

     However, we want to be careful not to create temporaries when
     they are not required.  For example, given:

       struct B {};
       struct D : public B {};
       D f();
       const B& b = f();

     there is no need to copy the return value from "f"; we can just
     extend its lifetime.  Similarly, given:

       struct S {};
       struct T { operator S(); };
       T t;
       const S& s = t;

    we can extend the lifetime of the return value of the conversion
    operator.  */
  gcc_assert (conv->kind == ck_ref_bind);
  if (decl)
    {
      tree var;
      tree base_conv_type;

      /* Skip over the REF_BIND.  */
      conv = conv->u.next;
      /* If the next conversion is a BASE_CONV, skip that too -- but
	 remember that the conversion was required.  */
      if (conv->kind == ck_base)
	{
	  if (conv->check_copy_constructor_p)
	    check_constructor_callable (TREE_TYPE (expr), expr);
	  base_conv_type = conv->type;
	  conv = conv->u.next;
	}
      else
	base_conv_type = NULL_TREE;
      /* Perform the remainder of the conversion.  */
      expr = convert_like_real (conv, expr,
				/*fn=*/NULL_TREE, /*argnum=*/0,
				/*inner=*/-1,
				/*issue_conversion_warnings=*/true,
				/*c_cast_p=*/false);
      if (error_operand_p (expr))
	expr = error_mark_node;
      else
	{
	  if (!real_lvalue_p (expr))
	    {
	      tree init;
	      tree type;

	      /* Create the temporary variable.  */
	      type = TREE_TYPE (expr);
	      var = make_temporary_var_for_ref_to_temp (decl, type);
	      layout_decl (var, 0);
	      /* If the rvalue is the result of a function call it will be
		 a TARGET_EXPR.  If it is some other construct (such as a
		 member access expression where the underlying object is
		 itself the result of a function call), turn it into a
		 TARGET_EXPR here.  It is important that EXPR be a
		 TARGET_EXPR below since otherwise the INIT_EXPR will
		 attempt to make a bitwise copy of EXPR to initialize
		 VAR.  */
	      if (TREE_CODE (expr) != TARGET_EXPR)
		expr = get_target_expr (expr);
	      /* Create the INIT_EXPR that will initialize the temporary
		 variable.  */
	      init = build2 (INIT_EXPR, type, var, expr);
	      if (at_function_scope_p ())
		{
		  add_decl_expr (var);
		  *cleanup = cxx_maybe_build_cleanup (var);

		  /* We must be careful to destroy the temporary only
		     after its initialization has taken place.  If the
		     initialization throws an exception, then the
		     destructor should not be run.  We cannot simply
		     transform INIT into something like:

			 (INIT, ({ CLEANUP_STMT; }))

		     because emit_local_var always treats the
		     initializer as a full-expression.  Thus, the
		     destructor would run too early; it would run at the
		     end of initializing the reference variable, rather
		     than at the end of the block enclosing the
		     reference variable.

		     The solution is to pass back a cleanup expression
		     which the caller is responsible for attaching to
		     the statement tree.  */
		}
	      else
		{
		  rest_of_decl_compilation (var, /*toplev=*/1, at_eof);
		  if (TYPE_HAS_NONTRIVIAL_DESTRUCTOR (type))
		    static_aggregates = tree_cons (NULL_TREE, var,
						   static_aggregates);
		}
	      /* Use its address to initialize the reference variable.  */
	      expr = build_address (var);
	      if (base_conv_type)
		expr = convert_to_base (expr,
					build_pointer_type (base_conv_type),
					/*check_access=*/true,
					/*nonnull=*/true);
	      expr = build2 (COMPOUND_EXPR, TREE_TYPE (expr), init, expr);
	    }
	  else
	    /* Take the address of EXPR.  */
	    expr = build_unary_op (ADDR_EXPR, expr, 0);
	  /* If a BASE_CONV was required, perform it now.  */
	  if (base_conv_type)
	    expr = (perform_implicit_conversion
		    (build_pointer_type (base_conv_type), expr));
	  expr = build_nop (type, expr);
	}
    }
  else
    /* Perform the conversion.  */
    expr = convert_like (conv, expr);

  /* Free all the conversions we allocated.  */
  obstack_free (&conversion_obstack, p);

  return expr;
}