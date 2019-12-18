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
typedef  enum tree_code_class { ____Placeholder_tree_code_class } tree_code_class ;
typedef  enum tree_code { ____Placeholder_tree_code } tree_code ;

/* Variables and functions */
 scalar_t__ ADDR_EXPR ; 
 int const AGGR_INIT_EXPR ; 
 int /*<<< orphan*/  AGGR_INIT_VIA_CTOR_P (scalar_t__) ; 
#define  CALL_EXPR 135 
 int COMPLETE_TYPE_P (int /*<<< orphan*/ ) ; 
 int const COMPONENT_REF ; 
#define  COMPOUND_EXPR 134 
#define  COND_EXPR 133 
 int /*<<< orphan*/  CONVERT_EXPR ; 
#define  INDIRECT_REF 132 
 int INIT_EXPR ; 
 int MODIFY_EXPR ; 
#define  NON_LVALUE_EXPR 131 
#define  NOP_EXPR 130 
 scalar_t__ NULL_TREE ; 
 int /*<<< orphan*/  OPT_Waddress ; 
 int /*<<< orphan*/  OPT_Wunused_value ; 
 int POSTDECREMENT_EXPR ; 
 int POSTINCREMENT_EXPR ; 
 int PREDECREMENT_EXPR ; 
 int PREINCREMENT_EXPR ; 
 int const PSEUDO_DTOR_EXPR ; 
 int const REFERENCE_TYPE ; 
#define  TARGET_EXPR 129 
 int /*<<< orphan*/  TARGET_EXPR_IMPLICIT_P (scalar_t__) ; 
 scalar_t__ TARGET_EXPR_INITIAL (scalar_t__) ; 
 int /*<<< orphan*/  TREE_ADDRESSABLE (scalar_t__) ; 
 int const TREE_CODE (scalar_t__) ; 
 int TREE_CODE_CLASS (int) ; 
 int /*<<< orphan*/  TREE_NO_WARNING (scalar_t__) ; 
 scalar_t__ TREE_OPERAND (scalar_t__,int) ; 
 int /*<<< orphan*/  TREE_SIDE_EFFECTS (scalar_t__) ; 
 scalar_t__ TREE_TYPE (scalar_t__) ; 
 int /*<<< orphan*/  TYPE_HAS_TRIVIAL_DESTRUCTOR (scalar_t__) ; 
 int TYPE_VOLATILE (scalar_t__) ; 
