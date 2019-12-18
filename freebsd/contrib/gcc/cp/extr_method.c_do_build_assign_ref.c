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
 scalar_t__ ANON_AGGR_TYPE_P (scalar_t__) ; 
 scalar_t__ BINFO_BASE_ITERATE (scalar_t__,int,scalar_t__) ; 
 int /*<<< orphan*/  COMPONENT_REF ; 
 scalar_t__ CP_TYPE_CONST_P (scalar_t__) ; 
 scalar_t__ DECL_ARGUMENTS (scalar_t__) ; 
 scalar_t__ DECL_ARTIFICIAL (scalar_t__) ; 
 scalar_t__ DECL_MUTABLE_P (scalar_t__) ; 
 scalar_t__ DECL_NAME (scalar_t__) ; 
 scalar_t__ FIELD_DECL ; 
 int LOOKUP_NONVIRTUAL ; 
 int LOOKUP_NORMAL ; 
 int /*<<< orphan*/  MODIFY_EXPR ; 
 int /*<<< orphan*/  NOP_EXPR ; 
 scalar_t__ NULL_TREE ; 
 int /*<<< orphan*/  PLUS_EXPR ; 
 scalar_t__ REFERENCE_TYPE ; 
 scalar_t__ TREE_CHAIN (scalar_t__) ; 
 scalar_t__ TREE_CODE (scalar_t__) ; 
 scalar_t__ TREE_TYPE (scalar_t__) ; 
 scalar_t__ TYPE_BINFO (scalar_t__) ; 
 scalar_t__ TYPE_FIELDS (scalar_t__) ; 
 scalar_t__ TYPE_HAS_TRIVIAL_ASSIGN_REF (scalar_t__) ; 
 int TYPE_QUAL_CONST ; 
 scalar_t__ VFIELD_NAME_P (scalar_t__) ; 
 int /*<<< orphan*/  ansi_assopname (int /*<<< orphan*/ ) ; 
 scalar_t__ begin_compound_stmt (int /*<<< orphan*/ ) ; 
 scalar_t__ build2 (int /*<<< orphan*/ ,scalar_t__,scalar_t__,scalar_t__) ; 
 scalar_t__ build3 (int /*<<< orphan*/ ,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 scalar_t__ build_base_path (int /*<<< orphan*/ ,scalar_t__,scalar_t__,int) ; 
 scalar_t__ build_modify_expr (scalar_t__,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ build_special_member_call (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int) ; 
 int /*<<< orphan*/  build_tree_list (scalar_t__,scalar_t__) ; 
 scalar_t__ convert_from_reference (scalar_t__) ; 
 scalar_t__ cp_build_qualified_type (scalar_t__,int) ; 
 int cp_type_quals (scalar_t__) ; 
 scalar_t__ current_class_ref ; 
 scalar_t__ current_class_type ; 
 int /*<<< orphan*/  error (char*,scalar_t__) ; 
 int /*<<< orphan*/  finish_compound_stmt (scalar_t__) ; 
 int /*<<< orphan*/  finish_expr_stmt (scalar_t__) ; 
 int /*<<< orphan*/  finish_return_stmt (scalar_t__) ; 
 scalar_t__ is_empty_class (scalar_t__) ; 
 scalar_t__ void_type_node ; 

__attribute__((used)) static void
do_build_assign_ref (tree fndecl)
{
  tree parm = TREE_CHAIN (DECL_ARGUMENTS (fndecl));
  tree compound_stmt;

  compound_stmt = begin_compound_stmt (0);
  parm = convert_from_reference (parm);

  if (TYPE_HAS_TRIVIAL_ASSIGN_REF (current_class_type)
      && is_empty_class (current_class_type))
    /* Don't copy the padding byte; it might not have been allocated
       if *this is a base subobject.  */;
  else if (TYPE_HAS_TRIVIAL_ASSIGN_REF (current_class_type))
    {
      tree t = build2 (MODIFY_EXPR, void_type_node, current_class_ref, parm);
      finish_expr_stmt (t);
    }
  else
    {
      tree fields;
      int cvquals = cp_type_quals (TREE_TYPE (parm));
      int i;
      tree binfo, base_binfo;

      /* Assign to each of the direct base classes.  */
      for (binfo = TYPE_BINFO (current_class_type), i = 0;
	   BINFO_BASE_ITERATE (binfo, i, base_binfo); i++)
	{
	  tree converted_parm;

	  /* We must convert PARM directly to the base class
	     explicitly since the base class may be ambiguous.  */
	  converted_parm = build_base_path (PLUS_EXPR, parm, base_binfo, 1);
	  /* Call the base class assignment operator.  */
	  finish_expr_stmt
	    (build_special_member_call (current_class_ref,
					ansi_assopname (NOP_EXPR),
					build_tree_list (NULL_TREE,
							 converted_parm),
					base_binfo,
					LOOKUP_NORMAL | LOOKUP_NONVIRTUAL));
	}

      /* Assign to each of the non-static data members.  */
      for (fields = TYPE_FIELDS (current_class_type);
	   fields;
	   fields = TREE_CHAIN (fields))
	{
	  tree comp = current_class_ref;
	  tree init = parm;
	  tree field = fields;
	  tree expr_type;
	  int quals;

	  if (TREE_CODE (field) != FIELD_DECL || DECL_ARTIFICIAL (field))
	    continue;

	  expr_type = TREE_TYPE (field);

	  if (CP_TYPE_CONST_P (expr_type))
	    {
	      error ("non-static const member %q#D, can't use default "
		     "assignment operator", field);
	      continue;
	    }
	  else if (TREE_CODE (expr_type) == REFERENCE_TYPE)
	    {
	      error ("non-static reference member %q#D, can't use "
		     "default assignment operator", field);
	      continue;
	    }

	  if (DECL_NAME (field))
	    {
	      if (VFIELD_NAME_P (DECL_NAME (field)))
		continue;
	    }
	  else if (ANON_AGGR_TYPE_P (expr_type)
		   && TYPE_FIELDS (expr_type) != NULL_TREE)
	    /* Just use the field; anonymous types can't have
	       nontrivial copy ctors or assignment ops.  */;
	  else
	    continue;

	  comp = build3 (COMPONENT_REF, expr_type, comp, field, NULL_TREE);

	  /* Compute the type of init->field  */
	  quals = cvquals;
	  if (DECL_MUTABLE_P (field))
	    quals &= ~TYPE_QUAL_CONST;
	  expr_type = cp_build_qualified_type (expr_type, quals);

	  init = build3 (COMPONENT_REF, expr_type, init, field, NULL_TREE);

	  if (DECL_NAME (field))
	    init = build_modify_expr (comp, NOP_EXPR, init);
	  else
	    init = build2 (MODIFY_EXPR, TREE_TYPE (comp), comp, init);
	  finish_expr_stmt (init);
	}
    }
  finish_return_stmt (current_class_ref);
  finish_compound_stmt (compound_stmt);
}