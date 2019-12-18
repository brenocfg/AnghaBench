#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ tree ;
struct z_candidate {scalar_t__ fn; TYPE_2__** convs; struct candidate_warning* warnings; } ;
struct candidate_warning {int /*<<< orphan*/  loser; struct candidate_warning* next; } ;
typedef  enum tree_code { ____Placeholder_tree_code } tree_code ;
struct TYPE_5__ {TYPE_2__* next; } ;
struct TYPE_6__ {scalar_t__ kind; TYPE_1__ u; } ;
typedef  TYPE_2__ conversion ;
struct TYPE_7__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
#define  ADDR_EXPR 170 
#define  ARRAY_REF 169 
 scalar_t__ BASELINK_BINFO (scalar_t__) ; 
 int /*<<< orphan*/  BASELINK_FUNCTIONS (scalar_t__) ; 
#define  BIT_AND_EXPR 168 
#define  BIT_IOR_EXPR 167 
#define  BIT_NOT_EXPR 166 
#define  BIT_XOR_EXPR 165 
#define  CALL_EXPR 164 
 scalar_t__ CLASS_TYPE_P (scalar_t__) ; 
#define  COMPONENT_REF 163 
#define  COMPOUND_EXPR 162 
#define  COND_EXPR 161 
#define  DELETE_EXPR 160 
 scalar_t__ ENUMERAL_TYPE ; 
#define  EQ_EXPR 159 
 scalar_t__ FUNCTION_DECL ; 
#define  GE_EXPR 158 
#define  GT_EXPR 157 
#define  IMAGPART_EXPR 156 
#define  INDIRECT_REF 155 
 int /*<<< orphan*/  IS_OVERLOAD_TYPE (scalar_t__) ; 
#define  LE_EXPR 154 
 int LOOKUP_COMPLAIN ; 
 int /*<<< orphan*/  LOOKUP_NORMAL ; 
#define  LSHIFT_EXPR 153 
#define  LT_EXPR 152 
#define  MAX_EXPR 151 
#define  MEMBER_REF 150 
#define  MINUS_EXPR 149 
#define  MIN_EXPR 148 
#define  MODIFY_EXPR 147 
#define  MULT_EXPR 146 
#define  NEGATE_EXPR 145 
#define  NEW_EXPR 144 
#define  NE_EXPR 143 
 int NOP_EXPR ; 
 scalar_t__ NULL_TREE ; 
#define  PLUS_EXPR 142 
#define  POSTDECREMENT_EXPR 141 
#define  POSTINCREMENT_EXPR 140 
#define  PREDECREMENT_EXPR 139 
#define  PREINCREMENT_EXPR 138 
#define  REALPART_EXPR 137 
#define  RSHIFT_EXPR 136 
 scalar_t__ TREE_CODE (scalar_t__) ; 
 scalar_t__ TREE_TYPE (scalar_t__) ; 
#define  TRUNC_DIV_EXPR 135 
#define  TRUNC_MOD_EXPR 134 
#define  TRUTH_ANDIF_EXPR 133 
#define  TRUTH_NOT_EXPR 132 
#define  TRUTH_ORIF_EXPR 131 
 scalar_t__ TYPE_BINFO (scalar_t__) ; 
 int /*<<< orphan*/  TYPE_MAIN_VARIANT (scalar_t__) ; 