#define  VAR_DECL 128 
 scalar_t__ VOID_TYPE_P (scalar_t__) ; 
 scalar_t__ build1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ build2 (int const,scalar_t__,scalar_t__,scalar_t__) ; 
 scalar_t__ build3 (int const,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  complete_type (scalar_t__) ; 
 int /*<<< orphan*/  error (char*) ; 
 scalar_t__ error_mark_node ; 
 scalar_t__ invalid_nonstatic_memfn_p (scalar_t__) ; 
 scalar_t__ is_overloaded_fn (scalar_t__) ; 
 int /*<<< orphan*/  pedwarn (char*,char const*) ; 
 int /*<<< orphan*/  processing_template_decl ; 
 int tcc_binary ; 
 int tcc_comparison ; 
 int tcc_unary ; 
 scalar_t__ type_unknown_p (scalar_t__) ; 
 int /*<<< orphan*/  void_type_node ; 
 scalar_t__ void_zero_node ; 
 scalar_t__ warn_unused_value ; 
 int /*<<< orphan*/  warning (int /*<<< orphan*/ ,char*,...) ; 

tree
convert_to_void (tree expr, const char *implicit)
{
  if (expr == error_mark_node
      || TREE_TYPE (expr) == error_mark_node)
    return error_mark_node;
  if (!TREE_TYPE (expr))
    return expr;
  if (invalid_nonstatic_memfn_p (expr))
    return error_mark_node;
  if (TREE_CODE (expr) == PSEUDO_DTOR_EXPR)
    {
      error ("pseudo-destructor is not called");
      return error_mark_node;
    }
  if (VOID_TYPE_P (TREE_TYPE (expr)))
    return expr;
  switch (TREE_CODE (expr))
    {
    case COND_EXPR:
      {
	/* The two parts of a cond expr might be separate lvalues.  */
	tree op1 = TREE_OPERAND (expr,1);
	tree op2 = TREE_OPERAND (expr,2);
	tree new_op1 = convert_to_void
	  (op1, (implicit && !TREE_SIDE_EFFECTS (op2)
		 ? "second operand of conditional" : NULL));
	tree new_op2 = convert_to_void
	  (op2, (implicit && !TREE_SIDE_EFFECTS (op1)
		 ? "third operand of conditional" : NULL));

	expr = build3 (COND_EXPR, TREE_TYPE (new_op1),
		       TREE_OPERAND (expr, 0), new_op1, new_op2);
	break;
      }

    case COMPOUND_EXPR:
      {
	/* The second part of a compound expr contains the value.  */
	tree op1 = TREE_OPERAND (expr,1);
	tree new_op1 = convert_to_void
	  (op1, (implicit && !TREE_NO_WARNING (expr)
		 ? "right-hand operand of comma" : NULL));

	if (new_op1 != op1)
	  {
	    tree t = build2 (COMPOUND_EXPR, TREE_TYPE (new_op1),
			     TREE_OPERAND (expr, 0), new_op1);
	    expr = t;
	  }

	break;
      }

    case NON_LVALUE_EXPR:
    case NOP_EXPR:
      /* These have already decayed to rvalue.  */
      break;

    case CALL_EXPR:   /* We have a special meaning for volatile void fn().  */
      break;

    case INDIRECT_REF:
      {
	tree type = TREE_TYPE (expr);
	int is_reference = TREE_CODE (TREE_TYPE (TREE_OPERAND (expr, 0)))
			   == REFERENCE_TYPE;
	int is_volatile = TYPE_VOLATILE (type);
	int is_complete = COMPLETE_TYPE_P (complete_type (type));

	/* Can't load the value if we don't know the type.  */
	if (is_volatile && !is_complete)
	  warning (0, "object of incomplete type %qT will not be accessed in %s",
		   type, implicit ? implicit : "void context");
	/* Don't load the value if this is an implicit dereference, or if
	   the type needs to be handled by ctors/dtors.  */
	else if (is_volatile && (is_reference || TREE_ADDRESSABLE (type)))
	  warning (0, "object of type %qT will not be accessed in %s",
		   TREE_TYPE (TREE_OPERAND (expr, 0)),
		   implicit ? implicit : "void context");
	if (is_reference || !is_volatile || !is_complete || TREE_ADDRESSABLE (type))
	  expr = TREE_OPERAND (expr, 0);

	break;
      }

    case VAR_DECL:
      {
	/* External variables might be incomplete.  */
	tree type = TREE_TYPE (expr);
	int is_complete = COMPLETE_TYPE_P (complete_type (type));

	if (TYPE_VOLATILE (type) && !is_complete)
	  warning (0, "object %qE of incomplete type %qT will not be accessed in %s",
		   expr, type, implicit ? implicit : "void context");
	break;
      }

    case TARGET_EXPR:
      /* Don't bother with the temporary object returned from a function if
	 we don't use it and don't need to destroy it.  We'll still
	 allocate space for it in expand_call or declare_return_variable,
	 but we don't need to track it through all the tree phases.  */
      if (TARGET_EXPR_IMPLICIT_P (expr)
	  && TYPE_HAS_TRIVIAL_DESTRUCTOR (TREE_TYPE (expr)))
	{
	  tree init = TARGET_EXPR_INITIAL (expr);
	  if (TREE_CODE (init) == AGGR_INIT_EXPR
	      && !AGGR_INIT_VIA_CTOR_P (init))
	    {
	      tree fn = TREE_OPERAND (init, 0);
	      expr = build3 (CALL_EXPR, TREE_TYPE (TREE_TYPE (TREE_TYPE (fn))),
			     fn, TREE_OPERAND (init, 1), NULL_TREE);
	    }
	}
      break;

    default:;
    }
  {
    tree probe = expr;

    if (TREE_CODE (probe) == ADDR_EXPR)
      probe = TREE_OPERAND (expr, 0);
    if (type_unknown_p (probe))
      {
	/* [over.over] enumerates the places where we can take the address
	   of an overloaded function, and this is not one of them.  */
	pedwarn ("%s cannot resolve address of overloaded function",
		    implicit ? implicit : "void cast");
	expr = void_zero_node;
      }
    else if (implicit && probe == expr && is_overloaded_fn (probe))
      {
	/* Only warn when there is no &.  */
	warning (OPT_Waddress, "%s is a reference, not call, to function %qE",
		 implicit, expr);
	if (TREE_CODE (expr) == COMPONENT_REF)
	  expr = TREE_OPERAND (expr, 0);
      }
  }

  if (expr != error_mark_node && !VOID_TYPE_P (TREE_TYPE (expr)))
    {
      if (implicit
	  && warn_unused_value
	  && !TREE_NO_WARNING (expr)
	  && !processing_template_decl)
	{
	  /* The middle end does not warn about expressions that have
	     been explicitly cast to void, so we must do so here.  */
	  if (!TREE_SIDE_EFFECTS (expr))
	    warning (OPT_Wunused_value, "%s has no effect", implicit);
	  else
	    {
	      tree e;
	      enum tree_code code;
	      enum tree_code_class class;

	      e = expr;
	      /* We might like to warn about (say) "(int) f()", as the
		 cast has no effect, but the compiler itself will
		 generate implicit conversions under some
		 circumstances.  (For example a block copy will be
		 turned into a call to "__builtin_memcpy", with a
		 conversion of the return value to an appropriate
		 type.)  So, to avoid false positives, we strip
		 conversions.  Do not use STRIP_NOPs because it will
		 not strip conversions to "void", as that is not a
		 mode-preserving conversion.  */
	      while (TREE_CODE (e) == NOP_EXPR)
		e = TREE_OPERAND (e, 0);

	      code = TREE_CODE (e);
	      class = TREE_CODE_CLASS (code);
	      if (class == tcc_comparison
		   || class == tcc_unary
		   || (class == tcc_binary
		       && !(code == MODIFY_EXPR
			    || code == INIT_EXPR
			    || code == PREDECREMENT_EXPR
			    || code == PREINCREMENT_EXPR
			    || code == POSTDECREMENT_EXPR
			    || code == POSTINCREMENT_EXPR)))
		warning (OPT_Wunused_value, "value computed is not used");
	    }
	}
      expr = build1 (CONVERT_EXPR, void_type_node, expr);
    }
  if (! TREE_SIDE_EFFECTS (expr))
    expr = void_zero_node;
  return expr;
}