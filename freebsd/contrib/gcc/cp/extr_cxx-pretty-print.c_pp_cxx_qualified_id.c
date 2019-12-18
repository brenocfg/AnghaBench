#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tree ;
struct TYPE_7__ {int /*<<< orphan*/  enclosing_scope; } ;
typedef  TYPE_1__ cxx_pretty_printer ;

/* Variables and functions */
 int /*<<< orphan*/  DECL_CONSTRUCTOR_P (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DECL_CONTEXT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DECL_FUNCTION_MEMBER_P (int /*<<< orphan*/ ) ; 
#define  FUNCTION_DECL 132 
#define  OFFSET_REF 131 
#define  OVERLOAD 130 
 int /*<<< orphan*/  OVL_CURRENT (int /*<<< orphan*/ ) ; 
#define  PTRMEM_CST 129 
 int /*<<< orphan*/  PTRMEM_CST_CLASS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PTRMEM_CST_MEMBER (int /*<<< orphan*/ ) ; 
#define  SCOPE_REF 128 
 int TREE_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_OPERAND (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  TREE_TYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TYPE_CONTEXT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TYPE_P (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pp_cxx_nested_name_specifier (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pp_cxx_parameter_declaration_clause (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pp_cxx_template_keyword_if_needed (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pp_cxx_unqualified_id (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
pp_cxx_qualified_id (cxx_pretty_printer *pp, tree t)
{
  switch (TREE_CODE (t))
    {
      /* A pointer-to-member is always qualified.  */
    case PTRMEM_CST:
      pp_cxx_nested_name_specifier (pp, PTRMEM_CST_CLASS (t));
      pp_cxx_unqualified_id (pp, PTRMEM_CST_MEMBER (t));
      break;

      /* In Standard C++, functions cannot possibly be used as
	 nested-name-specifiers.  However, there are situations where
	 is "makes sense" to output the surrounding function name for the
	 purpose of emphasizing on the scope kind.  Just printing the
	 function name might not be sufficient as it may be overloaded; so,
	 we decorate the function with its signature too.
	 FIXME:  This is probably the wrong pretty-printing for conversion
	 functions and some function templates.  */
    case OVERLOAD:
      t = OVL_CURRENT (t);
    case FUNCTION_DECL:
      if (DECL_FUNCTION_MEMBER_P (t))
	pp_cxx_nested_name_specifier (pp, DECL_CONTEXT (t));
      pp_cxx_unqualified_id
	(pp, DECL_CONSTRUCTOR_P (t) ? DECL_CONTEXT (t) : t);
      pp_cxx_parameter_declaration_clause (pp, TREE_TYPE (t));
      break;

    case OFFSET_REF:
    case SCOPE_REF:
      pp_cxx_nested_name_specifier (pp, TREE_OPERAND (t, 0));
      pp_cxx_unqualified_id (pp, TREE_OPERAND (t, 1));
      break;

    default:
      {
	tree scope = TYPE_P (t) ? TYPE_CONTEXT (t) : DECL_CONTEXT (t);
	if (scope != pp->enclosing_scope)
	  {
	    pp_cxx_nested_name_specifier (pp, scope);
	    pp_cxx_template_keyword_if_needed (pp, scope, t);
	  }
	pp_cxx_unqualified_id (pp, t);
      }
      break;
    }
}