#define  UNARY_PLUS_EXPR 130 
#define  VEC_DELETE_EXPR 129 
#define  VEC_NEW_EXPR 128 
 scalar_t__ VOID_TYPE ; 
 int /*<<< orphan*/  add_builtin_candidates (struct z_candidate**,int,int,scalar_t__,scalar_t__*,int) ; 
 int /*<<< orphan*/  add_candidates (int /*<<< orphan*/ ,scalar_t__,scalar_t__,int,scalar_t__,scalar_t__,int,struct z_candidate**) ; 
 scalar_t__ ansi_assopname (int) ; 
 scalar_t__ ansi_opname (int) ; 
 scalar_t__ build_array_ref (scalar_t__,scalar_t__) ; 
 scalar_t__ build_conditional_expr (scalar_t__,scalar_t__,scalar_t__) ; 
 scalar_t__ build_indirect_ref (scalar_t__,char*) ; 
 scalar_t__ build_m_component_ref (scalar_t__,scalar_t__) ; 
 scalar_t__ build_modify_expr (scalar_t__,int,scalar_t__) ; 
 scalar_t__ build_object_call (scalar_t__,scalar_t__) ; 
 scalar_t__ build_over_call (struct z_candidate*,int /*<<< orphan*/ ) ; 
 scalar_t__ build_unary_op (int,scalar_t__,int) ; 
 scalar_t__ ck_ref_bind ; 
 int /*<<< orphan*/  conversion_obstack ; 
 void* conversion_obstack_alloc (int /*<<< orphan*/ ) ; 
 scalar_t__ convert_like (TYPE_2__*,scalar_t__) ; 
 scalar_t__ cp_build_binary_op (int,scalar_t__,scalar_t__) ; 
 scalar_t__ error_mark_node ; 
 scalar_t__ error_operand_p (scalar_t__) ; 
 int /*<<< orphan*/  gcc_unreachable () ; 
 scalar_t__ integer_zero_node ; 
 int /*<<< orphan*/  joust (struct z_candidate*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ lookup_fnfields (scalar_t__,scalar_t__,int) ; 
 int /*<<< orphan*/  lookup_function_nonclass (scalar_t__,scalar_t__,int) ; 
 int /*<<< orphan*/  obstack_free (int /*<<< orphan*/ *,void*) ; 
 int /*<<< orphan*/  op_error (int,int,scalar_t__,scalar_t__,scalar_t__,char*) ; 
 TYPE_3__* operator_name_info ; 
 int pedantic ; 
 int /*<<< orphan*/  pedwarn (char*,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ prep_operand (scalar_t__) ; 
 int /*<<< orphan*/  print_z_candidates (struct z_candidate*) ; 
 struct z_candidate* splice_viable (struct z_candidate*,int,int*) ; 
 struct z_candidate* tourney (struct z_candidate*) ; 
 scalar_t__ tree_cons (scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  warning (int /*<<< orphan*/ ,char*,scalar_t__,scalar_t__) ; 

tree
build_new_op (enum tree_code code, int flags, tree arg1, tree arg2, tree arg3,
	      bool *overloaded_p)
{
  struct z_candidate *candidates = 0, *cand;
  tree arglist, fnname;
  tree args[3];
  tree result = NULL_TREE;
  bool result_valid_p = false;
  enum tree_code code2 = NOP_EXPR;
  conversion *conv;
  void *p;
  bool strict_p;
  bool any_viable_p;

  if (error_operand_p (arg1)
      || error_operand_p (arg2)
      || error_operand_p (arg3))
    return error_mark_node;

  if (code == MODIFY_EXPR)
    {
      code2 = TREE_CODE (arg3);
      arg3 = NULL_TREE;
      fnname = ansi_assopname (code2);
    }
  else
    fnname = ansi_opname (code);

  arg1 = prep_operand (arg1);

  switch (code)
    {
    case NEW_EXPR:
    case VEC_NEW_EXPR:
    case VEC_DELETE_EXPR:
    case DELETE_EXPR:
      /* Use build_op_new_call and build_op_delete_call instead.  */
      gcc_unreachable ();

    case CALL_EXPR:
      return build_object_call (arg1, arg2);

    default:
      break;
    }

  arg2 = prep_operand (arg2);
  arg3 = prep_operand (arg3);

  if (code == COND_EXPR)
    {
      if (arg2 == NULL_TREE
	  || TREE_CODE (TREE_TYPE (arg2)) == VOID_TYPE
	  || TREE_CODE (TREE_TYPE (arg3)) == VOID_TYPE
	  || (! IS_OVERLOAD_TYPE (TREE_TYPE (arg2))
	      && ! IS_OVERLOAD_TYPE (TREE_TYPE (arg3))))
	goto builtin;
    }
  else if (! IS_OVERLOAD_TYPE (TREE_TYPE (arg1))
	   && (! arg2 || ! IS_OVERLOAD_TYPE (TREE_TYPE (arg2))))
    goto builtin;

  if (code == POSTINCREMENT_EXPR || code == POSTDECREMENT_EXPR)
    arg2 = integer_zero_node;

  arglist = NULL_TREE;
  if (arg3)
    arglist = tree_cons (NULL_TREE, arg3, arglist);
  if (arg2)
    arglist = tree_cons (NULL_TREE, arg2, arglist);
  arglist = tree_cons (NULL_TREE, arg1, arglist);

  /* Get the high-water mark for the CONVERSION_OBSTACK.  */
  p = conversion_obstack_alloc (0);

  /* Add namespace-scope operators to the list of functions to
     consider.  */
  add_candidates (lookup_function_nonclass (fnname, arglist, /*block_p=*/true),
		  arglist, NULL_TREE, false, NULL_TREE, NULL_TREE,
		  flags, &candidates);
  /* Add class-member operators to the candidate set.  */
  if (CLASS_TYPE_P (TREE_TYPE (arg1)))
    {
      tree fns;

      fns = lookup_fnfields (TREE_TYPE (arg1), fnname, 1);
      if (fns == error_mark_node)
	{
	  result = error_mark_node;
	  goto user_defined_result_ready;
	}
      if (fns)
	add_candidates (BASELINK_FUNCTIONS (fns), arglist,
			NULL_TREE, false,
			BASELINK_BINFO (fns),
			TYPE_BINFO (TREE_TYPE (arg1)),
			flags, &candidates);
    }

  /* Rearrange the arguments for ?: so that add_builtin_candidate only has
     to know about two args; a builtin candidate will always have a first
     parameter of type bool.  We'll handle that in
     build_builtin_candidate.  */
  if (code == COND_EXPR)
    {
      args[0] = arg2;
      args[1] = arg3;
      args[2] = arg1;
    }
  else
    {
      args[0] = arg1;
      args[1] = arg2;
      args[2] = NULL_TREE;
    }

  add_builtin_candidates (&candidates, code, code2, fnname, args, flags);

  switch (code)
    {
    case COMPOUND_EXPR:
    case ADDR_EXPR:
      /* For these, the built-in candidates set is empty
	 [over.match.oper]/3.  We don't want non-strict matches
	 because exact matches are always possible with built-in
	 operators.  The built-in candidate set for COMPONENT_REF
	 would be empty too, but since there are no such built-in
	 operators, we accept non-strict matches for them.  */
      strict_p = true;
      break;

    default:
      strict_p = pedantic;
      break;
    }

  candidates = splice_viable (candidates, strict_p, &any_viable_p);
  if (!any_viable_p)
    {
      switch (code)
	{
	case POSTINCREMENT_EXPR:
	case POSTDECREMENT_EXPR:
	  /* Look for an `operator++ (int)'.  If they didn't have
	     one, then we fall back to the old way of doing things.  */
	  if (flags & LOOKUP_COMPLAIN)
	    pedwarn ("no %<%D(int)%> declared for postfix %qs, "
		     "trying prefix operator instead",
		     fnname,
		     operator_name_info[code].name);
	  if (code == POSTINCREMENT_EXPR)
	    code = PREINCREMENT_EXPR;
	  else
	    code = PREDECREMENT_EXPR;
	  result = build_new_op (code, flags, arg1, NULL_TREE, NULL_TREE,
				 overloaded_p);
	  break;

	  /* The caller will deal with these.  */
	case ADDR_EXPR:
	case COMPOUND_EXPR:
	case COMPONENT_REF:
	  result = NULL_TREE;
	  result_valid_p = true;
	  break;

	default:
	  if (flags & LOOKUP_COMPLAIN)
	    {
	      op_error (code, code2, arg1, arg2, arg3, "no match");
	      print_z_candidates (candidates);
	    }
	  result = error_mark_node;
	  break;
	}
    }
  else
    {
      cand = tourney (candidates);
      if (cand == 0)
	{
	  if (flags & LOOKUP_COMPLAIN)
	    {
	      op_error (code, code2, arg1, arg2, arg3, "ambiguous overload");
	      print_z_candidates (candidates);
	    }
	  result = error_mark_node;
	}
      else if (TREE_CODE (cand->fn) == FUNCTION_DECL)
	{
	  if (overloaded_p)
	    *overloaded_p = true;

	  result = build_over_call (cand, LOOKUP_NORMAL);
	}
      else
	{
	  /* Give any warnings we noticed during overload resolution.  */
	  if (cand->warnings)
	    {
	      struct candidate_warning *w;
	      for (w = cand->warnings; w; w = w->next)
		joust (cand, w->loser, 1);
	    }

	  /* Check for comparison of different enum types.  */
	  switch (code)
	    {
	    case GT_EXPR:
	    case LT_EXPR:
	    case GE_EXPR:
	    case LE_EXPR:
	    case EQ_EXPR:
	    case NE_EXPR:
	      if (TREE_CODE (TREE_TYPE (arg1)) == ENUMERAL_TYPE
		  && TREE_CODE (TREE_TYPE (arg2)) == ENUMERAL_TYPE
		  && (TYPE_MAIN_VARIANT (TREE_TYPE (arg1))
		      != TYPE_MAIN_VARIANT (TREE_TYPE (arg2))))
		{
		  warning (0, "comparison between %q#T and %q#T",
			   TREE_TYPE (arg1), TREE_TYPE (arg2));
		}
	      break;
	    default:
	      break;
	    }

	  /* We need to strip any leading REF_BIND so that bitfields
	     don't cause errors.  This should not remove any important
	     conversions, because builtins don't apply to class
	     objects directly.  */
	  conv = cand->convs[0];
	  if (conv->kind == ck_ref_bind)
	    conv = conv->u.next;
	  arg1 = convert_like (conv, arg1);
	  if (arg2)
	    {
	      conv = cand->convs[1];
	      if (conv->kind == ck_ref_bind)
		conv = conv->u.next;
	      arg2 = convert_like (conv, arg2);
	    }
	  if (arg3)
	    {
	      conv = cand->convs[2];
	      if (conv->kind == ck_ref_bind)
		conv = conv->u.next;
	      arg3 = convert_like (conv, arg3);
	    }
	}
    }

 user_defined_result_ready:

  /* Free all the conversions we allocated.  */
  obstack_free (&conversion_obstack, p);

  if (result || result_valid_p)
    return result;

 builtin:
  switch (code)
    {
    case MODIFY_EXPR:
      return build_modify_expr (arg1, code2, arg2);

    case INDIRECT_REF:
      return build_indirect_ref (arg1, "unary *");

    case PLUS_EXPR:
    case MINUS_EXPR:
    case MULT_EXPR:
    case TRUNC_DIV_EXPR:
    case GT_EXPR:
    case LT_EXPR:
    case GE_EXPR:
    case LE_EXPR:
    case EQ_EXPR:
    case NE_EXPR:
    case MAX_EXPR:
    case MIN_EXPR:
    case LSHIFT_EXPR:
    case RSHIFT_EXPR:
    case TRUNC_MOD_EXPR:
    case BIT_AND_EXPR:
    case BIT_IOR_EXPR:
    case BIT_XOR_EXPR:
    case TRUTH_ANDIF_EXPR:
    case TRUTH_ORIF_EXPR:
      return cp_build_binary_op (code, arg1, arg2);

    case UNARY_PLUS_EXPR:
    case NEGATE_EXPR:
    case BIT_NOT_EXPR:
    case TRUTH_NOT_EXPR:
    case PREINCREMENT_EXPR:
    case POSTINCREMENT_EXPR:
    case PREDECREMENT_EXPR:
    case POSTDECREMENT_EXPR:
    case REALPART_EXPR:
    case IMAGPART_EXPR:
      return build_unary_op (code, arg1, candidates != 0);

    case ARRAY_REF:
      return build_array_ref (arg1, arg2);

    case COND_EXPR:
      return build_conditional_expr (arg1, arg2, arg3);

    case MEMBER_REF:
      return build_m_component_ref (build_indirect_ref (arg1, NULL), arg2);

      /* The caller will deal with these.  */
    case ADDR_EXPR:
    case COMPONENT_REF:
    case COMPOUND_EXPR:
      return NULL_TREE;

    default:
      gcc_unreachable ();
    }
  return NULL_TREE;
}