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
 scalar_t__ CLASSTYPE_TEMPLATE_INFO (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CLASSTYPE_TI_ARGS (int /*<<< orphan*/ ) ; 
 scalar_t__ CONSTRUCTOR ; 
 scalar_t__ CONST_DECL ; 
 scalar_t__ CP_TYPE_CONST_NON_VOLATILE_P (int /*<<< orphan*/ ) ; 
 scalar_t__ DECL_CLASS_SCOPE_P (scalar_t__) ; 
 int /*<<< orphan*/  DECL_CONTEXT (scalar_t__) ; 
 scalar_t__ DECL_INITIAL (scalar_t__) ; 
 int DECL_INTEGRAL_CONSTANT_VAR_P (scalar_t__) ; 
 int /*<<< orphan*/  INTEGRAL_OR_ENUMERATION_TYPE_P (int /*<<< orphan*/ ) ; 
 scalar_t__ STRING_CST ; 
 scalar_t__ TREE_CODE (scalar_t__) ; 
 int /*<<< orphan*/  TREE_CONSTANT (scalar_t__) ; 
 int /*<<< orphan*/  TREE_TYPE (scalar_t__) ; 
 scalar_t__ VAR_DECL ; 
 scalar_t__ error_mark_node ; 
 scalar_t__ fold_non_dependent_expr (scalar_t__) ; 
 int /*<<< orphan*/  mark_used (scalar_t__) ; 
 int /*<<< orphan*/  processing_template_decl ; 
 scalar_t__ unshare_expr (scalar_t__) ; 
 scalar_t__ uses_template_parms (int /*<<< orphan*/ ) ; 

__attribute__((used)) static tree
constant_value_1 (tree decl, bool integral_p)
{
  while (TREE_CODE (decl) == CONST_DECL
	 || (integral_p
	     ? DECL_INTEGRAL_CONSTANT_VAR_P (decl)
	     : (TREE_CODE (decl) == VAR_DECL
		&& CP_TYPE_CONST_NON_VOLATILE_P (TREE_TYPE (decl)))))
    {
      tree init;
      /* Static data members in template classes may have
	 non-dependent initializers.  References to such non-static
	 data members are not value-dependent, so we must retrieve the
	 initializer here.  The DECL_INITIAL will have the right type,
	 but will not have been folded because that would prevent us
	 from performing all appropriate semantic checks at
	 instantiation time.  */
      if (DECL_CLASS_SCOPE_P (decl)
	  && CLASSTYPE_TEMPLATE_INFO (DECL_CONTEXT (decl))
	  && uses_template_parms (CLASSTYPE_TI_ARGS
				  (DECL_CONTEXT (decl))))
	{
	  ++processing_template_decl;
	  init = fold_non_dependent_expr (DECL_INITIAL (decl));
	  --processing_template_decl;
	}
      else
	{
	  /* If DECL is a static data member in a template
	     specialization, we must instantiate it here.  The
	     initializer for the static data member is not processed
	     until needed; we need it now.  */
	  mark_used (decl);
	  init = DECL_INITIAL (decl);
	}
      if (init == error_mark_node)
	return decl;
      if (!init
	  || !TREE_TYPE (init)
	  || (integral_p
	      ? !INTEGRAL_OR_ENUMERATION_TYPE_P (TREE_TYPE (init))
	      : (!TREE_CONSTANT (init)
		 /* Do not return an aggregate constant (of which
		    string literals are a special case), as we do not
		    want to make inadvertent copies of such entities,
		    and we must be sure that their addresses are the
		    same everywhere.  */
		 || TREE_CODE (init) == CONSTRUCTOR
		 || TREE_CODE (init) == STRING_CST)))
	break;
      decl = unshare_expr (init);
    }
  return decl;
}