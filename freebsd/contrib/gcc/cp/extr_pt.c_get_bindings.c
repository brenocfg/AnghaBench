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
 scalar_t__ DECL_CONV_FN_P (scalar_t__) ; 
 int /*<<< orphan*/  DECL_INNERMOST_TEMPLATE_PARMS (scalar_t__) ; 
 int DECL_NTPARMS (scalar_t__) ; 
 scalar_t__ DECL_TEMPLATE_INFO (scalar_t__) ; 
 scalar_t__ DECL_TI_TEMPLATE (scalar_t__) ; 
 int /*<<< orphan*/  DEDUCE_EXACT ; 
 int /*<<< orphan*/  LOOKUP_NORMAL ; 
 scalar_t__ NULL_TREE ; 
 scalar_t__ TREE_TYPE (scalar_t__) ; 
 int /*<<< orphan*/  TYPE_ARG_TYPES (scalar_t__) ; 
 scalar_t__ coerce_template_parms (int /*<<< orphan*/ ,scalar_t__,scalar_t__,int /*<<< orphan*/ ,int,int) ; 
 scalar_t__ error_mark_node ; 
 scalar_t__ fn_type_unification (scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ make_tree_vec (int) ; 
 scalar_t__ skip_artificial_parms_for (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tf_none ; 
 scalar_t__ tsubst (scalar_t__,scalar_t__,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ uses_template_parms (scalar_t__) ; 

__attribute__((used)) static tree
get_bindings (tree fn, tree decl, tree explicit_args, bool check_rettype)
{
  int ntparms = DECL_NTPARMS (fn);
  tree targs = make_tree_vec (ntparms);
  tree decl_type;
  tree decl_arg_types;

  /* Substitute the explicit template arguments into the type of DECL.
     The call to fn_type_unification will handle substitution into the
     FN.  */
  decl_type = TREE_TYPE (decl);
  if (explicit_args && uses_template_parms (decl_type))
    {
      tree tmpl;
      tree converted_args;

      if (DECL_TEMPLATE_INFO (decl))
	tmpl = DECL_TI_TEMPLATE (decl);
      else
	/* We can get here for some invalid specializations.  */
	return NULL_TREE;

      converted_args
	= coerce_template_parms (DECL_INNERMOST_TEMPLATE_PARMS (tmpl),
				 explicit_args, NULL_TREE,
				 tf_none,
				 /*require_all_args=*/false,
				 /*use_default_args=*/false);
      if (converted_args == error_mark_node)
	return NULL_TREE;

      decl_type = tsubst (decl_type, converted_args, tf_none, NULL_TREE);
      if (decl_type == error_mark_node)
	return NULL_TREE;
    }

  /* Never do unification on the 'this' parameter.  */
  decl_arg_types = skip_artificial_parms_for (decl, 
					      TYPE_ARG_TYPES (decl_type));

  if (fn_type_unification (fn, explicit_args, targs,
			   decl_arg_types,
			   (check_rettype || DECL_CONV_FN_P (fn)
			    ? TREE_TYPE (decl_type) : NULL_TREE),
			   DEDUCE_EXACT, LOOKUP_NORMAL))
    return NULL_TREE;

  return targs;
}