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
typedef  int /*<<< orphan*/ * tree ;
typedef  enum tree_code { ____Placeholder_tree_code } tree_code ;
typedef  int /*<<< orphan*/  cxx_pretty_printer ;

/* Variables and functions */
#define  BASELINK 149 
 int /*<<< orphan*/ * BASELINK_FUNCTIONS (int /*<<< orphan*/ *) ; 
#define  CONST_DECL 148 
 int /*<<< orphan*/ * DECL_NAME (int /*<<< orphan*/ *) ; 
#define  ENUMERAL_TYPE 147 
#define  FIELD_DECL 146 
#define  FUNCTION_DECL 145 
#define  IDENTIFIER_NODE 144 
 int /*<<< orphan*/  IDENTIFIER_TYPENAME_P (int /*<<< orphan*/ *) ; 
#define  LABEL_DECL 143 
#define  NAMESPACE_DECL 142 
#define  OVERLOAD 141 
 int /*<<< orphan*/ * OVL_CURRENT (int /*<<< orphan*/ *) ; 
#define  PARM_DECL 140 
#define  RECORD_TYPE 139 
#define  RESULT_DECL 138 
#define  TEMPLATE_DECL 137 
#define  TEMPLATE_ID_EXPR 136 
 int /*<<< orphan*/ * TEMPLATE_PARM_DECL (int /*<<< orphan*/ *) ; 
#define  TEMPLATE_PARM_INDEX 135 
#define  TEMPLATE_TEMPLATE_PARM 134 
#define  TEMPLATE_TYPE_PARM 133 
 int TREE_CODE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TREE_TYPE (int /*<<< orphan*/ *) ; 
#define  TYPE_DECL 132 
 int /*<<< orphan*/ * TYPE_IDENTIFIER (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * TYPE_NAME (int /*<<< orphan*/ *) ; 
#define  UNBOUND_CLASS_TEMPLATE 131 
#define  UNION_TYPE 130 
#define  USING_DECL 129 
#define  VAR_DECL 128 
 int /*<<< orphan*/ * constructor_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_destructor_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pp_complement (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pp_cxx_canonical_template_parameter (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pp_cxx_conversion_function_id (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pp_cxx_identifier (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  pp_cxx_template_id (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pp_cxx_tree_identifier (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pp_unsupported_tree (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
pp_cxx_unqualified_id (cxx_pretty_printer *pp, tree t)
{
  enum tree_code code = TREE_CODE (t);
  switch (code)
    {
    case RESULT_DECL:
      pp_cxx_identifier (pp, "<return-value>");
      break;

    case OVERLOAD:
      t = OVL_CURRENT (t);
    case VAR_DECL:
    case PARM_DECL:
    case CONST_DECL:
    case TYPE_DECL:
    case FUNCTION_DECL:
    case NAMESPACE_DECL:
    case FIELD_DECL:
    case LABEL_DECL:
    case USING_DECL:
    case TEMPLATE_DECL:
      t = DECL_NAME (t);

    case IDENTIFIER_NODE:
      if (t == NULL)
	pp_cxx_identifier (pp, "<unnamed>");
      else if (IDENTIFIER_TYPENAME_P (t))
	pp_cxx_conversion_function_id (pp, t);
      else
	{
	  if (is_destructor_name (t))
	    {
	      pp_complement (pp);
	      /* FIXME: Why is this necessary? */
	      if (TREE_TYPE (t))
		t = constructor_name (TREE_TYPE (t));
	    }
	  pp_cxx_tree_identifier (pp, t);
	}
      break;

    case TEMPLATE_ID_EXPR:
      pp_cxx_template_id (pp, t);
      break;

    case BASELINK:
      pp_cxx_unqualified_id (pp, BASELINK_FUNCTIONS (t));
      break;

    case RECORD_TYPE:
    case UNION_TYPE:
    case ENUMERAL_TYPE:
      pp_cxx_unqualified_id (pp, TYPE_NAME (t));
      break;

    case TEMPLATE_TYPE_PARM:
    case TEMPLATE_TEMPLATE_PARM:
      if (TYPE_IDENTIFIER (t))
	pp_cxx_unqualified_id (pp, TYPE_IDENTIFIER (t));
      else
	pp_cxx_canonical_template_parameter (pp, t);
      break;

    case TEMPLATE_PARM_INDEX:
      pp_cxx_unqualified_id (pp, TEMPLATE_PARM_DECL (t));
      break;

    case UNBOUND_CLASS_TEMPLATE:
      pp_cxx_unqualified_id (pp, TYPE_NAME (t));
      break;

    default:
      pp_unsupported_tree (pp, t);
      break;
    }
}